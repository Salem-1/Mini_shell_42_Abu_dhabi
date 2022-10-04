/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/04 06:36:14 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
void	spaces_smash(smash_kit *s, char *cmd, t_list *tmp, t_list **head)
{
	// is_redirection(s, cmd, head, s->i)
	//in each iteration check for the redirections 
	//if found fill cmd_node, then fill redirection
	//you can make something like redirection check that calls is redirection
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == ' ' && cmd[s->i + 1] && cmd[s->i + 1] != ' ')
		s->start = s->i + 1;
	else if (cmd[s->i] == ' ')
		;
	else if (cmd[s->i + 1] == ' ')
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start,
					s->end - s->start + 1), 'c');
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

void	double_qoute_smach(smash_kit *s, char *cmd, t_list *tmp, t_list **head)
{
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '"')
	{
		s->end = s->i ;
		tmp = fill_cmd_node(ft_substr(cmd, s->start, s->end - s->start + 1), 'd');
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

int	is_redirection(smash_kit *s,char *cmd, t_list **head, int i)
{
	if (cmd[i] == '|')
	{
		printf("should add the pipe\n");
		s->tmp = fill_cmd_node(ft_strdup("|"), 'p');
		ft_lstadd_back(head, s->tmp);
		return (1);
	}
	return (0);
}