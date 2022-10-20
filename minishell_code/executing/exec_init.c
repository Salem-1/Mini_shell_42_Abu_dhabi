/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:51:40 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 07:09:40 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//remembre to lower the cmd before go into execution operations
int	execution_operations(char *cmd, t_list *t_env, int *exit_status)
{
	if (cmd && cmd_not_empty(cmd))
	{
		add_history(cmd);
		exec_multiple_pipes(cmd, t_env, exit_status);
		free(cmd);
	}
	return (*exit_status);
}