/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/05 13:55:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
void	spaces_smash(smash_kit *s, char *cmd, t_list *tmp, t_list **head)
{
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == ' ' && cmd[s->i + 1] && cmd[s->i + 1] != ' ')
		s->start = s->i + 1;
	else if (cmd[s->i] == ' ')
		;
	else if (cmd[s->i + 1] == ' ' || check_redirection(cmd, s->i + 1))
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,s->end - s->start + 1)
				, 'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
	if (!cmd[s->i + 1])
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,
					s->end - s->start + 1), 'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

void	double_qoute_smash(smash_kit *s, char *cmd, t_list *tmp, t_list **head)
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

void	single_qoute_smach(smash_kit *s, char *cmd, t_list *tmp, t_list **head)
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

int	fill_redirection(smash_kit *s,char *cmd, t_list **head, int i)
{
	if (cmd[i] == '|')
	{
		s->tmp = fill_cmd_node(ft_strdup("|"), 'p');
		ft_lstadd_back(head, s->tmp);
	}
	if (cmd[i] == '>' || cmd[i] == '<')
		fill_in_out_app_hered(s, cmd, head, i);
	s->flag = 'i';
	return (0);
}

int	check_redirection(char *cmd, int i)
{
	if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<' )
		return (1);
	return (0);
}

void	fill_in_out_app_hered(smash_kit *s,char *cmd, t_list **head, int i)
{
	if (cmd[i] == '>' )
	{
		if (cmd[i+1] == '>')
		{
			s->tmp = fill_cmd_node(ft_strdup(">>"), 'a');
			s->i++;
		}
		else
			s->tmp = fill_cmd_node(ft_strdup(">"), 'g');
		ft_lstadd_back(head, s->tmp);
	}
	else if (cmd[i] == '<' )
	{
		if (cmd[i + 1] == '<')
		{
			s->tmp = fill_cmd_node(ft_strdup("<<"), 'h');
			s->i++;
		}
		else
			s->tmp = fill_cmd_node(ft_strdup("<"), 't');
		ft_lstadd_back(head, s->tmp);
	}
}