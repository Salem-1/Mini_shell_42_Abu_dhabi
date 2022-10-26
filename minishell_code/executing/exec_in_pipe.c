/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:47:50 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/27 01:03:00 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_in_pipe(t_pipes *t, t_list *env,int **fd, int i)
{
	// int	heredoc_case;

	// heredoc_case = 0;
	// if (i > 1)
	// {
	// 	if (t->single_cmd[i -1]-> before_sep == 'h'
	// 		|| t->single_cmd[i -1]-> before_sep == 't')
	// 	{
	// 		heredoc_case = 0;
	// 		err_printf("Reading from pipe   %d, i = %d , t->npipes -1 = %d\n\n", i - 1 + heredoc_case, i , t->npipes -1);
	// 	}
	// }
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == t->npipes - 1)
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		dup2(fd[i][1], STDOUT_FILENO);
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	close_files(fd, t->npipes);
	just_execve(t->single_cmd[i], env, t);
	return (0);
}

