/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outliar_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:40:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/06 20:14:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	cases to handle:
	---------------
	"ls  hello"
	"l"s
	l"s"
	''ec"h"o
	"ls"""
//single as double but without expansion
	errors:
	"ls
	ls"
	"
	l"s

*/

/*
	call_case 1 --> "hello" or 'hello' normal handle , take care for the '' or ""
	call_case 2 --> h"ello" or "hell"o or h"ell"o    , take care of unclosed quotes
	SURPRISE ......
	one more case
	case     3 --> 0"1"2"3"4"5"67'8'9"1"
					""" "
					" """
*/

char	*multiple_single_and_double_quotes(t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*merged_str;
forens_printf("\nMultiple single and double quote gen\n cmd = <%s>, flag = %c, start = %d, end = %d, i = %d\n\n", cmd, flag, s->start, s->end, s->i);
	merged_str = figure_out_end_of_quote_and_fill_arg(s, cmd, flag, exit_status);
	while (cmd[s->i + 1] == '\'' || cmd[s->i + 1] == '"')
	{
		s->i++;
		s->flag = cmd[s->i];
		s->start = s->i;
forens_printf("\nLooping Multiple single and double quote gen\n merge_str = <%s>, flag = %c, start = %d, end = %d, i = %d\n\n", merged_str, flag, s->start, s->end, s->i);
		merged_str = ft_expand_strjoin(merged_str,
				figure_out_end_of_quote_and_fill_arg(
					s, cmd, s->flag, exit_status
					)
				);
	}
forens_printf("\nExiting Multiple single and double quote gen\n merged_str = <%s>, flag = %c, start = %d, end = %d, i = %d\n\n", merged_str, flag, s->start, s->end, s->i);

	return (merged_str);
}

char	*figure_out_end_of_quote_and_fill_arg(
		t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*final_arg;
	int		call_case;

// forens_printf("\nEntering figure out end of quote cmd = <%s>, flag = %c, start = %d, end = %d, i = %d\n", cmd, flag, s->start, s->end, s->i);
	final_arg = NULL;
	call_case = 0;
	if (cmd[s->start] != flag)
	{
forens_printf("Calling case 2 string don't start with quote, start = %d, end = %d\n",  s->start, s->end);
		call_case = 2;
	}
	else if (cmd[s->i] == flag)
	{
		if (s->i == 0)
			s->i++;
		// if (!cmd[s->i + 1] || cmd[s->i + 1] == ' '
		if (!cmd[s->i + 1]
			|| check_redirection(cmd, s->i + 1)
			|| cmd[s->i + 1] == '\'' || cmd[s->i + 1] == '"')
		{
			// if (cmd[s->i + 1] == ' ' && cmd[s->i - 1] != s->flag)
			// 	s->i += 2;
forens_printf("calling case 1 main cmd[%d] = %c  cmd[%d] = %c , start = %d, flag = %c\n", s->i, cmd[s->i],s->i + 1, cmd[s->i + 1], s->start, s->flag);
			call_case = 1;
		}
		else
		{
			call_case = 2;
forens_printf("calling case 2 main cmd[%d] = %c  cmd[%d] = %c , start = %d, flag = %c\n", s->i, cmd[s->i],s->i + 1, cmd[s->i + 1], s->start, s->flag);
		}
	}
	if (call_case == 1)
		final_arg = fill_normal_quote_case(s, cmd, flag, exit_status);
	else if (call_case == 2)
		final_arg = fill_outliar_quote_by_split_expand(s, cmd, flag, exit_status);
	else
		s->parse_error_code = 2;
	forens_printf("After handling all quotes arg = #%s#\n", final_arg);
	return (final_arg);
}

char	*fill_normal_quote_case(t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*final_arg;

	s->end = s->i;
	forens_printf("Case 1 Filling normal quote, cmd = %s, start = %d, end = %d\n", cmd, s->start, s->end);
	if (s->start == s->end)
		s->end++;
	final_arg = ft_substr(cmd, s->start + 1, s->end - s->start - 1);
	forens_printf("final_arg before expand = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
	if (final_arg[0] != '\0')
	{
		if (flag == '"')
			final_arg = expand_var(s, final_arg, exit_status);
	}
	forens_printf("final_arg after filling normal case = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
	return (final_arg);
}

//fetch_end  figure out wher the arg ends;
char	*fill_outliar_quote_by_split_expand(t_smash_kit *s, char *cmd, char flag, int *exit_status)
{
	char	*final_arg;
	char	**splitted_arg;
	int		fetch_end;

	splitted_arg = NULL;
	(void)exit_status;
	final_arg = NULL;
	fetch_end = 1;
	forens_printf("Case 2 FIll outliar quote, flag = %c\n", flag);
	forens_printf("cmd before expand = %s, start = %d, end = %d, i = %d\n", cmd, s->start, s->end, s->i);

	// while (cmd[s->i + fetch_end] != '\0' && !check_redirection(cmd, s->i + fetch_end)
	// 	&& (cmd[s->i + fetch_end] != ' ') && (cmd[s->i + fetch_end] != '\'')
	// 	&& (cmd[s->i + fetch_end] != '"'))
	while (cmd[s->i + fetch_end] != '\0' && !check_redirection(cmd, s->i + fetch_end)
		 && (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"'))
	{
forens_printf("cmd[%d + %d] = %c\n", s->i, fetch_end, cmd[s->i + fetch_end]);
		fetch_end++;

	}
	s->end = s->i + fetch_end;
	s->i += fetch_end - 1;
	final_arg = ft_substr(cmd, s->start, s->end - s->start);
	forens_printf("final_arg after substr outliar case  = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
	splitted_arg = ft_split(final_arg, flag);
	if (flag == '"')
		final_arg = outliar_double_with_expand(s, splitted_arg, final_arg,exit_status);
	else
		final_arg = outliar_single_fill(splitted_arg, final_arg);
	forens_printf("End fill outliar case  = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
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

char	*outliar_double_with_expand(
	t_smash_kit *s, char **splitted_arg, char *final_arg, int *exit_status)
{
	int	i;

	i = 0;
	if (final_arg)
		free(final_arg);
	final_arg = NULL;
	while (splitted_arg[i])
	{
		final_arg = ft_expand_strjoin(final_arg, expand_var(s, splitted_arg[i], exit_status));
		i++;
	}
	if (splitted_arg)
		free(splitted_arg);
	return (final_arg);
}

char	*handle_outliar_remain_after_quote(t_smash_kit *s, char flag, char *cmd, int *exit_status)
{
	char	*remain;
	int		i;

	remain = NULL;
	i = 1;
	//this is a wrong function
	forens_printf("#####################################\n");
	forens_printf("outliar begining cmd = %s, remain = %s\n", cmd, remain);
	while (cmd[i] && (cmd[i] != ' ' || check_redirection(cmd, i)))
	{
		if (cmd[i] == flag)
		{
forens_printf("throw error in classifycmd will exit inshalla in a clean way parse error_type 'p', this is an unclosed new quote`\n");
			s->parse_error_code = 2;
		}
		i++;
	}
	forens_printf("outliar after loop cmd = %s, remain = %s\n", cmd, remain);
	if (i == 1)
	{
forens_printf("no chars after quote inside outliar quotes, i = 1 error line 78\n");
	forens_printf("outliar i == 1 case cmd = %s, remain = %s\n", cmd, remain);
	forens_printf("#####################################\n");
		return (NULL);
	}
	else
	{
		s->start = 0;
		s->i = i + s->end ;
		s->end = i;
		if (flag == '"')
			remain = expand_var(s, cmd, exit_status);
		else if (flag == '\'')
			remain = ft_substr(cmd, s->start + 1, s->end - s->start -1);
		s->start = s->end;
	forens_printf("outliar at the end case cmd = %s, remain = %s, s->i = %d\n", cmd, remain, s->i);
	forens_printf("#####################################\n");
		return (remain);
	}
}