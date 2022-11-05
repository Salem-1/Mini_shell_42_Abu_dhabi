/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/06 01:46:50 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_export(t_pipes *all_cmds,
				struct t_parsed_command *t, t_list **env, int flag)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	while (t->args[i])
	{
		if (valid_export_arg(t->args[i], 'e'))
		{
			tmp = parsed_exp_arg(t->args[i], env, tmp, t);
			if (tmp)
				ft_lstadd_back(env, tmp);
		}
		else
			raise_export_error(all_cmds, t->args[i], 'p');
		i++;
	}
	if (t->args[1] == NULL)
		vis_list(env, 'x');
	if (flag == 'c' && all_cmds->parse_error == 30)
		raise_export_error(all_cmds, t->args[i], 'c');
	if (all_cmds->parse_error == 30)
		return (1);
	return (0);
}

t_list	*parsed_exp_arg(char *cmd, t_list **env, t_list *tmp, struct t_parsed_command *t)
{
	char	**exp_item;
	int		m_size;

	exp_item = NULL;
	m_size = find_msize(cmd);
	if (ft_strnchr(cmd, '=') == -1)
	{
		if (is_repeated(cmd, env))
			return (NULL);
		else
			exp_item = fill_export_with_key_only(exp_item, m_size, cmd);
	}
	else
		exp_item = fill_export_with_key_val_variables(cmd, *env, tmp, exp_item);
	if (!exp_item)
		return (NULL);
	exp_item[m_size - 1] = NULL;
	tmp = fill_new_export_node(tmp, exp_item, m_size);
	if (is_repeated(exp_item[0], env))
	{
		if (t->args[1])
			free(t->args[1]);
		t->args[1] = ft_strdup(exp_item[0]);
		exec_unset(t, env, 1, 's');
	}
	return (tmp);
}

//flag == 'c' return the searched node
//flag == 'b' return the node before the searched node
// t_list	*search_env_for_export(t_list *t_env, char *env_variable, char flag, int throw_error)
// {
// 	t_list	*tmp;
// 	t_list	*node_before;
// 	size_t	len;

// 	tmp = t_env;
// 	node_before = NULL;
// 	if (!t_env || !env_variable)
// 		return (NULL);
// 	if (!valid_export_arg(env_variable, 'u') || find_msize(env_variable) != 2)
// 	{
// 		if (throw_error == 't')
// 		{
// 			throw_error = 's';
// 			unset_error(env_variable);
// 		}
// 		return (NULL);
// 	}
// 	while (tmp)
// 	{
// 		len = length_of_larger_string(tmp->key_val[0], env_variable);
// 		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
// 		{
// 			if (flag == 'c')
// 				return (tmp);
// 			else
// 				return (node_before);
// 		}
// 		node_before = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
//set the last exit, if succeessful it's 0,
//  if not make 127 for command not found
//126 permission denied, CTR-C 130, exit code of wait
//check the exit code of the builtins
//last minishelll inside wait() ==-1 no schild to wait upon CTR-c


/*
export specs:
if var with no value:
	-if not there Add var export list
	-if var is repeated do nothing
if var has value:
	-if exists update the value
	-else add the var=vlaue to env list

*/