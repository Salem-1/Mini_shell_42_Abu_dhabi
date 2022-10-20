/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:44:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/20 07:41:39 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	flags
	t    throw an error
	s    silent the error
*/
void	exec_export(struct t_parsed_command *t, t_list **env, int flag)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = NULL;
	while (t->args[i])
	{
		if (valid_export_arg(t->args[i]))
		{
			tmp = parsed_exp_arg(t->args[i], env, tmp, t);
			if (tmp)
				ft_lstadd_back(env, tmp);
		}
		else if (flag == 't')
			raise_export_error(t->args[i]);
		i++;
	}
	if (t->args[1] == NULL)
		vis_list(env, 'x');
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
		t->args[1] = ft_strdup(exp_item[0]);
		exec_unset(t, env, 1, 't');
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
	(void)env;
	equal_location = ft_strnchr(cmd, '=');
	if (equal_location == -1)
	{
		err_printf("Inside export parsingThis should never be triggered\n");
		return (NULL);
	}
	exp_item = malloc(sizeof(char *) * 3);
	if (!exp_item)
		return (NULL);
	exp_item[0] = ft_substr(cmd,0,  equal_location);
	exp_item[1] = ft_substr(cmd, equal_location + 1,
			ft_strlen(cmd) - equal_location);
	if (ft_strnchr(exp_item[1], '"') != -1 || ft_strnchr(exp_item[1], '\'') != -1)
	{
		if (ft_strnchr(exp_item[1], '"') < ft_strnchr(exp_item[1], '\'') || ft_strnchr(exp_item[1], '\'') == -1)
			exp_item[1] = clean_export_var_from_quotes(exp_item[1], '"');
		else
			exp_item[1] = clean_export_var_from_quotes(exp_item[1], '\'');
	}
	forens_printf("exported val = ~%s~\n", exp_item[1]);
	return (exp_item);
}

char	*clean_export_var_from_quotes(char *val, char quote)
{
	char	*new_arg;
	char	*result;
	int		i;

	new_arg = NULL;
	i = 0;
	if (!strrchr(val, quote))
		return (val);
	if (val[i] == quote && val[i+ 1] == quote)
	{
		free(val);
		return (ft_expand_strjoin(new_arg, ft_strdup("\0")));
	}
	else
		new_arg = ft_strjoin(new_arg, strchr(val, quote) + 1);
	while (new_arg[i])
	{
		if (new_arg[i] == quote)
			break ;
		i++;
	}
	result = ft_strjoin(ft_substr(new_arg, 0, i), &new_arg[i + 1]);
	free(new_arg);
	return (result);
}

t_list	*fill_new_export_node(t_list *tmp, char **exp_item, int m_size)
{
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