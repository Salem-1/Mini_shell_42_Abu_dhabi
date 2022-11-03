/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:39:54 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/02 18:37:13 by ahsalem          ###   ########.fr       */
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
	// printf("trying to remove (%s) var node\n", delete_me->key_val[0]);
	len = length_of_larger_string(delete_me->key_val[0], tmp->key_val[0]);
	if (!ft_strncmp(delete_me->key_val[0], tmp->key_val[0], len))
		delete_me = handle_unset_is_first_node(delete_me, *env);
	else
	{
		node_before_del = search_env(*env, delete_me->key_val[0],  'b', throw_error);
		node_before_del->next = delete_me->next;
	}
	// vis_list(env, 'v');
	// forens_printf("\n\n\n\n");
	ft_lstdelone(delete_me, del);
	delete_me = NULL;
	// vis_list(env, 'v');
	return (*env);
}

t_list	*handle_unset_is_first_node(t_list *delete_me, t_list *env)
{
	t_list	*second_node;

	second_node =  env->next;
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
t_list	*search_env(t_list *t_env, char *env_variable, char flag, int throw_error)
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
		{
			throw_error = 's';
			// unset_error(env_variable);
		}
		return (NULL);
	}
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], env_variable);
		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
		{
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

int	is_repeated(char *cmd, t_list **env)
{
	if (search_list(*env, cmd, 'e'))
		return (1);
	else
		return (0);
}

int	valid_export_arg(char *str, char flag)
{
	int	i;

	i = 1;
	flag++;
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		// if (flag == 'e')
		// 	err_printf("minishell: export: `%s': not a valid identifier\n", str);
		// else
		// 	err_printf("minishell: unset: `%s': not a valid identifier\n", str);

		return (0);
	}
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

int	find_msize(char *cmd)
{
	int	m_size;
	int	i;

	m_size = 2;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			m_size = 3;
			break ;
		}
		i++;
	}
	return (m_size);
}
