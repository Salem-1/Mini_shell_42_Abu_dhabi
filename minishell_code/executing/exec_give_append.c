/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_give_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:53:28 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 21:49:04 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output_append_execution(t_pipes *t, int i, int **fd)
{
	int	local_fd;

	local_fd = 0;
	while (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
	{
		if (t->single_cmd[i]->after_sep == 'g')
			local_fd = open(t->single_cmd[i + 1]->cmd,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (t->single_cmd[i]->after_sep == 'a')
			local_fd = open(t->single_cmd[i + 1]->cmd,
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (local_fd == -1)
			output_error_handle(t, i + 1, local_fd, fd);
		close(local_fd);
		i++;
	}
	return (i);
}

int	exec_to_output_operations(t_pipes *t,
	t_list *env, int i, int case_in)
{
	int	local_fd;
	int	local_i;

	local_fd = output_append_execution(t, i, t->fd) - 1;
	local_i = local_fd;
	local_fd = opening_out_file(t, local_fd);
	if (local_fd == -1)
		output_error_handle(t, local_fd + 1, local_fd, t->fd);
	if (dup2(local_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(local_fd);
	if (t->single_cmd[i]->before_sep == 'p')
		dup2(t->fd[i - 1][0], STDIN_FILENO);
	close_files(t->fd, t->npipes);
	if (t->single_cmd[local_i]->after_sep == 't')
		exec_to_take_operations(t, env, local_fd, 1);
	else if (t->single_cmd[local_i]->after_sep == 'h')
		exec_heredoc(t, local_fd, env, 1);
	if (case_in)
		return (0);
	else
		just_execve(t->single_cmd[i], env, t);
	return (0);
}

int	opening_out_file(t_pipes *t, int local_fd)
{
	if (t->single_cmd[local_fd]->after_sep == 'g')
			local_fd = open(t->single_cmd[local_fd + 1]->cmd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (t->single_cmd[local_fd]->after_sep == 'a')
			local_fd = open(t->single_cmd[local_fd + 1]->cmd,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	return (local_fd);
}
