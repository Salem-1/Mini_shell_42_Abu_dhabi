/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:09:44 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 22:44:00 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	vis_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		err_printf("It's a null array <%s>\n", arr[0]);
	while (arr[i] != NULL)
	{
		err_printf("%s\n", arr[i]);
		i++;
	}
}

void	visualize_cmd(t_parsed_command *t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	err_printf("Visualizing cmd.........\n");
	err_printf("cmd :%s  \npath is ~%c~   |\nagrs: ", t->cmd, t->path);
	err_printf("sep_before = ~%c~ | sep after = ~%c~ \nagrs: ",
		t->before_sep, t->after_sep);
	err_printf("\n-------------------------\n");
	while (t->args[i])
	{
		err_printf("%s ", t->args[i]);
		i++;
	}
	err_printf("\n-------------------------\n");
	err_printf("Cmd visualization end.........\n");
	err_printf("\n");
}

		// printf("tmp content = %s\n", (tmp)->flag);
void	vis_smached_cmd(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	if (tmp->flag < 30)
	{
		err_printf("Will not visualize cmd this is an errored one\n");
	}
	while (tmp)
	{
		err_printf("~%s~\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	visualized_piped_cmd(t_pipes *t)
{
	int	i;

	i = 0;
	err_printf("\nVisualizing piped cmd............\n");
	err_printf("\nnpipes = %d\n", t->npipes);
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->cmd)
			visualize_cmd(t->single_cmd[i]);
		else
			err_printf("cmd and args are NULLS\n");
		i++;
	}
	err_printf("End visualizing piped cmd............\n");
}
