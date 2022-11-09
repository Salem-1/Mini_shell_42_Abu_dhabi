/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:20:20 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/09 06:00:30 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	I created this function to fill the before sep in first-
	single_cmd with null
*/
void	malloc_single_cmd_in_t_piped_cmd(t_pipes *t, int i)
{
	if (t->parse_error != 0)
		return ;
	t->single_cmd[i] = ft_calloc(sizeof(t_parsed_command), 1);
	if (!t->single_cmd[i])
	{
		err_printf("Failed to malloc t->single_cmd[%d]", i);
		return ;
	}
	if (i == 0)
		t->single_cmd[0]->before_sep = '\0';
	else if (i > 0)
		t->single_cmd[i]->before_sep = t->single_cmd[i - 1]->after_sep;
}

//expand this one to include the take and heredoc if needed
//the i = -1 is potential error for segfualts check for it


void	decide_rel_abs_fill_cmd_null_arg(
		t_list *smashed_cmd, t_pipes *t, int i, int local_i)
{
	if (local_i != 0)
	{
		t->single_cmd[i]->cmd = t->single_cmd[i]->args[0];
		t->single_cmd[i]->path = decide_rel_or_abs_path(t->single_cmd[i]->cmd);
		t->single_cmd[i]->args[local_i] = NULL;
	}
	if (!smashed_cmd)
		t->single_cmd[i]->after_sep = '\0';
}

int	add_content_to_single_cmd_arg(t_parsed_command *single_cmd, int *local_i, t_list *smashed_cmd)
{
	if (smashed_cmd->flag == 'c')
	{
	//forens_printf("I don't have such null flags\n");
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
//forens_printf("Single_cmd n_args = %d\n", n_args);
	malloc_single_cmd_in_t_piped_cmd(t, *i);
	t->single_cmd[*i]->args = ft_calloc(sizeof(char *), n_args + 1);
	if (!t->single_cmd[*i]->args)
		return (0);
	return (n_args);
}