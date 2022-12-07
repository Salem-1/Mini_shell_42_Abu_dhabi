/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outliar_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:40:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 21:58:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	call_case 1 --> "hello" or 'hello' normal handle , take care for the '' or ""
	call_case 2 --> h"ello" or "hell"o or h"ell"o    , take care of unclosed quotes
	SURPRISE ......
	one more case
	case     3 --> 0"1"2"3"4"5"67'8'9"1"
					""" "
					" """
*/

char	*multiple_single_and_double_quotes(
		t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*merged_str;

	merged_str = figure_out_end_of_quote_and_fill_arg(
			s, cmd, flag, exit_status);
	if ((s->i + 1) >= s->cmd_len)
		return (merged_str);
	while (cmd[s->i + 1] == '\'' || cmd[s->i + 1] == '"')
	{
		s->i++;
		s->flag = cmd[s->i];
		s->start = s->i;
		merged_str = ft_expand_strjoin(merged_str,
				figure_out_end_of_quote_and_fill_arg(
					s, cmd, s->flag, exit_status));
	}
	return (merged_str);
}

//this is the source of the all evil
//check for throwing the error, then all the error cases
char	*figure_out_end_of_quote_and_fill_arg(
		t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*final_arg;
	int		call_case;

	final_arg = NULL;
	call_case = 0;
	call_case = decide_normal_or_outliar_fill(cmd, s, flag);
	if (call_case == 1)
		final_arg = fill_normal_quote_case(s, cmd, flag, exit_status);
	else if (call_case == 2)
		final_arg = fill_case_2(s, cmd, flag, exit_status);
	else if (call_case == 3)
		final_arg = fill_case_3(s, cmd, flag, exit_status);
	else
		s->parse_error_code = 2;
	return (final_arg);
}

int	decide_normal_or_outliar_fill(
	char *cmd, t_smash_kit *s, char flag)
{
	if (cmd[s->start] != flag)
	{
		return (3);
	}
	else if (cmd[s->i] == flag)
	{
		if (s->i == 0)
			s->i++;
		if (is_normal_quote_case(s, cmd))
			return (1);
		else
			return (2);
	}
	else
		return (0);
}

// if (!cmd[s->i + 1] || cmd[s->i + 1] == ' '
int	is_normal_quote_case(t_smash_kit *s, char *cmd)
{
	if (
		!cmd[s->i + 1]
		|| check_redirection(cmd, s->i + 1)
		|| cmd[s->i + 1] == '\'' || cmd[s->i + 1] == '"')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*fill_double_q(
	t_smash_kit *s, char **splitted_arg, char *final_arg, int *exit_status)
{
	int	i;

	i = 0;
	if (final_arg)
		free(final_arg);
	final_arg = NULL;
	while (splitted_arg[i])
	{
		final_arg = ft_expand_strjoin(
				final_arg, expand_var(s, splitted_arg[i], exit_status));
		i++;
	}
	if (splitted_arg)
		free(splitted_arg);
	return (final_arg);
}
