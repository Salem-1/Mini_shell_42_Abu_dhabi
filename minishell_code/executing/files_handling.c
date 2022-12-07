/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:21:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 11:02:33 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**open_pipes(int n, int **fd)
{
	int	i;

	i = 0;
	fd = ft_calloc(sizeof(int *), n);
	if (!fd)
		return (NULL);
	while (i < n)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		if (!fd[i])
		{
			free_split((void **)fd);
			return (NULL);
		}
		if (pipe(fd[i]) == -1)
		{
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
	while (i < npipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	close_files_and_wait(
		int **fd, struct t_pipes *t, int *exit_satus, int return_or_continue)
{
	int	forwait;
	int	i;

	i = 0;
	close_files(fd, t->npipes);
	if (return_or_continue == 3)
		return ;
	while (i < t->npipes)
	{
		wait(&forwait);
		*exit_satus = WEXITSTATUS(forwait);
		i++;
	}
}

int	local_exec_cmd_spec(t_pipes *t)
{
	int			redirec;
	int			i;
	static char	*parent_cmds[3] = {"export", "cd", "unset"};

	redirec = 0;
	i = 0;
	while (i < t->npipes)
	{
		redirec = 0;
		while (redirec < 3)
		{
			if (t->single_cmd[i])
			{
				if (!ft_strncmp(parent_cmds[redirec], t->single_cmd[i]->cmd, 7))
				{
					i = 0;
					return (1);
				}
			}
			redirec++;
		}
		i++;
	}
	return (0);
}
