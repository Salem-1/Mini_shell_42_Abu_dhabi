/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 14:48:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(struct t_pipes *all_cmds, int exit_shell)
{
	char	**args;
	int		len;

	args = all_cmds->single_cmd[0]->args;
	printf("should exit with code%d\n", exit_shell);
	// flush_pipes(all_cmds);
	len = length_of_larger_string(args[0], "exit");
	if (all_cmds->npipes == 1 && !ft_strncmp(args[0], "exit", len) && !args[1])
	{
		//remember to flush pipes
		exit(249);
	}
	//flush pipes
	exit(exit_shell);
	printf("%d", exit_shell);
}
