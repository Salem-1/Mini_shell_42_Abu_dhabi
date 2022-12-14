/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:33:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/20 16:58:14 by ahsalem          ###   ########.fr       */
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

forens_printf("Inside exec_multiple_pipes \n");
	fd = NULL;
	t = parsing_piped_cmd(cmd, env, exit_status);
	if (!t)
		return ;
	if (t->parse_error != 0)
	{
		forens_printf("Throwing parsing errorr, t->parse_error = %d\n", t->parse_error);
		throw_parser_error(t, exit_status);
		return ;
	}
	forens_printf("\nt->parse_error = %d\n", t->parse_error);
	i = 0;
	pid = 0;
	visualized_piped_cmd(t);
	if_there_is_heredoc_fill_it(t, env);
	forens_printf("opening %d pipes\n", t->npipes);
	fd = open_pipes(t->npipes, fd);
	//remeber to check for the null cmd
	while (i < t->npipes)
	{
		forens_printf("Multiple_cmd line 45 Current cmd = %s\n", t->single_cmd[i]->cmd);
		if (t->single_cmd[i]->after_sep == 'h')
			i = skip_multiple_heredocs(t, i);
		// forens_printf("after_heredoc checkpoint\n");
		forens_printf("Multiple_cmd line 49 Current cmd = %s\n", t->single_cmd[i]->cmd);
		if (t->single_cmd[i]->before_sep == 'g'
			|| t->single_cmd[i]->before_sep == 'a' || t->single_cmd[i]->before_sep == 'h' )
		{
			i++;
			continue ;
		}
		forens_printf("Multiple_cmd line 56 Current cmd = %s\n", t->single_cmd[i]->cmd);
		exec_export_unset_cd_in_parent(i,  t, env);
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
	close_files_and_wait(fd, t, exit_status);
		// flush_pipes(t);
	return ;
}

void	exec_export_unset_cd_in_parent(
		int i,  struct t_pipes *t, t_list *env)
{
	int	redirec;

	redirec = 0;
	if (!t->single_cmd[i] || !t->single_cmd[i]->cmd)
		return ;
	while (t->single_cmd[redirec] && redirec < t->npipes)
	{
		if (t->single_cmd[redirec]->after_sep == 'p'
			|| t->single_cmd[redirec]->after_sep == 'g'
			|| t->single_cmd[redirec]->after_sep == 'a')
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
		else
			close_files(fd, t->npipes);
		just_execve(t->single_cmd[i], env, t);
	}
	if (t->single_cmd[i]->after_sep == 'g'
		|| t->single_cmd[i]->after_sep == 'a')
		output_append_execution(t, fd, i);
	else if (t->single_cmd[i]->after_sep == 'h')
	{	
		write(fd[i][1], t->single_cmd[i + 1]->args[0],
			ft_strlen(t->single_cmd[i + 1]->args[0]));
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
		free(t->single_cmd[i + 1]->args[0]);
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
		*exit_satus = WEXITSTATUS(forwait);
		// *exit_satus = WIFSIGNALED(forwait);
		forens_printf("cmd %d exection end exit status %d\n", i, *exit_satus);
		i++;
	}
	forens_printf("\n------------------------------------------\n");
	forens_printf("------------------------------------------\n");
	forens_printf("------------------------------------------\n");
	forens_printf("------------------------------------------\n\n\n");
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
}