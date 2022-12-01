/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 18:42:52 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipes	*parsing_piped_cmd(char *cmd, t_list *env, int *exit_status)
{
	t_list				*smashed_cmd;
	t_pipes				*t;
	int					i;
	t_list				*smashed_head;

	i = 0;
	t = NULL;
	smashed_cmd = NULL;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd, env, exit_status);
	if (!smashed_cmd)
		return (NULL);
	smashed_head = smashed_cmd;
	t = init_t_struct(t, smashed_cmd, env);
	if (t->parse_error != 0)
		return (t);
	while (smashed_cmd)
	{
		smashed_cmd = fill_cmd(smashed_cmd, t, i);
		if (smashed_cmd)
			smashed_cmd = smashed_cmd->next;
		else
			break ;
		i++;
	}
	parsing_laundry(t, smashed_head, cmd, i);
	return (t);
}


t_pipes	*init_t_struct(t_pipes *t, t_list *smashed_cmd, t_list *env)
{
	t = ft_calloc(sizeof(t_pipes), 1);
	if (!t)
		return (NULL);
	t->fd = NULL;
	t->env = env;
	t->parse_error = scan_cmd_for_parsing_errors(smashed_cmd);
	if (smashed_cmd->flag < 30 || t->parse_error != 0)
	{
		if (smashed_cmd->flag == 2 || t->parse_error == 2)
			fill_errored_pipe(t, 2, smashed_cmd);
		else if (smashed_cmd->flag == 1 || t->parse_error == 1)
			fill_errored_pipe(t, 1, smashed_cmd);
		else if (smashed_cmd->flag == 3 || t->parse_error == 3)
			fill_errored_pipe(t, 3, smashed_cmd);
		return (t);
	}
	t->npipes = count_cmds(smashed_cmd);
	if (smashed_cmd->flag != 'c' && t->npipes == 1)
		t->single_cmd = ft_calloc(sizeof(t_parsed_command *), t->npipes + 2);
	else
		t->single_cmd = ft_calloc(sizeof(t_parsed_command *), t->npipes + 1);
	if (!t->single_cmd)
		return (NULL);
	return (t);
}

t_list	*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i)
{
	int		local_i;

	init_fill_cmd(&local_i, &i, t, smashed_cmd);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == 'c')
			t->single_cmd[i]->args[local_i++]
				= ft_strdup((char *)smashed_cmd->content);
		else
		{
			if (smashed_cmd->flag == 'g' || smashed_cmd->flag == 'a')
				fill_outliar_redirected_cmd(smashed_cmd, t, &i, &local_i);
			else if (smashed_cmd->flag == 't')
				fill_outliar_input(smashed_cmd, t, &i, &local_i);
			else if (smashed_cmd->flag == 'h')
				if (!smashed_cmd)
					return (smashed_cmd);
			t->single_cmd[i]->after_sep = smashed_cmd->flag;
			break ;
		}
		smashed_cmd = smashed_cmd->next;
	}
	decide_rel_abs_fill_cmd_null_arg(smashed_cmd, t, i, local_i);
	return (smashed_cmd);
}

/*
this line belongs to line 83
		// forens_printf("fill_cmd i= %d,local_i=%d, smashed_arg = %s, flag = \n",
		// 	i, local_i, smashed_cmd->content, smashed_cmd->flag);
*/