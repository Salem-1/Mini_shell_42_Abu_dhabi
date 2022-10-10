/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:20:20 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 06:45:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_single_cmd_in_t_piped_cmd(t_pipes *t, int i)
{
	if (i == 0)
	{
		t->single_cmd[0] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[0]->before_sep = '\0';
	}
	else if (i > 0)
	{
		t->single_cmd[i] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[i]->before_sep = t->single_cmd[i - 1]->after_sep;
	}
	else
		printf("This is a bug in malloc_single_cmd, i = %d\n", i);
}

//expand this one to include the take and heredoc if needed
//the i = -1 is potential error for segfualts check for it
int	count_outliar_redire(t_list *cmd, int i)
{
	t_list	*tmp;

	printf("entering out count i = %d\n", i);
	if (i < -1)
		i = -1;
	tmp = cmd;
	if (!tmp)
		return (0);
	if (tmp->flag == 'a' || tmp->flag == 'g' || tmp->flag == 't')
	{
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->flag == 'c')
				i++;
			else
				break ;
			tmp = tmp->next;
		}
		printf("\nOutliar redirects cmds %d\n", i);
		return (i);
	}
	return (0);
}