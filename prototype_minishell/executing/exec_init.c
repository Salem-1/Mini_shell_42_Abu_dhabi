/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:51:40 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/25 04:59:04 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_operations(char *cmd, t_list *t_env)
{
	if (cmd && cmd_not_empty(cmd))
	{
		add_history(cmd);
		if (is_piped(cmd))
			exec_multiple_pipes(cmd, t_env);
		else
			execute_one_cmd(cmd, t_env);
		free(cmd);
	}
}