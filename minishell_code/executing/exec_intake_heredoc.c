/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_intake_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:58:33 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/25 03:23:31 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_to_take_operations(t_pipes *t, t_list *env, int **fd, int i)
{
	int	local_i;
	int	local_fd;

	local_i = i;
	while (t->single_cmd[local_i]->after_sep == 't')
	{
		local_fd = open(t->single_cmd[local_i + 1]->cmd, O_RDONLY);
		if (local_fd == -1)
			pipes_and_redirect_errors(t, i + 1, local_fd, fd);
		close(local_fd);
		local_i++;
	}
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
	just_execve(t->single_cmd[i], env, t);
	return (0);
}