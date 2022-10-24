/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 13:31:42 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
//handle 'unclosed quote
//remember to handle this case "he hello"ho 
//remember to handle this case also 'how is is one sh'unk


//unfortuntely will need to map the whole double and single quote parsing process
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
	else if (cmd[s->i + 1] == ' ' || check_redirection(cmd, s->i + 1)
		|| !cmd[s->i + 1])
	{
		s->end = s->i;
		smashed_arg = ft_substr(cmd, s->start, s->end - s->start + 1);
//forens_printf("space_smash, smashed_arg = %s, start = %d, end = %d\n", smashed_arg, s->start, s->end);
		smashed_arg = expand_var(s, smashed_arg, exit_status);
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
	if (cmd[s->i] != '"' && !cmd[s->i + 1])
	{
		//forens_printf("Unclose \" double quote, throwing an error\n");
		s->parse_error_code = 2;
	}
	else if (cmd[s->i] == '"')
	{
		//forens_printf("before cleaning arg = <%s>, start = %d i = %d\n", cmd, s->start, s->i);
		smashed_arg = figure_out_end_of_quote_and_fill_arg(
						s, cmd, '"', exit_status);
		//forens_printf("filling node with ~%s~\n", smashed_arg);
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, s->tmp);
		s->end = 0;
		s->flag = 'i';
	}
}



void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	char	*smashed_arg;
	int		exit_code;

	exit_code = 0;
//forens_printf("check for single quote <%c>\n", cmd[s->i]);
	smashed_arg = NULL;
	if (s->i == s->start)
		s->i++;
	if (cmd[s->i] != '\'' && !cmd[s->i + 1])
	{
		//forens_printf("Unclose ' single quote, throwing an error\n");
		s->parse_error_code = 2;
		// return ;
	}
	if (cmd[s->i] == '\'' || ((cmd[s->i] != '\'' && !cmd[s->i + 1])))
	{
		//forens_printf("before cleaning arg = <%s>, start = %d i = %d\n", cmd, s->start, s->i);
		smashed_arg = figure_out_end_of_quote_and_fill_arg(
						s, cmd, '\'', &exit_code);
		//forens_printf("filling node with ~%s~\n", smashed_arg);
		tmp = fill_cmd_node(smashed_arg,'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
