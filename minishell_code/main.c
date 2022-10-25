/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/25 22:07:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <time.h>

int	main(int argc, char **argv, char **envp)
{
	static int			exit_status;
	char				*cmd;
	t_list				*t_env;

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
		if (cmd == NULL)
			return (0);
		if (execution_operations(cmd, t_env, &exit_status) == 249)
			return (0);
	}
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line ();
		rl_redisplay();
	}
}

void	init_signals()
{
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, SIG_IGN);
}