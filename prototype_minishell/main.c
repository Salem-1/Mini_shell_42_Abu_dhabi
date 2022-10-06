/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/06 19:09:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	int					exit_shell;
	char				*cmd;
	t_list				*t_env;
	t_pipes				*test;

	exit_shell = 0;
	sa.sa_handler = &handle_signals;
	cmd = NULL;
	t_env = NULL;
	if ((argc > 1 && argv) || (!envp))
		return (0);
	t_env = parse_env(envp, t_env);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		cmd = readline("minishell $> ");
		if (cmd == NULL)
			return (0);
		test = parsing_piped_cmd(cmd);
		// if (execution_operations(cmd, t_env, exit_shell) == 1)
		// 	return (0);
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
	else if (sig == SIGQUIT)
	{
		printf( "%c[K", ESC );
		rl_on_new_line ();
		rl_redisplay();
	}

}