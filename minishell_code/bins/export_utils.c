/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:38:13 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/24 13:31:42 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	//forens_printf("exported val = ~%s~\n", exp_item[1]);
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

char	**fill_export_with_key_only(char **exp_item, int m_size, char *cmd)
{
	exp_item = malloc(sizeof(char *) * m_size);
	if (!exp_item)
		return (NULL);
	exp_item[0] = ft_strdup(cmd);
	return (exp_item);
}