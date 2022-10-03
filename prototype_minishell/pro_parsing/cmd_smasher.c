/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/03 17:20:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*cmd_smasher(char *cmd, t_list **head)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (cmd[i])
	{
		printf("hello from the other side %c\n", cmd[i]);
		i++;
	}
	return (tmp);
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