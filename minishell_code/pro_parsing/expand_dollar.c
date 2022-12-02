/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:21:53 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 20:38:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
typedef struct dollar_expansion_kit
{
	char	*smashed_arg;
	char	*new_arg;
	char	*var_key;
	t_list	*var_val;
	char	*tmp;
	int		start;
	int		end;
}	t_dollar_expansion_kit;
*/

char	*expand_var(t_smash_kit *s, char *cmd, int *exit_status)
{
	t_dollar_expansion_kit	e;

	e.smashed_arg = cmd;
	e.tmp = NULL;
	e.end = 0;
	e.new_arg = NULL;
	e.start = ft_strnchr(e.smashed_arg, '$');
	if (e.start == -1)
		return (e.smashed_arg);
	e.end = get_end_of_var(e.smashed_arg + e.start + 1);
	while (e.start != -1)
		e.start = dollar_expan_operation_loop(&e, s, exit_status);
	free(cmd);
	return (e.new_arg);
}

int	dollar_expan_operation_loop(
	t_dollar_expansion_kit *e, t_smash_kit *s, int *exit_status)
{
	(void)s;
	e->new_arg = ft_expand_strjoin(
			e->new_arg, ft_substr(e->smashed_arg, 0, e->start));
	e->var_key = ft_substr(e->smashed_arg, e->start + 1, e->end);
	if (e->var_key[0] != '\0')
		e->var_val = search_expanded_var(s->env, e->var_key, exit_status);
	else
		e->var_val = ft_strdup("$");
	free(e->var_key);
	if (e->var_val)
		e->new_arg = ft_expand_strjoin(e->new_arg, e->var_val);
	e->smashed_arg += e->start + e->end + 1;
	e->start = ft_strnchr(e->smashed_arg, '$');
	e->end = get_end_of_var(e->smashed_arg + e->start + 1);
	if (e->start == -1 && ft_strlen(e->smashed_arg) > '\0')
		e->new_arg = ft_expand_strjoin(e->new_arg, ft_strdup(e->smashed_arg));
	return (e->start);
}

char	*search_expanded_var(
	t_list *t_env, char *env_variable, int *exit_status)
{
	t_list	*tmp;
	size_t	len;

	tmp = t_env;
	if (!t_env || !env_variable)
		return (NULL);
	if (env_variable[0] == '?')
		return (ft_itoa(*exit_status));
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], env_variable);
		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
			return (ft_strdup(tmp->key_val[1]));
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_end_of_var(char *var)
{
	int	i;

	i = 0;
	if (var[i] == '?')
		return (1);
	while (var[i])
	{
		if (!(ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}
