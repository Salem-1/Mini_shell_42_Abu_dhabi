/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/24 13:17:15 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_command	*parse_one_cmd(char *command)
{
	t_parsed_command	*t;
	char				**split_command;

	t = malloc(sizeof(t_parsed_command));
	if (!t)
		return (NULL);
	split_command = ft_split(command, ' ');
	if (!split_command)
	{
		free(t);
		return (NULL);
	}
	t->cmd = split_command[0];
	if (split_command[0][0] == '/')
		t->path = 'a';
	else
		t->path = 'r';
	t->args = split_command;
	t->env = NULL;
	t->splitted_cmd = split_command;
	return (t);
}

char	**get_path(t_list *t_env)
{
	char	**split_pathes;
	char	*bins_path;

	bins_path = search_list(t_env, "PATH");
	split_pathes = ft_split(bins_path, ':');
	return (split_pathes);
}

int	cmd_not_empty(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (!ft_isspace(&cmd[i]))
			return (1);
		i++;
	}
	return (0);
}
