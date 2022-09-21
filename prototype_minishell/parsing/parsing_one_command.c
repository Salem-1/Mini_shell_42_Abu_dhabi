/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/21 11:36:59 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_command	*parse_one_cmd(char *command, char **envp)
{
	struct t_parsed_command	*t;
	char					**split_command;

	t = malloc(sizeof(struct t_parsed_command));
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
	envp = (void *)envp;
	return (t);
}

void	free_cmd(struct t_parsed_command	*t)
{
	int	i;

	i = 0;
	while (t->splitted_cmd[i])
	{
		free(t->splitted_cmd[i++]);
	}
	free(t);
}

char **get_path(char **envp)
{
	char	**split_env;
	char	*bins_path;
	int		i;

	i = 0;
	bins_path = search_split(envp, "PATH");
	split_env = ft_split(bins_path, ':');
	return (split_env);
}

char *search_split(char **splitted_haystack, char *needle)
{
	char	**tmp_split;
	int		i;
	char	*value;
	size_t	len;

	value = NULL;
	tmp_split = NULL;
	i = 0;
	if (!splitted_haystack || !needle)
		return (NULL);
	while (splitted_haystack[i])
	{
		tmp_split = ft_split(splitted_haystack[i], '=');
		if (!tmp_split)
			return (NULL);
		len = length_of_larger_string(tmp_split[0], needle);
		if (ft_strncmp(tmp_split[0], needle, len))
		{
			value = ft_strdup(tmp_split[1]);
			free_split(tmp_split);
			return (value);
		}
		free_split(tmp_split);
	}
	return (NULL);
}
