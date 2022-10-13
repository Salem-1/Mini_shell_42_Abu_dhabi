/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:51:40 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/13 20:51:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//remembre to lower the cmd before go into execution operations
int	execution_operations(char *cmd, t_list *t_env, int *exit_status)
{
	int	exec_success;

	exec_success = 0;
	if (cmd && cmd_not_empty(cmd))
	{
		add_history(cmd);
		exec_multiple_pipes(cmd, t_env, exit_status);
		free(cmd);
		if (exec_success == 1)
			return (1);
	}
	return (exec_success);
}