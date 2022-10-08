/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:09:44 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/08 13:30:40 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	vis_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		printf("It's a null array <%s>\n", arr[0]);
	while (arr[i] != NULL)
	{
		printf("%s\n",arr[i]);
		i++;
	}
}

void	visualize_cmd(t_parsed_command *t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	printf("Visualizing cmd.........\n");
	printf("cmd :%s  \npath is ~%c~   |\nagrs: ", t->cmd, t->path);
	printf("sep_before = ~%c~ | sep after = ~%c~ \nagrs: ",
		t->before_sep, t->after_sep);
	printf("\n-------------------------\n");
	while (t->args[i])
	{
		printf("%s ", t->args[i]);
		i++;
	}
	printf("\n-------------------------\n");
	printf("Cmd visualization end.........\n");
	printf("\n");
}

		// printf("tmp content = %s\n", (tmp)->flag);
void	vis_smached_cmd(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		printf("~%s~\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	visualized_piped_cmd(t_pipes *t)
{
	int	i;

	i = 0;
	printf("\nVisualizing piped cmd............\n");
	printf("\nnpipes = %d\n", t->npipes);
	while (i < t->npipes)
	{
		visualize_cmd(t->single_cmd[i]);
		i++;
	}
	printf("End visualizing piped cmd............\n");
}