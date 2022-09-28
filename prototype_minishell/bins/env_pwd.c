/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:11:08 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/28 08:13:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_env(t_list **env)
{
	vis_list(env, 'v');
}

void	exec_pwd(t_list *env)
{
	char	*current_path;

	current_path = search_list(env, "PWD", 'p');
	printf("%s\n", current_path);
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

int	is_repeated(char *cmd, t_list **env)
{
	if (search_list(*env, cmd, 'e'))
		return (1);
	else
		return (0);
}
