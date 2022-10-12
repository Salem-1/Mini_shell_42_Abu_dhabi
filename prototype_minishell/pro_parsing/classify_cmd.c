/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/12 08:26:04 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//remember to take the nulls
void	spaces_smash(t_smash_kit *s, char *cmd, t_list *tmp, t_list **head)
{
	char	*smashed_arg;

	smashed_arg = NULL;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == ' ' && cmd[s->i + 1] && cmd[s->i + 1] != ' ')
		s->start = s->i + 1;
	else if (cmd[s->i] == ' ')
		;
	else if (cmd[s->i + 1] == ' ' || check_redirection(cmd, s->i + 1)
		|| !cmd[s->i + 1])
	{
		s->end = s->i;
		smashed_arg = expand_var(s, cmd);
		tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
//respect this function and work it all over again inshalla
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
		new_arg = expand_strjoin(new_arg, smashed_arg);
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
			new_arg = expand_strjoin(new_arg, ft_strdup(var_val->key_val[1]));
			printf(" new_arg = %s\n", new_arg);
		}
		else
		{
			tmp = ft_substr(smashed_arg, 0, end + 1);
			printf("tmp = %s\n", tmp);
			new_arg = expand_strjoin(new_arg, tmp);
		}
		// free(var_key);
		smashed_arg = smashed_arg + end + 1;
		printf("at loop end smashed_arg = %s\n", smashed_arg);
		start = ft_strnchr(smashed_arg, '$');
		// if (start == -1)
		// 	new_arg = expand_strjoin(new_arg, smashed_arg,
		// 			ft_strlen(new_arg) + ft_strlen(smashed_arg));
	}
	new_arg = expand_strjoin(new_arg, smashed_arg + end);
	printf(" new_arg will return  %s\n", new_arg);
	// free(smashed_arg);
	return (new_arg);
}

t_list	*search_expanded_var(t_list *t_env, char *env_variable)
{
	t_list	*tmp;
	size_t	len;

	tmp = t_env;
	if (!t_env || !env_variable)
		return (NULL);
	while (tmp)
	{
		len = length_of_larger_string(tmp->key_val[0], env_variable);
		if (!ft_strncmp(tmp->key_val[0], env_variable, len))
			return (tmp);
		
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_end_of_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!(ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

void	double_qoute_smash(t_smash_kit *s, char *cmd, t_list *tmp,
			t_list **head)
{
	if (s->i == s->start)
		s->i++;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '"')
	{
		//make outliar function to check the word write after the double quote
		s->end = s->i ;
		tmp = fill_cmd_node(ft_substr(cmd, s->start + 1,
					s->end - s->start -1 ), 'c');
		//apply the expansion function inside the fillnode to 
		//join the new string with expanded values
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

void	single_qoute_smach(t_smash_kit *s, char *cmd,
		t_list *tmp, t_list **head)
{
	if (s->i == s->start)
		s->i++;
	if (!cmd[s->i])
		return ;
	if (cmd[s->i] == '\'')
	{
		s->end = s->i;
		tmp = fill_cmd_node(ft_substr(cmd, s->start + 1,
					s->end - s->start -1 ),'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}
