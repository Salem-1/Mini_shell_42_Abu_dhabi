/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/19 19:26:02 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stick_error_code_if_it__exists(char *cmd, t_list *head, t_smash_kit *s)
{
	search_for_unclosed_quote(cmd, s);
	if (head)
	{
		if (s->parse_error_code != 0)
			head->flag = s->parse_error_code;
		vis_smached_cmd(&head);
	}
}

void	search_for_unclosed_quote(char *cmd, t_smash_kit *s)
{
	s->i = 0;
	s->start = 0;
	s->end = 0;
	s->flag = '\0';
	while (cmd[s->i])
	{
		if (s->start == 0)
			set_flag_start_end_for_error_check(cmd, s);
		else
		{
			if (cmd[s->i] == s->flag)
			{
				s->end = 2;
				s->start = 0;
			}
		}
		s->i++;
	}
	if (s->end == 1)
		s->parse_error_code = 2;
}

void	set_flag_start_end_for_error_check(char *cmd, t_smash_kit *s)
{

	if (cmd[s->i] == '"')
		s->flag = '"';
	else if(cmd[s->i] == '\'')
		s->flag = '\'';
	if (cmd[s->i] == '\'' || cmd[s->i] == '"')
	{
		s->start = 1;
		s->end = 1;
	}
}