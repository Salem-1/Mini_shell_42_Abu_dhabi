/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_give_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:53:28 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/08 18:49:10 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//case  echo hi > f1 > f2 >> f3 >> f4
//also open in local file descriptors
int	output_append_execution(t_pipes *t, int i, int **fd)
{
	int	local_fd;
// err_printf("entered the append execution function\n");
	local_fd = 0;
	while (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
	{
		if (t->single_cmd[i]->after_sep == 'g')
			local_fd = open(t->single_cmd[i + 1]->cmd,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (t->single_cmd[i]->after_sep == 'a')
			local_fd = open(t->single_cmd[i + 1]->cmd,
					O_CREAT | O_APPEND |O_WRONLY, 0644);
		if (local_fd == -1)
			pipes_and_redirect_errors(t, i + 1, local_fd, fd);
		close(local_fd);
		i++;
	}
	return (i);
}

/*
execve down here execute the command before the redirection
regardless it was in pipe or not
*/

int	exec_to_output_operations(t_pipes *t, t_list *env, int **fd, int i, int case_in)
{
	int	local_fd;
	local_fd = output_append_execution(t, i, fd) - 1;
	if (t->single_cmd[local_fd]->after_sep == 'g')
			local_fd = open(t->single_cmd[local_fd + 1]->cmd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (t->single_cmd[local_fd]->after_sep == 'a')
			local_fd = open(t->single_cmd[local_fd + 1]->cmd,
				O_CREAT | O_APPEND |O_WRONLY, 0644);
	if (local_fd == -1)
		pipes_and_redirect_errors(t, local_fd + 1, local_fd, fd);
	if (dup2(local_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(local_fd);
	if (t->single_cmd[i]->before_sep == 'p')
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	close_files(fd, t->npipes);
	if (t->single_cmd[local_fd]->after_sep == 't')
		exec_to_take_operations(t, env, t->fd, local_fd, 1);
	// || t->single_cmd[local_fd]->after_sep == 'h')
	if (case_in)
		return (0);
	else
		just_execve(t->single_cmd[i], env, t);
	return (0);
}
