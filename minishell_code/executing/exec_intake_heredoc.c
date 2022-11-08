/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_intake_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:58:33 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/08 20:00:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//(1 * !(i == 0)) to handle the special case of < cat, in order no to seg fault
int	exec_to_take_operations(t_pipes *t, t_list *env, int **fd, int i, int case_out)
{
	int	local_i;
	int	local_fd;

	local_i = i;
	while (t->single_cmd[local_i]->after_sep == 't')
	{
		local_fd = open(
				t->single_cmd[local_i +1 ]->cmd, O_RDONLY);
		if (local_fd == -1)
			pipes_and_redirect_errors(t, i + 1, local_fd, fd);
		close(local_fd);
		local_i++;
		// if (i == 0)
		// 	break ;
	}
err_printf("inside exec to take operations\n");
	local_fd = open(t->single_cmd[local_i]->cmd, O_RDONLY);
	if (dup2(local_fd, STDIN_FILENO) == -1)
		perror("dup2");
	if (local_i != t->npipes - 1)
	{
		if (dup2(fd[local_i][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close(local_fd);
	close_files(fd, t->npipes);
	if ((t->single_cmd[local_i]->after_sep == 'g'
		|| t->single_cmd[local_i]->after_sep == 'a') && i != -1)
	{
		exec_to_output_operations(t, env, t->fd,  local_i, 1);
	}
	if (case_out == 1)
		return (0);
	if (i == 0)
	{
		// flush_pipes(t);
		exit(0);
	}
	just_execve(t->single_cmd[i], env, t);
	return (0);
}