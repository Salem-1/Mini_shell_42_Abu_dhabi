/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:51:40 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 20:27:50 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execution_operations(char *cmd, t_list *t_env, int *exit_status)
{
	if (cmd)
	{
		if (cmd_not_empty(cmd))
		{
			add_history(cmd);
			*exit_status = signal_update_exit_status(exit_status);
			if (ft_strlen(cmd) <= 262144)
				exec_multiple_pipes(cmd, t_env, exit_status);
			else
			{
				free(cmd);
				err_printf("minishell: /bin/echo: Argument list too long\n");
				*exit_status = 1;
			}
		}
	}
	else
	{
		clean_env(t_env);
		exit(*exit_status);
	}
	return (*exit_status);
}

//getconf ARG_MAX for cmd length for mac is 262144