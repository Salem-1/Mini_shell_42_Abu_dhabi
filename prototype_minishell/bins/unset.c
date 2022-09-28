/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:39:54 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/28 10:03:30 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(struct t_parsed_command *t, t_list **env,int i)
{
	t_list	*tmp;

	tmp = NULL;
	// printf("calling unset, t->args[%d] = %s\n", i,  t->args[i]);
	// printf("assigning tmp to the searched variable\n");
	printf("calling unset\n");
	if (!t->args[i])
		return ;
	// printf("searching env for our var\n");
	tmp = search_env(*env, t->args[i], 'c');
	// printf("deleting %s node\n", tmp->key_val[0]);
	if (!tmp)
	{
		// printf("empty unset node, calling teh exec_unset again, rcursively\n");
		exec_unset(t, env, i + 1);
	}
	// printf("deleting the target var\n");
	clear_var(tmp, env);
	if (t->args[i + 1])
	{
		// printf("There are still exec arguments, call exec_unset recursively again\n");
		exec_unset(t, env, i + 1);
	}
	exec_env(env);
	printf("nothing more to do, as unset I fullfilled my life call\nGood bye!!\n");
}

void	clear_var(t_list *delete_me, t_list **env)
{
	t_list	*node_before_del;
	int		len;

	if (!env || !delete_me)
		return ;
	node_before_del = NULL;
	len = length_of_larger_string(delete_me->key_val[0], (*env)->key_val[0]);
	// printf("deleting %s node\n", delete_me->key_val[0]);
	if (!ft_strncmp(delete_me->key_val[0], (*env)->key_val[0], len))
		env = &delete_me->next;
	else
	{
		node_before_del = search_env(*env, delete_me->key_val[0],  'c');
		node_before_del->next = delete_me->next;
	}
	ft_lstdelone(delete_me, del);
}

t_list	*search_env(t_list *t_env, char *env_variable, char flag)
{
	t_list	*tmp;
	t_list	*node_before;
	size_t	len;

	tmp = t_env;
	node_before = NULL;
	if (!t_env || !env_variable)
		return (NULL);
	// printf("entering the searching loop\n");
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], env_variable);
		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
		{
			// printf("returning something\n");
			if (flag == 'c')
				return (tmp);
			else 
				return (node_before);
		}
		node_before = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

int	valid_export_arg(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i])
				|| str[i] == '_' || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}
