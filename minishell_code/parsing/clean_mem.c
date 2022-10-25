/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:19:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/25 22:08:00 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_parsed_command	*t)
{
	int	i;

	i = 0;
	while (t->args[i])
	{
		free(t->args[i]);
		i++;
	}
	// free(t->splitted_cmd[i]);	i = 0;
	free_split((void **)t->args);
	free(t);
}

void	flush_pipes(t_pipes	*t)
{
	int	i;

	i = 0;
	while (t->single_cmd[i])
	{
		free_cmd(t->single_cmd[i]);
		i++;
	}
	// if (t->single_cmd[i])
	// 	free_cmd(t->single_cmd[i]);
	if (t->single_cmd)
		free(t->single_cmd);
	if (t)
		free(t);
}

// void	clear_env(t_list *env)
// {
	
// }