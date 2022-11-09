/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:21:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/09 07:03:28 by ahsalem          ###   ########.fr       */
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
	while (i < npipes )
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
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
// err_printf("in close files and wiat cmd %d execution end exit status %d\n", i, *exit_satus);
		i++;
	}
// 	//forens_printf("\n------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n");
// 	//forens_printf("------------------------------------------\n\n\n");
}


int	local_exec_cmd_spec(t_pipes *t)
{
	int		redirec;
	int		i;
	char	*parent_cmds[3] = {"export", "cd", "unset"};
	redirec = 0;
	i = 0;
	while (i < t->npipes)
	{
		redirec = 0;
		while (redirec < 3)
		{
			err_printf(" Seg , i = %d\n", i);
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