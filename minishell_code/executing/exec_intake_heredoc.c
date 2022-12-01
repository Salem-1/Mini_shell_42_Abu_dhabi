/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_intake_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:58:33 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 14:39:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//(1 * !(i == 0)) to handle the special case of < cat, in order no to seg fault
int	exec_to_take_operations(t_pipes *t,
		t_list *env, int i, int case_out)
{
	int	local_i;
	int	local_fd;

	local_i = i;
	while (t->single_cmd[local_i]->after_sep == 't')
		local_fd = local_fd_with_multiple_intakes(t, &local_i, i, local_fd);
	local_fd = open(t->single_cmd[local_i]->cmd, O_RDONLY);
	if (dup2(local_fd, STDIN_FILENO) == -1)
		perror("dup2");
	if (local_i != t->npipes - 1)
	{
		if (dup2(t->fd[local_i][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close(local_fd);
	close_files(t->fd, t->npipes);
	if ((t->single_cmd[local_i]->after_sep == 'g'
			|| t->single_cmd[local_i]->after_sep == 'a'))
		exec_to_output_operations(t, env, local_i, 1);
	if (case_out)
		return (0);
	just_execve(t->single_cmd[i], env, t);
	return (0);
}

int	local_fd_with_multiple_intakes(
		t_pipes *t, int *local_i, int i, int local_fd)
{
	local_fd = open(t->single_cmd[*local_i +1]->cmd, O_RDONLY);
	if (local_fd == -1)
		intake_errors(t, i + 1, local_fd, t->fd);
	close(local_fd);
	*local_i = *local_i + 1;
	return (local_fd);
}

void	exec_heredoc(t_pipes *t, int i, t_list *env, int case_out)
{
	int	local_i;

	local_i = i;
	while (t->single_cmd[local_i]->after_sep == 'h')
		local_i++;
	dup2(t->fd[i][0], STDIN_FILENO);
	if (local_i != t->npipes - 1)
	{
		if (dup2(t->fd[local_i][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close_files(t->fd, t->npipes);
	if ((t->single_cmd[local_i]->after_sep == 'g'
			|| t->single_cmd[local_i]->after_sep == 'a'))
		exec_to_output_operations(t, env, local_i, 1);
	if (case_out)
		return ;
	just_execve(t->single_cmd[i], env, t);
}
