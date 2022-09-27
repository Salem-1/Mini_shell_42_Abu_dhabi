/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:11:08 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 11:04:59 by ahsalem          ###   ########.fr       */
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

int	is_repeated(char *cmd, t_list **env)
{
	if (search_list(*env, cmd, 'e'))
		return (1);
	else
		return (0);
}