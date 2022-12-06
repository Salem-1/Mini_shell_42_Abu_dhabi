/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:22:13 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 21:53:09 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_reched_end_2(char *cmd, t_smash_kit *s, int fetch_end)
{
	if (cmd[s->i + fetch_end] != '\0'
		&& !check_redirection(cmd, s->i + fetch_end)
		&& (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"'
		))
		return (1);
	else
		return (0);
}

char	*fixing_edge_quote_start_case_2(t_smash_kit *s,
			char *cmd, char flag, int *exit_status)
{
	int	fetch_end;

	fetch_end = 1;
	if ((cmd[s->end + 1] != '\0'
			&& !check_redirection(cmd, s->end + 1)
			&& cmd[s->end + 1] != ' '
			&& (cmd[s->end + 1] != '\'')
			&& (cmd[s->end + 1] != '"')))
	{
		s->i = s->end;
		fetch_end = special_find_end_in_case_2_abstract(cmd, s, fetch_end);
		s->end = s->i + fetch_end;
		s->i += fetch_end - 1;
		return (special_special_start_case_2(s, cmd, flag, exit_status));
	}
	else
	{
		s->i++;
		return (fill_normal_quote_case(s, cmd, flag, exit_status));
	}
}

int	special_not_reched_end_2(char *cmd, t_smash_kit *s, int fetch_end)
{
	if (cmd[s->i + fetch_end] != '\0'
		&& !check_redirection(cmd, s->i + fetch_end)
		&& (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"')
		&& (cmd[s->i + fetch_end] != ' '))
		return (1);
	else
		return (0);
}

int	special_find_end_in_case_2_abstract(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	while (special_not_reched_end_2(cmd, s, fetch_end))
		fetch_end++;
	return (fetch_end);
}

char	*special_special_start_case_2(t_smash_kit *s,
	char *cmd, char flag, int *exit_status)
{
	char	*final_arg;
	char	**splitted_arg;

	splitted_arg = NULL;
	final_arg = NULL;
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	return (final_arg);
}
