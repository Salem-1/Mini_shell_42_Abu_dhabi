/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:21:53 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 07:17:11 by ahsalem          ###   ########.fr       */
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
char	*expand_var(t_smash_kit *s, char *cmd, int * exit_status)
{
	t_dollar_expansion_kit	e;
printf("analyzing expansion operations:\n");
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	e.tmp = NULL;
	e.end = 0;
	e.new_arg = NULL;
	if (cmd[s->start] == '"')
		e.smashed_arg = ft_substr(cmd,  s->start + 1, s->end - s->start -1);
	else
		e.smashed_arg = ft_substr(cmd, s->start, s->end - s->start + 1);
	printf("smashed arg = %s\n", e.smashed_arg);
	e.start = ft_strnchr(e.smashed_arg, '$');
	printf("START = %d\n", e.start);
	if (e.start == -1)
		return (e.smashed_arg);
	e.end = get_end_of_var(e.smashed_arg + e.start + 1);
	printf("END = %d\n", e.end);
	while (e.start != -1)
		e.start = dollar_expan_operation_loop(&e, s, exit_status);
printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
printf("analyzing end .................\n");
	return (e.new_arg);
}

int	dollar_expan_operation_loop(
	t_dollar_expansion_kit *e, t_smash_kit *s, int *exit_status)
{
	(void)s;
	printf("Before join remaining/nnew arg  = %s\ncmd joined portion = %s \noriginal cmd = %s\n", e->new_arg, ft_substr(e->smashed_arg, 0, e->start), e->smashed_arg);
	e->new_arg = ft_expand_strjoin(
			e->new_arg, ft_substr(e->smashed_arg, 0, e->start));
	printf("\n\nAfter join remaining, new arg  = %s\nsamshed_arg = %s\n", e->new_arg, e->smashed_arg);

	e->var_key = ft_substr(e->smashed_arg, e->start + 1, e->end);
	printf("var_key = ~%s~\n", e->var_key);
	e->var_val = search_expanded_var(s->env, e->var_key, exit_status);
	if (e->var_val)
	{
		printf("var_value = %s\n", e->var_val);
		e->new_arg = ft_expand_strjoin(e->new_arg, e->var_val);
		printf("new_arg after joining value = %s\n", e->new_arg);
	}
	else
	{
		// e->new_arg = ft_expand_strjoin(e->new_arg, ft_strdup("$"));
		// e->new_arg = ft_expand_strjoin(e->new_arg, e->var_key);
	}
	e->smashed_arg += e->start + e->end + 1; 
	e->start = ft_strnchr(e->smashed_arg, '$');
	e->end = get_end_of_var(e->smashed_arg + e->start + 1);
	printf("remainig smashed arg = %s, new_arg = %s\n", e->smashed_arg, e->new_arg);
	if (e->start == -1 && ft_strlen(e->smashed_arg) > '\0')
		e->new_arg = ft_expand_strjoin(e->new_arg, ft_strdup(e->smashed_arg));
	printf("Exiting the loop new_arg = %s\n", e->new_arg);
	printf("before loop end, start = %d, end = %d\n", e->start, e->end);
	return (e->start);
	// return (-1);
}

char	*search_expanded_var(t_list *t_env, char *env_variable, int *exit_status)
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
/*
char	*expand_var(t_smash_kit *s, char *cmd)
{
	char	*smashed_arg;
	char	*new_arg;
	char	*var_key;
	t_list	*var_val;
	char	*tmp;
	int		start;
	int		end;

	tmp = NULL;
	end = 0;
	new_arg = NULL;
	smashed_arg = ft_substr(cmd, s->start, s->end - s->start + 1);
	printf("smashed arg = %s\n", smashed_arg);
	start = ft_strnchr(smashed_arg, '$');
	printf("START = %d\n", start);
	if (start == -1)
		return (smashed_arg);
	end = get_end_of_var(smashed_arg + start + 1);
	printf("END = %d\n", end);
	while (start != -1)
	{
		printf("before loop new_arg = %s\n", new_arg);
		new_arg = ft_expand_strjoin(new_arg, smashed_arg);
		start = ft_strnchr(smashed_arg, '$');
		printf("inside loop START = %d\n", start);
		end = get_end_of_var(smashed_arg + start + 1);
		printf("inside loop END = %d\n", end);
		var_key = ft_substr(smashed_arg, start + 1, end);
		printf("var_key = %s\n", var_key);
		var_val = search_expanded_var(s->env, var_key);
		if (var_val)
		{
			printf("var_value = %s\n", var_val->key_val[1]);
			new_arg = ft_expand_strjoin(new_arg, ft_strdup(var_val->key_val[1]));
			printf(" new_arg = %s\n", new_arg);
		}
		else
		{
			tmp = ft_substr(smashed_arg, 0, end + 1);
			printf("tmp = %s\n", tmp);
			new_arg = ft_expand_strjoin(new_arg, tmp);
		}
		// free(var_key);
		smashed_arg = smashed_arg + end + 1;
		printf("at loop end smashed_arg = %s\n", smashed_arg);
		start = ft_strnchr(smashed_arg, '$');
		// if (start == -1)
		// 	new_arg = expand_strjoin(new_arg, smashed_arg,
		// 			ft_strlen(new_arg) + ft_strlen(smashed_arg));
	}
	new_arg = ft_expand_strjoin(new_arg, smashed_arg + end);
	printf(" new_arg will return  %s\n", new_arg);
	// free(smashed_arg);
	return (new_arg);
}

*/