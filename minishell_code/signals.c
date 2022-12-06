/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:46:12 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 22:54:59 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctr_d_in_heredoc(char *line)
{
	if (line == NULL)
	{
		write(1, "\n", 2);
		return (1);
	}
	return (0);
}

int	ctr_c_in_heredoc(t_pipes *t, char *filled_heredoc, char *line, int i)
{
	if (g_ctr_c.g_inside_heredoc == 2)
	{
		g_ctr_c.g_inside_heredoc = 0;
		save_heredoc_in_file_and_free_line(line, i, t, filled_heredoc);
		return (1);
	}
	else
		return (0);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_ctr_c.g_inside_heredoc)
		{
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line ();
			rl_redisplay();
		}
		else
		{
			g_ctr_c.g_inside_heredoc = 2;
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line ();
			rl_redisplay();
		}
		g_ctr_c.exit_ctr_c = 1;
	}
}

void	init_signals(void)
{
	g_ctr_c.g_inside_heredoc = 0;
	g_ctr_c.exit_ctr_c = 0;
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

int	signal_update_exit_status(int *exit_status)
{
	if (g_ctr_c.exit_ctr_c == 1)
	{
		g_ctr_c.exit_ctr_c = 0;
		if (*exit_status == 0)
			return (1);
	}
	return (*exit_status);
}
