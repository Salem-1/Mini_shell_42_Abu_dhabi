/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 19:13:44 by ahsalem          ###   ########.fr       */
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
		vis_export(env, 'x');
	if (flag == 'c' && all_cmds->parse_error == 30)
		raise_export_error(all_cmds, t->args[i], 'c');
	if (all_cmds->parse_error == 30)
		return (1);
	return (0);
}

t_list	*parsed_exp_arg(
	char *cmd, t_list **env, t_list *tmp, struct t_parsed_command *t)
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
		handling_repeated_export_item(t, exp_item, env);
	return (tmp);
}

void	handling_repeated_export_item(
	struct t_parsed_command *t, char	**exp_item, t_list **env)
{
	if (t->args[1])
		free(t->args[1]);
	t->args[1] = ft_strdup(exp_item[0]);
	exec_unset(t, env, 1, 's');
}

int	valid_export_arg(char *str, char flag)
{
	int	i;

	i = 1;
	flag++;
	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
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
