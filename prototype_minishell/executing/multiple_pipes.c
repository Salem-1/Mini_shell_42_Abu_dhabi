/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/08 00:31:51 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity
void	exec_multiple_pipes(char *cmd, t_list *env)
{
	struct t_pipes	*t;
	int				**fd;
	int				pid;
	int				i;

	fd = NULL;
	t = parsing_piped_cmd(cmd);
	if (!t)
		return ;
	i = 0;
	pid = 0;
	visualized_piped_cmd(t);
	fd = open_pipes(t->npipes, fd);
	printf(">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<\n");
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->before_sep == 'g')
		{
			i++;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			piping_and_redirections(i, fd, t, env);
			return ;
		}
		i++;
	}
	close_files_and_wait(fd, t);
	return ;
}

void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	int	w_end;
	int	r_end;

	w_end = fd[i][1];
	r_end = STDIN_FILENO;
	if (t->npipes == 1)
		just_execve(t->single_cmd[i], env);
	if (t->single_cmd[i]->after_sep == 'g')
	{
		w_end = open(t->single_cmd[i + 1]->cmd, O_CREAT | O_WRONLY, 0644);
		if (w_end == -1)
			perror("open");
	}
	if (i == 0)
		dup2(w_end, STDOUT_FILENO);
	else if (i == t->npipes -1)
		dup2(fd[i -1][0], STDIN_FILENO);
	else
	{
		dup2(w_end, STDOUT_FILENO);
		dup2(fd[i -1][0], STDIN_FILENO);
	}
	close_files(fd, t->npipes);
	just_execve(t->single_cmd[i], env);
}

void	close_files_and_wait(int **fd, struct t_pipes	*t)
{
	int	forwait;
	int	i;

	i = 0;
	close_files(fd, t->npipes);
	while (i < t->npipes)
	{
		wait(&forwait);
		printf(">>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<\n");
		printf("The waited status exit code is %d\n", WEXITSTATUS(forwait));
		i++;
	}
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