/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outliar_redirect_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:11:01 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/16 11:27:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
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
	int	j;

	if (t->single_cmd[*i]->before_sep == '\0')
		after_red = count_outliar_redire(smashed_cmd, 0);
	else
		after_red = count_outliar_redire(smashed_cmd, -1);
	if (after_red == 0)
		return ;
	j = 0;
	t->single_cmd[*i + 1] = malloc(sizeof(t_parsed_command) * 1);
	if (!t->single_cmd[*i + 1])
		return ;
	//fille the outliar cases for the first cmd
	if (t->single_cmd[*i]->before_sep == '\0')
	{
		if (after_red == 2)
			case_input_file_cat(smashed_cmd, t, i, local_i);
		// else if (after_red > 2)
		// 	case_input_file_cat_otherfiles(smashed_cmd, t, i, local_i);
		
		forens_printf("###Calling case %s 1\n", t->single_cmd[*i]->cmd);
		return ;
	}
}


/*
	convert 
	< file.txt cat
	to 
	cat < file.txt
*/

void	case_input_file_cat(
	t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	t->single_cmd[*i]->after_sep = 't';
	t->single_cmd[*i]->args = malloc(sizeof(char *) * 2);
	t->single_cmd[*i]->args[0] = (char *)smashed_cmd->next->next->content;
	t->single_cmd[*i]->args[1] = NULL;
	t->single_cmd[*i]->cmd = t->single_cmd[*i]->args[0];
	fill_redirec_outliar_cmd_hard_coded(t, i, smashed_cmd);
	smashed_cmd = smashed_cmd->next->next->next;
	(*local_i) += 1;
}

/*
void	case_input_file_cat_otherfiles(t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	int	after_red;
	int	j;

	after_red = 0;
	j = 0;
	smashed_cmd = smashed_cmd->next->next;
	t->single_cmd[*i]->args = malloc(sizeof(char *) * after_red);
	while ( smashed_cmd && j < after_red - 1)
	{
		if (smashed_cmd->flag == 'c')
			t->single_cmd[*i]->args[j] = (char *)smashed_cmd->content;
		else
			break;
		j++;
		(*local_i) += 1;
		smashed_cmd = smashed_cmd->next;
	}
	if (smashed_cmd)
	{
		t->single_cmd[*i]->after_sep = smashed_cmd->flag;
		smashed_cmd = smashed_cmd->next;
	}
	else
		t->single_cmd[*i]->after_sep = '\0';
	return ;
}
*/

void	fill_redirec_outliar_cmd_hard_coded(
	t_pipes *t, int *i, t_list *smashed_cmd)
{
	t->single_cmd[*i + 1]->before_sep = smashed_cmd->flag;
	t->single_cmd[*i + 1]->args = malloc(sizeof(char *) * 2);
	if (!t->single_cmd[*i + 1]->args)
		return ;
	t->single_cmd[*i + 1]->args[0] = (char *)smashed_cmd->next->content;
	t->single_cmd[*i + 1]->args[1] = NULL;
	t->single_cmd[*i + 1]->cmd = (char *)smashed_cmd->next->content;
}

int	count_outliar_redire(t_list *cmd, int i)
{
	t_list	*tmp;

forens_printf("entering out count i = %d\n", i);
	if (i < -1)
		i = -1;
	tmp = cmd;
	if (!tmp)
		return (0);
	// if (tmp->flag == 'a' || tmp->flag == 'g' || tmp->flag == 't'|| tmp->flag == 'h')
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
	forens_printf("\nOutliar redirects cmds %d\n", i);
		return (i);
	}
	return (0);
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
	t->single_cmd[*i + 1] = malloc(sizeof(t_parsed_command) * 1);
	if (!t->single_cmd[*i + 1])
		return ;
	fill_redirec_outliar_cmd_hard_coded(t, i, smashed_cmd);
	smashed_cmd = smashed_cmd->next;
	while (j < after_red)
	{
		smashed_cmd = smashed_cmd->next;
		if (!smashed_cmd || smashed_cmd->flag != 'c')
			break ;
		t->single_cmd[*i]->args[(*local_i)++] = (char *)smashed_cmd->content;
		j++;
	}
}
