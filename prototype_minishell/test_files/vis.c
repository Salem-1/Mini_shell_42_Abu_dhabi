/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:09:44 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 16:38:20 by ahsalem          ###   ########.fr       */
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
		printf("is valied %d  %s\n",valid_export_arg(arr[i]), arr[i]);
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

void	vis_list(t_list **env, char is_env_or_exp)
{
	t_list	*tmp;

	if (!env)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (is_env_or_exp == 'x')
		{
			if ((tmp)->flag == 'v')
				printf("declare -x %s=\"%s\"\n", tmp->key_val[0], tmp->key_val[1]);
			else
				printf("declare -x %s\n", tmp->key_val[0]);

		}
		else if (((tmp)->flag) == 'v')
			printf("%s=%s\n", tmp->key_val[0], tmp->key_val[1]);
		tmp = tmp->next;
	}
}

		// printf("tmp content = %s\n", (tmp)->flag);