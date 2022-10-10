/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:20:20 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 08:01:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_single_cmd_in_t_piped_cmd(t_pipes *t, int i)
{
	if (i == 0)
	{
		t->single_cmd[0] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[0]->before_sep = '\0';
	}
	else if (i > 0)
	{
		t->single_cmd[i] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[i]->before_sep = t->single_cmd[i - 1]->after_sep;
	}
	else
		printf("This is a bug in malloc_single_cmd, i = %d\n", i);
}

//expand this one to include the take and heredoc if needed
//the i = -1 is potential error for segfualts check for it
int	count_outliar_redire(t_list *cmd, int i)
{
	t_list	*tmp;

	printf("entering out count i = %d\n", i);
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
		printf("\nOutliar redirects cmds %d\n", i);
		return (i);
	}
	return (0);
}

void	decide_rel_abs_fill_cmd_null_arg(
		t_list *smashed_cmd, t_pipes *t, int i, int local_i)
{
	t->single_cmd[i]->cmd = t->single_cmd[i]->args[0];
	t->single_cmd[i]->path = decide_rel_or_abs_path(t->single_cmd[i]->cmd);
	t->single_cmd[i]->args[local_i] = NULL;
	printf("Am I seg here 2 cmd = %s i = %d, local_i = %d \n", t->single_cmd[i]->cmd, i, local_i);
	if (!smashed_cmd)
		t->single_cmd[i]->after_sep = '\0';
}

int	add_content_to_single_cmd_arg(t_parsed_command *single_cmd, int *local_i, t_list *smashed_cmd)
{
	if (smashed_cmd->flag == 'c')
	{
		printf("I don't have such null flags\n");
		return (0);
	}
	else if (smashed_cmd->flag == '\0')
	{
		single_cmd->args[(*local_i)++] = (char *)smashed_cmd->content;
		return (0);
	}
	return (1);
}

int	init_fill_cmd(int *local_i, int *i, t_pipes * t, t_list *smashed_cmd)
{
	int n_args;

	n_args = 0;
	*local_i = 0;
	n_args = count_args_in_cmd(smashed_cmd);
	printf("Single_cmd n_args = %d\n", n_args);
	malloc_single_cmd_in_t_piped_cmd(t, *i);
	t->single_cmd[*i]->args = malloc(sizeof(char *) * n_args + 1);
	return (n_args);
}