/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/11 09:41:16 by ahsalem          ###   ########.fr       */
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
		smashed_arg = expand_var(s, cmd, ' ');
		tmp = fill_cmd_node(smashed_arg, 'c');
		ft_lstadd_back(head, tmp);
		s->end = 0;
		s->flag = 'i';
	}
}

char	*expand_var(t_smash_kit *s, char *cmd, char flag)
{
	char	*smashed_arg;
	char	*searched_var;

	smashed_arg = NULL;
	searched_var = NULL;
	// if (!ft_strchr(cmd, '$'))
	if (flag == ' ')
		return (ft_substr(cmd, s->start, s->end - s->start + 1));
	// else
	// {
	// 	smashed_arg = ft_strchr(cmd, '$');
	// 	searched_var = ft_strtrim(searched_var, "$");
	// 	if (!ft_strncmp(searched_var, cmd + 1, ft_strlen(cmd) - 2))
	// 		return (ft_strdup(search_env()))
	// }
	return (ft_substr(cmd, s->start, s->end - s->start + 1));
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
