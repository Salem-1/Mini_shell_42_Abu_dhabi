/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_quote_cases.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:40:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 10:34:35 by ahsalem          ###   ########.fr       */
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
	int		quote_end;

	splitted_arg = NULL;
	final_arg = NULL;
	fetch_end = 1;
	quote_end = 0;
	forens_printf("\n\nCase 2\ns=%d,e=%d,i=%d \n", s->start, s->end, s->i);
	while (not_reched_end_2(cmd, s, fetch_end, &quote_end))
	{
		forens_printf("fetching end cmd[%d + %d] = <%c>, flag = %c\n",
			s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
		fetch_end++;
	}
	s->end = s->i + fetch_end;
	s->i += fetch_end - 1;
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	return (final_arg);
}

int	not_reched_end_2(char *cmd, t_smash_kit *s, int fetch_end, int *quote_end)
{
	if (cmd[s->i] == s->flag && *quote_end == 0)
		*quote_end = 1;
	else if (cmd[s->i] == s->flag && *quote_end == 1)
		*quote_end = 2;
	if (cmd[s->i + fetch_end] != '\0'
		&& !check_redirection(cmd, s->i + fetch_end)
		&& (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"'
		))
		return (1);
	else
	{
		forens_printf("\nreached end cmd[%d + %d] = <%c>, flag = %c",
			s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
		forens_printf(" start = %d\n\n", s-> start);
		return (0);
	}
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
	forens_printf("\n\nCase 3\ns=%d,e=%d,i=%d \n", s->start, s->end, s->i);
	if (s->start == 0)
		s->i--;
	while (not_reched_end_3(cmd, s, fetch_end))
	{
		forens_printf("fetching end cmd[%d + %d] = <%c>, flag = %c\n",
			s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
		fetch_end++;
	}
	s->end = s->i + fetch_end;
	s->i += fetch_end - 1;
	if(s->start == 0)
		s->i++;
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	return (final_arg);
}

int	not_reched_end_3(char *cmd, t_smash_kit *s, int fetch_end)
{
	if (cmd[s->i + fetch_end] != '\0'
		&& !check_redirection(cmd, s->i + fetch_end)
		&& (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"')
		&& !(s->start == 0 && cmd[s->i + fetch_end] == ' '))
		return (1);
	else
	{
		if ((s->start == 0)
			&& (cmd[s->i + fetch_end + 1] != '\0'
				&& !check_redirection(cmd, s->i + fetch_end)
				&& (cmd[s->i + fetch_end + 1] != '\'')
				&& (cmd[s->i + fetch_end + 1] != '"')
				&& ((cmd[s->i + fetch_end + 1] != ' ')
					&& ((cmd[s->i + fetch_end ] != ' ')))))
		{
			return (1);
		}
		forens_printf("\nreached end cmd[%d + %d] = <%c>, flag = %c",
			s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
		forens_printf(" start = %d\n\n", s-> start);
		return (0);
	}
}

char	*fill_normal_quote_case(t_smash_kit *s,
	char *cmd, char flag, int *exit_status)
{
	char	*final_arg;

	s->end = s->i;
	forens_printf("Case 1 Filling normal quote,");
	forens_printf(" cmd = %s, start = %d, end = %d\n",
		cmd, s->start, s->end);
	if (s->start == s->end)
		s->end++;
	final_arg = ft_substr(cmd, s->start + 1, s->end - s->start - 1);
	forens_printf("final_arg before expand = %s, start = %d, end = %d\n",
		final_arg, s->start, s->end);
	if (final_arg[0] != '\0')
	{
		if (flag == '"')
			final_arg = expand_var(s, final_arg, exit_status);
	}
	forens_printf("final_arg after filling normal case");
	forens_printf(" = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
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
		forens_printf("splitted_arg = %s\n", splitted_arg[i]);
		final_arg = ft_expand_strjoin(final_arg, splitted_arg[i]);
		i++;
	}
	if (splitted_arg)
		free(splitted_arg);
	return (final_arg);
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
