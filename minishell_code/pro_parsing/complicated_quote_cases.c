/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_quote_cases.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:40:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 21:56:41 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fetch_end  figure out wher the arg ends;
char	*fill_case_2(t_smash_kit *s,
	char *cmd, char flag, int *exit_status)
{
	int		fetch_end;
	char	*final_arg;
	char	**splitted_arg;

	splitted_arg = NULL;
	final_arg = NULL;
	fetch_end = 1;
	if (s->start == 0 || check_redirection(cmd, s->end))
		s->i--;
	fetch_end = find_end_in_case_2_abstract(cmd, s, fetch_end);
	s->last_end = s->end;
	s->end = s->i + fetch_end;
	s->i += fetch_end - 1;
	if (cmd[s->start == s->flag] && cmd[s->end] == s->flag
		&& (s->start == 0 || check_redirection(cmd, s->last_end)))
		return (fixing_edge_quote_start_case_2(s, cmd, flag, exit_status));
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	return (final_arg);
}

int	find_end_in_case_2_abstract(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	while (not_reched_end_2(cmd, s, fetch_end))
	{
		fetch_end++;
	}
	return (fetch_end);
}

char	*fill_case_3(t_smash_kit *s,
			char *cmd, char flag, int *exit_status)
{
	int		fetch_end;
	char	*final_arg;
	char	**splitted_arg;

	splitted_arg = NULL;
	final_arg = NULL;
	fetch_end = 1;
	if (s->start == 0 || check_redirection(cmd, s->end))
		s->i--;
	while (not_reched_end_3(cmd, s, fetch_end))
		fetch_end++;
	s->last_end = s->end;
	s->end = s->i + fetch_end;
	s->i += fetch_end - 1;
	if (s->start == 0 || check_redirection(cmd, s->last_end))
		s->i++;
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	return (final_arg);
}

char	*fill_normal_quote_case(t_smash_kit *s,
	char *cmd, char flag, int *exit_status)
{
	char	*final_arg;

	s->end = s->i;
	if (s->start == s->end)
		s->end++;
	final_arg = ft_substr(cmd, s->start + 1, s->end - s->start - 1);
	if (final_arg[0] != '\0')
	{
		if (flag == '"')
			final_arg = expand_var(s, final_arg, exit_status);
	}
	return (final_arg);
}

char	*outliar_single_fill(char **splitted_arg, char *final_arg)
{
	int	i;

	i = 0;
	if (final_arg)
		free(final_arg);
	final_arg = NULL;
	while (splitted_arg[i])
	{
		final_arg = ft_expand_strjoin(final_arg, splitted_arg[i]);
		i++;
	}
	if (splitted_arg)
		free(splitted_arg);
	return (final_arg);
}
