/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/15 12:57:41 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <time.h>

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	static int			exit_status;
	char				*cmd;
	t_list				*t_env;
	
time_t t = time(NULL);
forens_printf("-----------------------------------------------------------\n");
forens_printf("Session start: %s\n\n\n", ctime(&t));
	exit_status = 0;
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
forens_printf("%s\n\n", cmd);
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
	else if (sig == SIGQUIT)
	{
		printf( "%c[K", ESC );
		rl_on_new_line ();
		rl_redisplay();
	}

}

