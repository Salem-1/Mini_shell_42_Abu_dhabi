/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/06 20:45:06 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
void	spaces_smash(t_smash_kit *s, char *cmd, t_list *tmp, t_list **head)
{
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == ' ' && cmd[s->i + 1] && cmd[s->i + 1] != ' ')
		s->start = s->i + 1;
	else if (cmd[s->i] == ' ')
		;
	else if (cmd[s->i + 1] == ' ' || check_redirection(cmd, s->i + 1)
		|| !cmd[s->i + 1])
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,s->end - s->start + 1)
				, 'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

void	double_qoute_smash(t_smash_kit *s, char *cmd, t_list *tmp,
			t_list **head)
{
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '"')
	{
		s->end = s->i ;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,
					s->end - s->start + 1), 'd');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '\'')
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,
					s->end - s->start + 1),'s');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
