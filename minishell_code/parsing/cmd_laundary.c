/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_laundary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:27:23 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 21:50:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing_laundry(t_pipes *t, t_list *smashed_head, char *cmd, int i)
{
	t->single_cmd[i + 1] = NULL;
	clean_env(smashed_head);
	free(cmd);
	if (t->npipes == 1)
		return ;
	if (t->npipes == 2 && t->single_cmd[0]->after_sep == 't'
		&& !t->single_cmd[0]->cmd
		&& t->single_cmd[1]->args[0])
	{
		if (t->single_cmd[1]->args[1])
		{
			if (t->single_cmd[1]->args[2])
			{
				case_take_f1_cat_f2_f3_etc(t);
			}
		}
	}
}

void	case_take_f1_cat_f2_f3_etc(t_pipes *t)
{
	int	i;
	int	count_args;

	count_args = 0;
	i = 0;
	if (t->single_cmd[0]->args[0])
		free(t->single_cmd[0]->args[0]);
	while (t->single_cmd[1]->args[count_args++])
		;
	t->single_cmd[0]->args = malloc(sizeof(char *) * count_args);
	if (!t->single_cmd[0]->args)
		return ;
	while (t->single_cmd[1]->args[i + 1])
	{
		t->single_cmd[0]->args[i] = ft_strdup(t->single_cmd[1]->args[i + 1]);
		i++;
	}
	t->single_cmd[0]->args[i] = NULL;
	t->npipes = 1;
	t->single_cmd[0]->cmd = t->single_cmd[0]->args[0];
	t->single_cmd[0]->before_sep = '\0';
	t->single_cmd[0]->after_sep = '\0';
	t->single_cmd[0]->path = 'r';
}
