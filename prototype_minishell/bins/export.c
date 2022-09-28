/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/27 19:16:37 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//if the exported var has an export value, and 
//export not assigning new value, then do noting

//remember to search for the var and replace it with  new 

//check export duplicates with value, then celebrate
void	exec_export(struct t_parsed_command *t, t_list **env)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = NULL;
	while (t->args[i])
	{
		if (valid_export_arg(t->args[i]))
		{
			tmp = parsed_exp_arg(t->args[i], env, tmp);
			if (tmp)
				ft_lstadd_back(env, tmp);
		}
		else
			raise_export_error(t->args[i]);
		i++;
	}
	if (t->args[1] == NULL)
		vis_list(env, 'x');
}

t_list	*parsed_exp_arg(char *cmd, t_list **env, t_list *tmp)
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
	if (is_repeated(exp_item[0], &env))
	{
		t->args[1] = exp_item[0];
		exec_unset(t, env, 1);
	}
	return (tmp);
}

char	**fill_export_with_key_only(char **exp_item, int m_size, char *cmd)
{
	exp_item = malloc(sizeof(char *) * m_size);
	if (!exp_item)
		return (NULL);
	exp_item[0] = ft_strdup(cmd);
	return (exp_item);
}

//test this befor deployment
char	**fill_export_with_key_val_variables(char *cmd,
			t_list *env,t_list *tmp, char **exp_item)
{
	int	equal_location;

	(void)tmp;
	equal_location = ft_strnchr(cmd, '=');
	if (equal_location == -1)
	{
		printf("This should never be triggered\n");
		return (NULL);
	}
	exp_item = malloc(sizeof(char *) * 3);
	if (!exp_item)
		return (NULL);
	exp_item[0] = ft_substr(cmd,0,  equal_location);
	exp_item[1] = ft_substr(cmd, equal_location + 1,
			ft_strlen(cmd) - equal_location);
	return (exp_item);
}

t_list	*fill_new_export_node(t_list *tmp, char **exp_item, int m_size)
{
	t_list *existing_var;

	tmp = ft_lstnew(exp_item);
	if (m_size == 2)
		tmp->flag = 'x';
	return (tmp);
}
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