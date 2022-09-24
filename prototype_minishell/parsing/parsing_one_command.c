/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/23 06:32:54 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_command	*parse_one_cmd(char *command)
{
	t_parsed_command	*t;
	char					**split_command;

	t = malloc(sizeof( t_parsed_command));
	if (!t)
		return NULL;
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

char **get_path(t_list *t_env)
{
	char	**split_pathes;
	char	*bins_path;
	int		i;

	i = 0;
	bins_path = search_list(t_env, "PATH");
	// printf("bins in Path is = %s\n", bins_path);
	split_pathes = ft_split(bins_path, ':');
	return (split_pathes);
}
