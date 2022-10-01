/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 21:29:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity
void	exec_multiple_pipes(char *cmd, t_list *env)
{
	static t_pipes	*t;
	int				**fd;
	int				pid;
	int				i;
	int				forwait;

	fd = NULL;
	t = parsing_piped_cmd(cmd);
	i = 0;
	pid = 0;
	fd = open_pipes(t->npipes, fd);
	printf("Number of pipes (%d)\n", t->npipes);
	while (i < t->npipes)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				dup2(fd[i][1], STDOUT_FILENO);
			else if (i == t->npipes -1)
				dup2(fd[i -1][0], STDIN_FILENO);
			else
			{
				dup2(fd[i][1], STDOUT_FILENO);
				dup2(fd[i -1][0], STDIN_FILENO);
			}
			close_files(fd, t->npipes);
			just_execve(t->single_cmd[i], env);
			return ;
		}
		i++;
	}
	close_files(fd, t->npipes);
	i = 0;
	while (i < t->npipes)
	{
		wait(&forwait);
		printf("The watied status exit code is %d\n", WEXITSTATUS(forwait));
		i++;
	}
	return ;
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
			perror("pipe");
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
	// free_split((void **)fd);
}