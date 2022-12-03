/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 07:33:07 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity
//the exit code of the staff executed inside the child is missed up

void	exec_multiple_pipes(char *cmd, t_list *env, int *exit_status)
{
	struct t_pipes	*t;
	int				i;
	int				parent_exit_status;
	int				return_or_continue;

	return_or_continue = 0;
	parent_exit_status = 0;
	t = parsing_piped_cmd(cmd, env, exit_status);
	if (errord_t_piped(t, exit_status))
		return ;
	i = init_exec_multiple_pipes_args(t, env);
	while (i < t->npipes)
	{
		return_or_continue = exec_loop(t, &i, &parent_exit_status);
		if (return_or_continue == 1)
			return ;
		else if (return_or_continue == 2)
			continue ;
		i++;
	}
	close_files_and_wait(t->fd, t, exit_status);
	if (parent_exit_status != 0)
		*exit_status = parent_exit_status;
	flush_pipes(t);
}

int	update_i_in_case_of_redirection(t_pipes *t, int *i)
{
	char	redir;

	redir = t->single_cmd[*i]->before_sep;
	if (redir == 'g' || redir == 'a' || redir == 'h' || redir == 't')
	{
		if (*i == 0)
			return (0);
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
	if (*exit_status != 0)
		i = *exit_status;
	close_files_and_wait(t->fd, t, exit_status);
	if (i != 0)
		*exit_status = i;
	return (1);
}

//lat 5 lines setting the exit code of the bins executed in parent

void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	if (t->npipes == 1 || t->single_cmd[i]->after_sep == 't')
	{
		if (t->single_cmd[i]->after_sep == 't')
			exec_to_take_operations(t, env, i, 0);
		else
			close_files(fd, t->npipes);
		just_execve(t->single_cmd[i], env, t);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		exec_to_output_operations(t, env, i, 0);
	else if (t->single_cmd[i]->after_sep == 'h')
	{
		exec_heredoc(t, i, env, 0);
	}
	else
		execute_in_pipe(t, env, fd, i);
}
