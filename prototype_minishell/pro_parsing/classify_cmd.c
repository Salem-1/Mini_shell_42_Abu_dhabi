/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 01:35:14 by ahsalem          ###   ########.fr       */
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
		s->end = s->i;
		smashed_arg = expand_var(s, cmd, exit_status);
		smashed_arg = ft_expand_strjoin(smashed_arg, handle_outliar_quote(s, '"', &cmd[s->end], exit_status));
		s->tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, s->tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

char	*handle_outliar_quote(t_smash_kit *s, char flag, char *cmd, int *exit_status)
{
	char	*remain;
	int		i;

	remain = NULL;
	i = 1;
	while (cmd[i] && (cmd[i] != ' ' || check_redirection(cmd, i)))
	{
		if (cmd[i] == flag)
			printf("throw error in classifycmd will exit inshalla in a clean way\n");
		i++;
	}
	if (i == 1)
		return (NULL);
	else
	{
		s->start = 0;
		s->i = i + s->end;
		s->end = i;
		if (flag == '"')
			remain = expand_var(s, cmd, exit_status);
		else if (flag == '\'')
			remain = ft_substr(cmd, s->start + 1, s->end - s->start -1);
		s->start = s->end;
		return (remain);
	}
}
void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	char	*smashed_arg;

	smashed_arg = NULL;
	if (s->i == s->start)
		s->i++;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '\'')
	{
		s->end = s->i;
		smashed_arg = ft_substr(cmd, s->start + 1, s->end - s->start -1 );
		smashed_arg = ft_expand_strjoin(smashed_arg,
				handle_outliar_quote(s, '\'', &cmd[s->end], 0));
		tmp = fill_cmd_node(smashed_arg,'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
