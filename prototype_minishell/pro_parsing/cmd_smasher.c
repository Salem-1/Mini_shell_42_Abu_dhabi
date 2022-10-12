/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/11 17:53:05 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*cmd_smasher(char *cmd, t_list **head, t_list *env)
{
	t_smash_kit	*s;

	s = NULL;
	s = init_smash_kit(s, head, env);
	while (cmd[s->i])
	{
		if (cmd_classifier(s, cmd) == 'r')
		{
			printf("redirection smasher cmd[%d] = (%c)\n", s->i, cmd[s->i]);
			fill_redirection(s, cmd, head, s->i);
		}
		else if (cmd_classifier(s, cmd) == '\'')
			single_qoute_smach(s, cmd, s->tmp, head);
		else if (cmd_classifier(s, cmd) == '"')
			double_qoute_smash(s, cmd, s->tmp, head);
		else
			spaces_smash(s, cmd, s->tmp, head);
		s->i++;
	}
	vis_smached_cmd(head);
	free(s);
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
t_smash_kit	*init_smash_kit(t_smash_kit *s, t_list **head, t_list *env)
{
	s = malloc(sizeof(t_smash_kit) * 1);
	if (!s)
		return (NULL);
	s->start = 0;
	s->end  = 0;
	s->i = 0;
	s->tmp = *head;
	s->flag = 'i';
	s->env = env;
	return (s);
}

t_list	*fill_cmd_node(char *arg, char type)
{
	t_list	*new_node;

	new_node = ft_lstnew(NULL);
	new_node->content = (void *)arg;
	new_node->flag = type;
	return (new_node);
}
