/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:46:12 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 21:38:40 by ahsalem          ###   ########.fr       */
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
			printf("\nPress Enter to go back to minishell!");
		}
		g_ctr_c.exit_ctr_c = 1;
	}
}

void	init_signals(void)
{
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, SIG_IGN);
}
