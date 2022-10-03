/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/03 19:53:07 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for empty and spaces only cmds not to execute or add to his
int		exit_shell = 0;

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*cmd;
	t_list				*t_env;
	t_list				*tmp;

	sa.sa_handler = &handle_signals;
	cmd = NULL;
	t_env = NULL;
	tmp = NULL;
	if ((argc > 1 && argv) || (!envp))
	{
		printf("Error!\n./minishell  cannot take arguments\n");
		return (0);
	}
	t_env = parse_env(envp, t_env);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		cmd = readline("minishell $> ");
		if (cmd == NULL)
			return (0);
		// tmp = cmd_smasher(cmd, &tmp);
		printf("visualizing the cmd\n");
		printf("visualization finished\n");
		if (execution_operations(cmd, t_env, exit_shell) == 1)
			return (0);
		// free_split((void **)tmp);
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
		// rl_clear_history();
	}
	else if (sig == SIGQUIT)
	{
		//printf("minishel $> ");
		printf( "%c[K", ESC );
		rl_on_new_line ();
		rl_redisplay();
		//rl_replace_line("", 0);
	}

}