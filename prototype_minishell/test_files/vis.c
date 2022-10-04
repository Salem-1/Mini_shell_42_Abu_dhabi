/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:09:44 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/03 21:41:20 by ahsalem          ###   ########.fr       */
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
	printf("%s ", t->cmd);
	while (t->args[i])
	{
		printf("%s ", t->args[i]);
		i++;
	}
	printf("\n");
}

		// printf("tmp content = %s\n", (tmp)->flag);
void	vis_smached_cmd(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		printf("<%s>\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}