/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:39:54 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 09:40:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_export_arg(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])
				|| str[i] == '_' || str[i] == '='))
			return (0);
			i++;
	}
	return (1);
}

int	find_msize(char *cmd)
{
	int	m_size;
	int	i;

	m_size = 2;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			m_size = 3;
			break ;
		}
		i++;
	}
	return (m_size);
}
