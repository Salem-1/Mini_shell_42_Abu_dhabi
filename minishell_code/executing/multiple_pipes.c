/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/09 07:05:13 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity
//the exit code of the staff executed inside the child is missed up
void	exec_multiple_pipes(char *cmd, t_list *env, int *exit_status)
{
	struct t_pipes	*t;
	int				**fd;
	int				pid;
	int				i;

forens_printf("Inside exec_multiple_pipes \n");
	fd = NULL;
	t = parsing_piped_cmd(cmd, env, exit_status);
	if (!t)
		return ;
	if (t->parse_error != 0)
	{
forens_printf("Throwing parsing errorr, t->parse_error = %d\n", t->parse_error);
		throw_parser_error(t, exit_status);
		return ;
	}
	//forens_printf("\nt->parse_error = %d\n", t->parse_error);
	i = 0;
	pid = 0;
visualized_piped_cmd(t);
	if_there_is_heredoc_fill_it(t, env);
	//forens_printf("opening %d pipes\n", t->npipes);
	fd = open_pipes(t->npipes, fd);
	t->fd = fd;
	//remeber to check for the null cmd
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->after_sep == 'h')
			i = skip_multiple_heredocs(t, i);
		*exit_status = exec_exit_export_unset_cd_in_parent(
				&i, t, env, exit_status);
		if (update_i_in_case_of_redirection(t, &i))
			continue ;
// err_printf("inside execution loof i= %d\n", i);
		pid = fork();
		if (pid == 0)
		{
			piping_and_redirections(i, fd, t, env);
			return ;
		}
		if (t->single_cmd[i]->after_sep == 't')
			i++;
		i++;
	}
	if (!was_exec_in_parent(i, exit_status, t))
	{
		close_files_and_wait(fd, t, exit_status);
	}
	flush_pipes(t);
	return ;
}

//do the staff of input after out put and vise versa here
int	update_i_in_case_of_redirection(t_pipes *t, int *i)
{
	char redir;

	redir = t->single_cmd[*i]->before_sep;
	if (redir == 'g' || redir == 'a' || redir == 'h' || redir == 't')
	{
		if (*i == 0)
			return(0);
		*i = *i + 1;
		return (1);
	}
	return (0);
}

//I created this function to update the exit status for the locals
int	was_exec_in_parent(int i, int *exit_status, t_pipes *t)
{
	int	redirec;

	redirec = 0;
	while (t->single_cmd[redirec] && redirec < t->npipes)
	{
		if (t->single_cmd[redirec]->after_sep == 'p'
			|| t->single_cmd[redirec]->before_sep == 'p' )
			return (0);
		redirec++;
	}
	//this is a seg fault function in case < file cat 
	// if (!local_exec_cmd_spec(t))
	// 	return (0);
	if (*exit_status != 0)
		i = *exit_status;
	close_files_and_wait(t->fd, t, exit_status);
	if (i != 0)
		*exit_status = i;
	return (1);
}

//lat 5 lines setting the exit code of the bins executed in parent


//for echo hi > f1 > f2 > f3
		//it creates f1 and f2 and only fill f3
//for cat < f1 < f2 < f3
		//cat reads only from f3 and ignore f1 and f2
//for echo hi > f1 > f2 > f3 < f4
		//it creates f1 f2 and fill f3 with hi and do nothing with f4
void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	if (t->npipes == 1 || t->single_cmd[i]->after_sep == 't')
	{
		if (t->single_cmd[i]->after_sep == 't')
			exec_to_take_operations(t, env, fd, i , 0);
		else
			close_files(fd, t->npipes);
		just_execve(t->single_cmd[i], env, t);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		exec_to_output_operations(t, env,fd, i, 0);
	else if (t->single_cmd[i]->after_sep == 'h')
	{	
		write(fd[i][1], t->single_cmd[i + 1]->args[0],
			ft_strlen(t->single_cmd[i + 1]->args[0]));
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
		free(t->single_cmd[i + 1]->args[0]);
		// if (case_out)
		// 	return (0);
		//then add this case to the heredoc execution 
		just_execve(t->single_cmd[i], env, t);
	}
	else
		execute_in_pipe(t, env, fd, i);
}
