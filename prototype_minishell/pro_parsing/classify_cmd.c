/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/13 22:00:39 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
//remember to handle this case "he hello"ho 
//remember to handle this case also 'how is is one sh'unk
void	spaces_smash(t_smash_kit *s, char *cmd, t_list **head, int *exit_status)
{
	char	*smashed_arg;

	smashed_arg = NULL;
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
		smashed_arg = expand_var(s, cmd, exit_status);
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, s->tmp);
		s->end = 0;
		s->flag = 'i';
	}
}


void	double_qoute_smash(t_smash_kit *s, char *cmd,
			t_list **head, int *exit_status)
{
	char	*smashed_arg;

	smashed_arg = NULL;
	if (s->i == s->start)
		s->i++;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '"')
	{
		//make outliar function to check the word write after the double quote
		while (cmd[s->i] != '"' || cmd[s->i] != ' ')
			s->i++;
		s->end = s->i ;
		smashed_arg = expand_var(s, cmd, exit_status);
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		//apply the expansion function inside the fillnode to 
		//join the new string with expanded values
		ft_lstadd_back(head, s->tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	if (s->i == s->start)
		s->i++;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '\'')
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start + 1,
					s->end - s->start -1 ),'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
