/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:19:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/09 00:48:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_parsed_command	*single_cmd)
{
	free_split((void **)single_cmd->args);
	single_cmd->args = NULL;
	free(single_cmd);
	single_cmd = NULL;
}

void	flush_pipes(t_pipes	*t)
{
	int	i;
	i = 0;
	if (!t)
		return ;
	// clean_env(t->env);
	if (t->single_cmd)
	{
		while (t->single_cmd[i])
		{
			free_cmd(t->single_cmd[i]);
			i++;
		}
		free(t->single_cmd[i]);
		free(t->single_cmd);
	}
	free_fd(t);
	free(t);
}

void	free_fd(t_pipes *t)
{
	int	i;

	i = 0;
	if (!t || !t->fd)
		return ;
	while (i < t->npipes)
	{
		free(t->fd[i]);
		i++;
	}
	free(t->fd);
}

void	clean_env(t_list *env)
{
	if (!env)
		return ;
	ft_lstclear(&env, del);
	env = NULL;
}

void	freedom(char *cmd, t_list *env, t_list *smashed_cmd)
{
	if (cmd)
		free(cmd);
	clean_env(env);
	clean_env(smashed_cmd);
	exit(0);
}
