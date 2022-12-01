/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:39:54 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 09:36:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	flags
	t    throw an error
	s    silent the error
*/
int	exec_unset(struct t_parsed_command *t, t_list **env, int i, char flag)
{
	t_list	*tmp;
	int		exit_code;

	exit_code = 0;
	tmp = NULL;
	if (!t->args[i])
		return (0);
	while (t->args[i])
	{
		if (!valid_export_arg(t->args[i], 'u')
			|| ft_strnchr(t->args[i], '=') != -1)
		{
			if (flag == 't')
				unset_error(t->args[i], 1, 'n', NULL);
			exit_code = 1;
			i++;
			continue ;
		}
		tmp = search_env(*env, t->args[i], 'c', flag);
		if (tmp)
			*env = clear_var(tmp, env, flag);
		i++;
	}
	return (exit_code);
}

t_list	*handle_unset_is_first_node(t_list *delete_me, t_list *env)
{
	t_list	*second_node;

	second_node = env->next;
	if (second_node)
	{
		free(env->key_val[0]);
		free(env->key_val[1]);
		env->key_val[0] = ft_strdup(second_node->key_val[0]);
		env->key_val[1] = ft_strdup(second_node->key_val[1]);
		env->flag = second_node->flag;
		env->next = second_node->next;
		delete_me = second_node;
	}
	return (delete_me);
}
//flag == 'c' return the searched node
//flag == 'b' return the node before the searched node

t_list	*search_env(t_list *t_env,
			char *env_variable, char flag, int throw_error)
{
	t_list	*tmp;
	t_list	*node_before;
	size_t	len;

	tmp = t_env;
	node_before = NULL;
	if (!t_env || !env_variable)
		return (NULL);
	if (!valid_export_arg(env_variable, 'u') || find_msize(env_variable) != 2)
	{
		if (throw_error == 't')
			throw_error = 's';
		return (NULL);
	}
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], env_variable);
		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
			return (search_env_result(flag, tmp, node_before));
		node_before = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*search_env_result(char flag, t_list *tmp, t_list *node_before)
{
	if (flag == 'c')
		return (tmp);
	else
		return (node_before);
}
