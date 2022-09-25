/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 07:26:11 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/25 10:04:31 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	//pipe for files
	//fork
	//dup the stdout to the write pipe
	//inside the parent fork() again
	//dup the stdin to the reading pipe
	//exec then close all pipes in the main, and inside if conditions
	// // char *cmd1[] = {"/usr/bin/top", "-l", "1", NULL};
	// char *cmd2[] = {"/usr/bin/grep", "CPU", NULL};
void	exec_with_pipe(char *cmd, t_list *env)
{
	static t_pipes	*t;
	int				fd[2];
	int				pid;
	int				pid2;

	t = parsing_piped_cmd(cmd);
	if (pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
		exec_to_out(fd, t, env);
	pid2 = fork();
	if (pid2 == 0)
		exec_to_in(fd, t, env);
	close(fd[0]);
	// close(fd[1]);
	wait(NULL);
	wait(NULL);
	flush_pipes(t);
	return ;
}

void	exec_to_out(int fd[2], t_pipes *t, t_list *env)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	just_execve(t->single_cmd[0], env);
}

void	exec_to_in(int fd[2], t_pipes *t, t_list *env)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	just_execve(t->single_cmd[1], env);
}
	// printf("Execution inside exec with pipes under construction\n");
	// int i = 0;
	// int		pipes = 1;

	// if (pipe(fd) == -1)
	// 	perror("pipe");
	// while (i < pipes + 1)
	// {
	// 	if (pid != 0)
	// 		pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		if (i == 0)
	// 		{
	// 			dup2(fd[1], STDOUT_FILENO);
	// 			close(fd[0]);
	// 			close(fd[1]);
	// 			execve(cmd1[0], cmd1, NULL);
	// 		}
	// 		else
	// 		{
	// 			dup2(fd[0], STDIN_FILENO);
	// 			close(fd[0]);
	// 			close(fd[1]);
	// 			// printf("execting second command\n");
	// 			if (execve(cmd2[0], cmd2, NULL) == -1)
	// 				perror("execve");
	// 		}
	// 	}
	// 	i++;
	// }
	// i = 0;
	// // printf("this shoud print after execution once\n");
	// close(fd[1]);
	// close(fd[0]);
	// while (i < pipes + 1)
	// {
	// 	wait(NULL);
	// 	i++;
	// }