/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 21:55:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
//handle 'unclosed quote
//remember to handle this case "he hello"ho 
//remember to handle this case also 'how is is one sh'unk

void	spaces_smash(t_smash_kit *s, char *cmd, t_list **head, int *exit_status)
{
	char	*smashed_arg;

	smashed_arg = NULL;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '"')
		s->flag = '"';
	else if (cmd[s->i] == '\'')
		s->flag = '\'';
	if (cmd[s->i] == ' ' && cmd[s->i + 1] && cmd[s->i + 1] != ' ')
		s->start = s->i + 1;
	else if (cmd[s->i] == ' ')
		;
	else if ((s->flag == 's' && (cmd[s->i + 1] == ' '
				|| (check_redirection(cmd, s->i + 1))))
		|| ((s->i + 1) >= s->cmd_len))
	{
		filling_normal_spaced_word(
			s, smashed_arg, head, exit_status);
	}
}

void	filling_normal_spaced_word(
		t_smash_kit *s, char *smashed_arg, t_list **head, int *exit_status)
{
	s->end = s->i;
	smashed_arg = ft_substr(s->cmd, s->start, s->end - s->start + 1);
	smashed_arg = expand_var(s, smashed_arg, exit_status);
	if (!(!smashed_arg[0] && s->cmd[0]))
	{
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, s->tmp);
	}
	else
		free(smashed_arg);
	s->flag = 'i';
}

void	double_qoute_smash(t_smash_kit *s, char *cmd,
			t_list **head, int *exit_status)
{
	char	*smashed_arg;

	smashed_arg = NULL;
	if (s->i == s->start)
		s->i++;
	if (cmd[s->i] != '"' && ((s->i + 1) >= s->cmd_len))
	{
		s->parse_error_code = 2;
	}
	else if (cmd[s->i] == '"')
	{
		smashed_arg = multiple_single_and_double_quotes(
				s, cmd, '"', exit_status);
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, s->tmp);
		s->flag = 'i';
	}
}

void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	char	*smashed_arg;
	int		exit_code;

	exit_code = 0;
	smashed_arg = NULL;
	if (s->i == s->start)
		s->i++;
	if (cmd[s->i] != '\'' && ((s->i + 1) >= s->cmd_len))
	{
		s->parse_error_code = 2;
	}
	if (cmd[s->i] == '\'' || ((cmd[s->i] != '\''
				&& ((s->i + 1) >= s->cmd_len))))
	{
		smashed_arg = multiple_single_and_double_quotes(
				s, cmd, '\'', &exit_code);
		tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, tmp);
		s->flag = 'i';
	}
}
