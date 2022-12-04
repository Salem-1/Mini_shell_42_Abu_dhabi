/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 20:39:09 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static int		exit_status;
	char			*cmd;
	t_list			*t_env;

	g_ctr_c.g_inside_heredoc = 0;
	g_ctr_c.exit_ctr_c = 0;
	forens_printf("\n\n\n");
	exit_status = 0;
	cmd = NULL;
	t_env = NULL;
	if ((argc > 1 && argv) || (!envp))
		return (0);
	init_signals();
	t_env = parse_env(envp, t_env);
	while (1)
	{
		cmd = readline("minishell $> ");
		execution_operations(cmd, t_env, &exit_status);
	}
}
