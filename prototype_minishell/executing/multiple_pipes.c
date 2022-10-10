/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/09 16:36:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity
void	exec_multiple_pipes(char *cmd, t_list *env)
{	struct t_pipes	*t;
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
		if (t->single_cmd[i]->after_sep == 't')
			i++;
		i++;
	}
	close_files_and_wait(fd, t);
	return ;
}

void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	if (t->npipes == 1 || t->single_cmd[i]->after_sep == 't' )
	{
		if (t->single_cmd[i]->after_sep == 't')
			input_execution(t, fd, i);
		just_execve(t->single_cmd[i], env);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		output_append_execution(t, fd, i);
	if (i == 0 )
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
}

void	output_append_execution(t_pipes *t, int **fd, int i)
{
	if (t->single_cmd[i]->after_sep == 'g')
	{
		close(fd[i][1]);
		fd[i][1] = open(t->single_cmd[i + 1]->cmd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[i][1] == -1)
			perror("open");
	}
	else if (t->single_cmd[i]->after_sep == 'a')
	{
		close(fd[i][i]);
		fd[i][1] = open(t->single_cmd[i + 1]->cmd,
				O_CREAT | O_APPEND |O_WRONLY, 0644);
		if (fd[i][1] == -1)
			perror("open");
	}
}

void	input_execution(t_pipes *t, int **fd, int i)
{
	if (t->single_cmd[i]->after_sep == 't')
	{
		close(fd[i][0]);
		fd[i][0] = open(t->single_cmd[i + 1]->cmd, O_RDONLY);
		if (fd[i][0] == -1)
			perror("open");
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
	}
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
		printf(">>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<\n");
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