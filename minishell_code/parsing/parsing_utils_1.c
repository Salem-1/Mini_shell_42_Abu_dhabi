/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 13:31:42 by ahsalem          ###   ########.fr       */
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

int	count_args_in_cmd(t_list *smashed_cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = smashed_cmd;
	if (!tmp)
		return (0);
	while (tmp->flag != 'c')
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->flag == 'c')
			i++;
		else
		{
			return (i + count_outliar_redire(tmp, -1));
		}
		tmp = tmp->next;
	}
	return (i);
}

int	count_cmds(t_list *cmd)
{
	t_list	*tmp;
	int		n;
	//forens_printf("inside count cmds\n");
	n = 1;
	tmp = cmd;
	while (tmp)
	{
		//forens_printf("flag = %c arg = ~%s~,\n", tmp->flag, (char *)tmp->content);
		if (tmp->flag != 'c')
			n++;
		tmp = tmp->next;
	}
	return (n);
}

