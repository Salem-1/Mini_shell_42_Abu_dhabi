/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:39:54 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/11 20:28:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle the invalid parameter name with message as follows
//unset: b=4: invalid parameter name
//with exit code 1
//printf("trying to remove (%s) var node\n", delete_me->key_val[0]);
//unset for multible variables not cleaning the env
void	exec_unset(struct t_parsed_command *t, t_list **env,int i)
{
	t_list	*tmp;

	tmp = NULL;
	if (!t->args[i])
		return ;
	tmp = search_env(*env, t->args[i], 'c');
	if (!tmp)
		exec_unset(t, env, i + 1);
	clear_var(tmp, env);
	if (t->args[i + 1])
		exec_unset(t, env, i + 1);
}

//The first condition for the case of the removed var is the first item
void	clear_var(t_list *delete_me, t_list **env)
{
	t_list	*node_before_del;
	int		len;

	node_before_del = NULL;
	if (!env || !delete_me)
		return ;
	// printf("trying to remove (%s) var node\n", delete_me->key_val[0]);
	len = length_of_larger_string(delete_me->key_val[0], (*env)->key_val[0]);
	if (!ft_strncmp(delete_me->key_val[0], (*env)->key_val[0], len))
		env = &delete_me->next;
	else
	{
		node_before_del = search_env(*env, delete_me->key_val[0],  'b');
		node_before_del->next = delete_me->next;
	}
	ft_lstdelone(delete_me, del);
}

//flag == 'c' return the searched node
//flag == 'b' return the node before the searched node
t_list	*search_env(t_list *t_env, char *env_variable, char flag)
{
	t_list	*tmp;
	t_list	*node_before;
	size_t	len;

	tmp = t_env;
	node_before = NULL;
	if (!t_env || !env_variable)
		return (NULL);
	if (!valid_export_arg(env_variable) || find_msize(env_variable) != 2)
	{
		unset_error(env_variable);
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

int	valid_export_arg(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		printf("throw an error (%s) inside valid_export_error()\n", str);
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
