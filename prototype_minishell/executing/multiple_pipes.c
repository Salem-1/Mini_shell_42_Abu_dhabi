/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 07:32:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t->npipes is number of pipes + 1 just for sake of simplicity

void	exec_multiple_pipes(char *cmd, t_list *env, int *exit_status)
{
	struct t_pipes	*t;
	int				**fd;
	int				pid;
	int				i;

	fd = NULL;
	t = parsing_piped_cmd(cmd, env, exit_status);
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
		exec_export_unset_cd_in_parent(i,  t, env);
		pid = fork();
		if (pid == 0)
		{
			piping_and_redirections(i, fd, t, env);
			return ;
		}
		if (t->single_cmd[i]->after_sep == 't')
			i++;
		//increment the i for the heredoc sake after finishing the heredoc inshalla
		i++;
	}
	close_files_and_wait(fd, t, exit_status);
		// flush_pipes(t);
	return ;
}

void	exec_export_unset_cd_in_parent(
		int i,  struct t_pipes *t, t_list *env)
{
	int	redirec;

	redirec = 0;
	if (!t->single_cmd[i])
		return ;
	while (t->single_cmd[redirec] && redirec < t->npipes)
	{
		if (t->single_cmd[redirec]->after_sep == 'p'
			|| t->single_cmd[redirec]->after_sep == 'p')
			return ;
		redirec++;
	}
	if (!ft_strncmp(t->single_cmd[i]->cmd, "cd", 3))
		exec_cd(t->single_cmd[i], &env, t, 's');
	else if (!ft_strncmp(t->single_cmd[i]->cmd, "export", 7))
		exec_export(t->single_cmd[i], &env, 's');
	else if (!ft_strncmp(t->single_cmd[i]->cmd, "unset", 6))
		exec_unset(t->single_cmd[i], &env, 1, 's');
}

void	piping_and_redirections(int i, int **fd, struct t_pipes *t, t_list *env)
{
	if (t->npipes == 1 || t->single_cmd[i]->after_sep == 't' )
	{
		if (t->single_cmd[i]->after_sep == 't')
			input_execution(t, fd, i);
		just_execve(t->single_cmd[i], env, t);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		output_append_execution(t, fd, i);
	else if (t->single_cmd[i]->after_sep == 'h' || t->single_cmd[i]->before_sep == 'h')
	{	
		if (t->single_cmd[i]->before_sep == 'h')
			exec_exit(t, 0);
		lets_heredoc(fd, &i, t);
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
		just_execve(t->single_cmd[i], env, t);
	}
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
	just_execve(t->single_cmd[i], env, t);
}

void	close_files_and_wait(int **fd, struct t_pipes	*t, int *exit_satus)
{
	int	forwait;
	int	i;

	i = 0;
	close_files(fd, t->npipes);
	while (i < t->npipes)
	{
		wait(&forwait);
		printf(">>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<\n");
		*exit_satus = WEXITSTATUS(forwait);
		printf("The waited status exit code is %d\n", *exit_satus);
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