/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 15:27:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	if there is parser error
	will fill the first flag with parser error code, 
	check if there is an error if the flag value less than 30
*/

t_list	*cmd_smasher(char *cmd, t_list **head, t_list *env, int *exit_status)
{
	t_smash_kit	s;

	init_smash_kit(&s, head, env, cmd);
	s.cmd_len = (int)ft_strlen(cmd);
	while (s.i < s.cmd_len)
	{
		forens_printf("smasher loop %d=%c,flag=%c, s.start = %d, s.end = %d\n",
			s.i, cmd[s.i], s.flag, s.start, s.end);
		if (cmd_classifier(&s, cmd) == 'r')
		{
			fill_redirection(&s, cmd, head, s.i);
		}
		else if (cmd_classifier(&s, cmd) == '\'')
			single_qoute_smach(&s, cmd, s.tmp, head);
		else if (cmd_classifier(&s, cmd) == '"')
			double_qoute_smash(&s, cmd, head, exit_status);
		else
			spaces_smash(&s, cmd, head, exit_status);
		if (s.parse_error_code != 0)
			break ;
		s.i++;
	}
	stick_error_code_if_it__exists(cmd, *head, &s);
	return (*head);
}

char	cmd_classifier(t_smash_kit *s, char *cmd)
{
	int	i;

	i = s->i;
	if (s->flag != 'i')
		return (s->flag);
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			i++;
			continue ;
		}
		else if (check_redirection(cmd, i))
			s->flag = 'r';
		else if (cmd[i] == '"')
			s->flag = '"';
		else if (cmd[i] == '\'')
			s->flag = '\'';
		else
			s->flag = 's';
		s->start = i;
		return (s->flag);
	}
	return (s->flag);
}

/*
	s->flag = i for initial stage
			= c for command
			= p for pipes
			= g give
			= t take
*/
void	init_smash_kit(t_smash_kit *s, t_list **head, t_list *env, char *cmd)
{
	s->start = 0;
	s->end = 0;
	s->last_end = 0;
	s->i = 0;
	s->tmp = *head;
	s->flag = 'i';
	s->env = env;
	s->parse_error_code = 0;
	s->cmd_len = 0;
	s->cmd = cmd;
}

t_list	*fill_cmd_node(char *arg, char type)
{
	t_list	*new_node;

	new_node = ft_lstnew(NULL);
	new_node->content = (void *)arg;
	new_node->flag = type;
	return (new_node);
}
