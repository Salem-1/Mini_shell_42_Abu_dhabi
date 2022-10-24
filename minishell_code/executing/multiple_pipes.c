/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 22:03:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity

void	exec_multiple_pipes(char *cmd, t_list *env, int *exit_status)
{
	struct t_pipes	*t;
	int				**fd;
	int				pid;
	int				i;

//forens_printf("Inside exec_multiple_pipes \n");
	fd = NULL;
	t = parsing_piped_cmd(cmd, env, exit_status);
	//try cleanining all memory here 
	//try exit here to check the memory leaks of the parsing 
	//this is a good starting point
	if (!t)
		return ;
	if (t->parse_error != 0)
	{
		//forens_printf("Throwing parsing errorr, t->parse_error = %d\n", t->parse_error);
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
	//remeber to check for the null cmd
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->after_sep == 'h')
			i = skip_multiple_heredocs(t, i);
		if (t->single_cmd[i]->before_sep == 'g'
			|| t->single_cmd[i]->before_sep == 'a'
			|| t->single_cmd[i]->before_sep == 'h'
			|| t->single_cmd[i]->before_sep == 't')
		{
			i++;
			continue ;
		}
		//forens_printf("Multiple_cmd line 56 Current cmd = %s\n", t->single_cmd[i]->cmd);
		exec_exit_export_unset_cd_in_parent(&i,  t, env, exit_status);
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
	close_files_and_wait(fd, t, exit_status);
		// flush_pipes(t);
	return ;
}

//for echo hi > f1 > f2 > f3
		//it creates f1 and f2 and only fill f3
//for cat < f1 < f2 < f3
		//cat reads only from f3 and ignore f1 and f2
//for echo hi > f1 > f2 > f3 < f4
		//it creates f1 f2 and fill f3 with hi and do nothing with f4
void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	if (t->npipes == 1 || t->single_cmd[i]->after_sep == 't' )
	{
		if (t->single_cmd[i]->after_sep == 't')
			exec_to_take_operations(t, env, fd, i);
		else
			close_files(fd, t->npipes);
		just_execve(t->single_cmd[i], env, t);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		exec_to_output_operations(t, env,fd, i);
	else if (t->single_cmd[i]->after_sep == 'h')
	{	
		write(fd[i][1], t->single_cmd[i + 1]->args[0],
			ft_strlen(t->single_cmd[i + 1]->args[0]));
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
		free(t->single_cmd[i + 1]->args[0]);
		just_execve(t->single_cmd[i], env, t);
	}
	else
		execute_in_pipe(t, env, fd, i);
}

void	close_files_and_wait(int **fd, struct t_pipes	*t, int *exit_satus)
{
	int	forwait;
	int	i;

	i = 0;
	close_files(fd, t->npipes);
	while (i < t->npipes)
	{
		wait(&forwait);
		*exit_satus = WEXITSTATUS(forwait);
		// *exit_satus = WIFSIGNALED(forwait);
// //forens_printf("in close files and wiat cmd %d execution end exit status %d\n", i, *exit_satus);
		i++;
	}
// 	//forens_printf("\n------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n\n\n");
}

int	**open_pipes(int n, int **fd)
{
	int	i;
	i = 0;
	fd = malloc(sizeof(int *) * n);
	if (!fd)
		return (NULL);
	while (i < n)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_split((void **)fd);
			return (NULL);
		}
		if (pipe(fd[i]) == -1)
		{
			free_split((void **)fd);
			return (NULL);
		}
		i++;
	}
	return (fd);
}

void	close_files(int **fd, int npipes)
{
	int	i;

	i = 0;
	while (i < npipes )
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}