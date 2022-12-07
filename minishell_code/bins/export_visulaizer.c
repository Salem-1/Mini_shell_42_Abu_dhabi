/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_visulaizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:13:56 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 19:38:49 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	vis_export(t_list **env, char is_env_or_exp)
{
	capitals_export_print(*env, is_env_or_exp);
	print_export_with_condition(*env, is_env_or_exp, '_');
	small_export_print(*env, is_env_or_exp);
}

void	print_export_with_condition(
		t_list *env, char is_env_or_exp, char letter)
{
	t_list	*tmp;

	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		if (tmp->key_val[0][0] == letter)
		{
			if (is_env_or_exp == 'x')
			{
				if ((tmp)->flag == 'v')
					printf("declare -x %s=\"%s\"\n",
						tmp->key_val[0], tmp->key_val[1]);
				else
					printf("declare -x %s\n", tmp->key_val[0]);
			}
			else if (((tmp)->flag) == 'v')
				printf("%s=%s\n", tmp->key_val[0], tmp->key_val[1]);
		}
		tmp = tmp->next;
	}
}

void	capitals_export_print(
		t_list *env, char is_env_or_exp)
{
	char	i;

	i = 'A';
	while (i <= 'Z')
	{
		print_export_with_condition(env, is_env_or_exp, i);
		i++;
	}
}

void	small_export_print(
		t_list *env, char is_env_or_exp)
{
	char	i;

	i = 'a';
	while (i <= 'z')
	{
		print_export_with_condition(env, is_env_or_exp, i);
		i++;
	}
}
