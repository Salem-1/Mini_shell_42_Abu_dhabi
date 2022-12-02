/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:09:44 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 18:45:45 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	vis_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		forens_printf("It's a null array <%s>\n", arr[0]);
	while (arr[i] != NULL)
	{
		forens_printf("%s\n", arr[i]);
		i++;
	}
}

void	visualize_cmd(t_parsed_command *t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	forens_printf("Visualizing cmd.........\n");
	forens_printf("cmd :%s  \npath is ~%c~   |\nagrs: ", t->cmd, t->path);
	forens_printf("sep_before = ~%c~ | sep after = ~%c~ \nagrs: ",
		t->before_sep, t->after_sep);
	forens_printf("\n-------------------------\n");
	while (t->args[i])
	{
		forens_printf("%s ", t->args[i]);
		i++;
	}
	forens_printf("\n-------------------------\n");
	forens_printf("Cmd visualization end.........\n");
	forens_printf("\n");
}

		// printf("tmp content = %s\n", (tmp)->flag);
void	vis_smached_cmd(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	if (tmp->flag < 30)
	{
		forens_printf("Will not visualize cmd this is an errored one\n");
	}
	while (tmp)
	{
		forens_printf("~%s~\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	visualized_piped_cmd(t_pipes *t)
{
	int	i;

	i = 0;
	forens_printf("\nVisualizing piped cmd............\n");
	forens_printf("\nnpipes = %d\n", t->npipes);
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->cmd)
			visualize_cmd(t->single_cmd[i]);
		else
			forens_printf("cmd and args are NULLS\n");
		i++;
	}
	forens_printf("End visualizing piped cmd............\n");
}
