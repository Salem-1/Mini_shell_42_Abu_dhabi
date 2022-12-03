/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:46:12 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 07:57:25 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		exit(130);
	}
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_inside_heredoc)
		{
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line ();
			rl_redisplay();
		}
		else
		{
			g_inside_heredoc = 2;
			rl_replace_line("", 0);
			printf("minishell $>");
			// rl_on_new_line ();
			// rl_redisplay();
		}
	}
}

void	init_signals(void)
{
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, SIG_IGN);
}
