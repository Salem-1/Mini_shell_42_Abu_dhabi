/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:51:40 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 21:42:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execution_operations(char *cmd, t_list *t_env, int exit_shell)
{
	int	exec_success;

	exec_success = 0;
	if (cmd && cmd_not_empty(cmd))
	{
		add_history(cmd);
		if (is_piped(cmd))
			exec_multiple_pipes(cmd, t_env);
		else
			exec_success = execute_one_cmd(cmd, t_env, exit_shell);
		free(cmd);
		if (exec_success == 1)
			return (1);
	}
	return (exec_success);
}