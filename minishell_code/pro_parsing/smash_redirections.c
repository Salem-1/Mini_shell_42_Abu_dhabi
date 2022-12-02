/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smash_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 07:40:51 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_redirection(t_smash_kit *s, char *cmd, t_list **head, int i)
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

void	fill_in_out_app_hered(t_smash_kit *s, char *cmd, t_list **head, int i)
{
	if (cmd[i] == '>' )
	{
		if (cmd[i + 1] == '>')
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
