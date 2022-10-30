/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_laundary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:27:23 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/28 02:10:51 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing_laundry(t_pipes *t)
{
	//forens_printf("\n*********~~~~~~~~~~~~~Let's Rock and Roll~~~~~~~~~~~~~*********\n");
	//forens_printf("inside parsing laundary, let's miss up the execution\n");
	//forens_printf("num cmds = %d\n", t->npipes);
	if (t->npipes == 1)
		return ;
	if (t->npipes == 2 && t->single_cmd[0]->after_sep == 't' && !t->single_cmd[0]->cmd
		&& t->single_cmd[1]->args[0])
	{
		//forens_printf("if 1\n");
		if (t->single_cmd[1]->args[1])
		{
		//forens_printf("if 2\n");
			if (t->single_cmd[1]->args[2])
			{
				//forens_printf("we are gonna miss with this command \n");
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
		//forens_printf("arg[%d] = %s\n", i , t->single_cmd[0]->args[i]);
		i++;
	}
	t->single_cmd[0]->args[i] = NULL;
	t->npipes = 1;
	t->single_cmd[0]->cmd = t->single_cmd[0]->args[0];
	t->single_cmd[0]->before_sep = '\0';
	t->single_cmd[0]->after_sep = '\0';
	t->single_cmd[0]->path = 'r';
}
