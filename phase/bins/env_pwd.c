/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:11:08 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 20:10:32 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_env(t_list **env)
{
	vis_list(env, 'v');
}

void	exec_pwd()
{
	char	*current_path;

	current_path = malloc (sizeof(char) * 4089);
	current_path = getcwd(current_path, 4089);
	printf("%s\n", current_path);
	free(current_path);
}
