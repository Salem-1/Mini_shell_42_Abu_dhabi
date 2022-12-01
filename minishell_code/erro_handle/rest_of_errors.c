/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_of_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:07:52 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 11:08:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
