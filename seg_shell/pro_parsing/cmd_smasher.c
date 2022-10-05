/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/04 19:41:44 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*cmd_smasher(char *cmd, t_list **head)
{
	smash_kit *s;

	s = NULL;
	s = init_smash_kit(s, head);
	while (cmd[s->i])
	{
		if (cmd_classifier(s, cmd, head) == '"')
		{
			double_qoute_smach(s, cmd, s->tmp, head);
		}
		else if (cmd_classifier(s, cmd, head) == '\'')
			single_qoute_smach(s, cmd, s->tmp, head);
		else
			spaces_smash(s, cmd, s->tmp, head);
		s->i++;
	}
	vis_smached_cmd(head);
	free(s);
	return (*head);
}

char	cmd_classifier(smash_kit *s, char *cmd, t_list **head)
{
	int	i;

	i = s->i;
	if (s->flag != 'i')
		return (s->flag);
	while (cmd[i])
	{
		if (is_redirection(s, cmd, head, i) || cmd[i] == ' ')
		{
			i++;
			continue ;
		}
		else if (cmd[i] == '"')
		{
			s->flag = '"';
		}
		else if (cmd[i] == '\'')
			s->flag = '\'';		
		else
			s->flag = 's';
		s->start = i;
		s->i = i + 1;
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
smash_kit	*init_smash_kit(smash_kit *s, t_list **head)
{
	s = malloc(sizeof(smash_kit) * 1);
	if (!s)
		return (NULL);
	s->start = 0;
	s->end  = 0;
	s->i = 0;
	s->tmp = *head;
	s->flag = 'i';
	return (s);
}

t_list	*fill_cmd_node(char *arg, char type)
{
	t_list *new_node;

	new_node = ft_lstnew(NULL);
	new_node->content = (void *)arg;
	new_node->flag = type;
	return (new_node);
}

/*
typedef struct s_list
{
	void			*content; //the string extracted from the command line
	char			**key_val; //NULL
	char			flag; //a: args  r: redirection
	struct s_list	*next;
}	t_list;
*/
//loop over the cmd with i
//get the location of start and end of the first word
//create new node and assign the char * then add to the lst last 
//keep looping and add items 
//add normal txt
//add "ignore every thing here"
// add 'ignore every thing here'
// check for | < > >> << 
//test and celebrate
/*
static int	*word_data_helper(const char *s, int *arr, int char_index)
{
	int				i;
	char			quote;
	static int		flag = 0;

	quote = '\0';
	i = 0;
	while (s[i])
	{
		quote = quote_update(s[i], quote, flag);
		if (quote == '\0')
			flag = 0;
		if ((is_delimi(s[i], quote)
				&& !is_delimi(s[i + 1], quote) && s[i + 1]))
		{
			if (quote != '\0')
				flag++;
			arr[char_index] = i + 1;
			char_index++;
		}
		if (!(is_delimi(s[i], quote)
				&& (is_delimi(s[i + 1], quote) || !s[i + 1])))
		{
			if (quote != '\0')
				flag++;
			arr[char_index] = i + 1;
			char_index++;
		}
		i++;
	}
	return (arr);
}

char	quote_update(char s, char quote, int flag)
{
	if (flag == 2)
		return ('\0');
	if (s == '\'' && quote != '"')
		quote = '\'';
	else if (s == '\"' && quote != '\'')
		quote = '"';
	return (quote);
}
*/