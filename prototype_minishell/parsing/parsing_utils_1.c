/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 10:02:45 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_list(t_list *t_env, char *needle, char flag)
{
	t_list	*tmp;
	size_t	len;

	tmp = t_env;
	if (!t_env || !needle)
		return (NULL);
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], needle);
		if (!ft_strncmp(tmp->key_val[0], needle, len))
		{
			if (flag == 'p')
				return (tmp->key_val[1]);
			else
				return ("the var exists");
		}
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	length_of_larger_string(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}

int	is_piped(char *cmd)
{
	if (ft_strchr(cmd, '|') != NULL)
		return (1);
	return (0);
}