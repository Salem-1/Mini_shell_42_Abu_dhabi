/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:09:14 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 16:21:45 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_repeated(char *cmd, t_list **env)
{
	if (search_list(*env, cmd, 'e'))
		return (1);
	else
		return (0);
}

//The first condition for the case of the removed var is the first item
t_list	*clear_var(t_list *delete_me, t_list **env, int throw_error)
{
	t_list	*node_before_del;
	int		len;
	t_list	*tmp;

	node_before_del = NULL;
	if (!env || !delete_me)
		return (NULL);
	tmp = *env;
	len = length_of_larger_string(delete_me->key_val[0], tmp->key_val[0]);
	if (!ft_strncmp(delete_me->key_val[0], tmp->key_val[0], len))
		delete_me = handle_unset_is_first_node(delete_me, *env);
	else
	{
		node_before_del = search_env(
				*env, delete_me->key_val[0], 'b', throw_error);
		node_before_del->next = delete_me->next;
	}
	ft_lstdelone(delete_me, del);
	delete_me = NULL;
	return (*env);
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
