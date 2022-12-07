/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outliar_redirect_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:11:01 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 22:01:40 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
//check if this is the first node that has t  for this case:  < f cat f2 f3 f4 
	then t-> n_pipes--, and rearrange the cmd to be:
	sep before '\0'
	cmd : cat
	args : cat f2 f3 f4
	sep after what is after f4

smashed_cmd = smashed_cmd->next	
---------

	count args after the n_args
	if at the begining
	if 1 act normally
	if 2 shuffle the order
	if 3 ignore t and next c then fill the rest normally
	if < in the middle and n_args > 1 then ignore < file
	and join the command so 
	cat < file.txt f2 f3 f4   will be
	cat f2 f3 f4
*/

void	fill_outliar_input(
		t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	int	after_red;

	if (t->single_cmd[*i]->before_sep == '\0')
		after_red = count_outliar_redire(smashed_cmd, 0);
	else
		after_red = count_outliar_redire(smashed_cmd, -1);
	if (after_red == 0)
		return ;
	if (!t->single_cmd[*i + 1])
		return ;
	if (t->single_cmd[*i]->before_sep == '\0')
	{
		err_printf("this shouldn't be triggred\n");
		if (after_red == 2)
			case_input_file_cat(smashed_cmd, t, i, local_i);
		return ;
	}
}

/*
	convert 
	< file.txt cat
	to 
	cat < file.txt
	
	
	the functions below cause double free
*/
void	case_input_file_cat(
	t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	err_printf("inside case_input_file_cat\n");
	t->single_cmd[*i]->after_sep = 't';
	t->single_cmd[*i]->args = malloc(sizeof(char *) * 2);
	t->single_cmd[*i]->args[0] = (char *)smashed_cmd->next->next->content;
	t->single_cmd[*i]->args[1] = NULL;
	t->single_cmd[*i]->cmd = t->single_cmd[*i]->args[0];
	fill_redirec_outliar_cmd_hard_coded(t, i, smashed_cmd);
	smashed_cmd = smashed_cmd->next->next->next;
	(*local_i) += 1;
}

void	fill_outliar_redirected_cmd(
	t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	int	after_red;
	int	j;

	after_red = 0;
	j = 0;
	after_red = count_outliar_redire(smashed_cmd, -1);
	if (after_red <= 0)
		return ;
	smashed_cmd = smashed_cmd->next;
	while (j < after_red)
	{
		smashed_cmd = smashed_cmd->next;
		if (!smashed_cmd || smashed_cmd->flag != 'c')
			break ;
		t->single_cmd[*i]->args[(*local_i)++]
			= ft_strdup((char *)smashed_cmd->content);
		j++;
	}
}

int	count_outliar_redire(t_list *cmd, int i)
{
	t_list	*tmp;

	if (i < -1)
		i = -1;
	tmp = cmd;
	if (!tmp)
		return (0);
	if (tmp->flag == 'a' || tmp->flag == 'g' || tmp->flag == 't')
	{
		tmp = tmp->next;
		while (tmp)
		{
			if (tmp->flag == 'c')
				i++;
			else
				break ;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

//I left this function as a refrence
void	fill_redirec_outliar_cmd_hard_coded(
	t_pipes *t, int *i, t_list *smashed_cmd)
{
	t->single_cmd[*i + 1]->before_sep = smashed_cmd->flag;
	if (t->single_cmd[*i + 1]->args)
		free(t->single_cmd[*i + 1]->args);
	t->single_cmd[*i + 1]->args = ft_calloc(sizeof(char *), 2);
	if (!t->single_cmd[*i + 1]->args)
		return ;
	t->single_cmd[*i + 1]->args[0]
		= ft_strdup((char *)smashed_cmd->next->content);
	t->single_cmd[*i + 1]->args[1] = NULL;
	t->single_cmd[*i + 1]->cmd = ft_strdup((char *)smashed_cmd->next->content);
}
