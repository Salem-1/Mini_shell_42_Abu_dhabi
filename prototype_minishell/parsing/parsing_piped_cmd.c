/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/08 17:37:17 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO free all the malloced staff after pipes inshalla
//do function to parse the pipe, return pipe count ant splitted piped cmd

//check the single cmd for errors like / > < ;

t_pipes	*parsing_piped_cmd(char *cmd)
{
	t_list				*smashed_cmd;
	t_pipes				*t;
	int					n_cmds;
	int					i;

	i = 0;
	t = NULL;
	n_cmds = 0;
	smashed_cmd = NULL;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd);
	n_cmds = count_cmds(smashed_cmd);
	printf("n_cmds = %d\n", n_cmds);
	t = init_t_struct(t, n_cmds);
	fill_cmd(smashed_cmd, t, -1);
	while (smashed_cmd)
	{
		printf("round %d\n", i);
		smashed_cmd  = fill_cmd(smashed_cmd, t, i);
		printf("i = %d  ", i);
		// visualize_cmd(t->single_cmd[i]);
		if (smashed_cmd)
			smashed_cmd = smashed_cmd->next;
		else
			break ;
		i++;
	}
	return (t);
}

t_list	*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i)
{
	int		n_args;
	int		local_i;

	local_i = 0;
	if (i == -1)
	{
		t->single_cmd[0] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[0]->before_sep = '\0';
		return (smashed_cmd);
	}
	n_args = count_args_in_cmd(smashed_cmd);
	printf("n_args = %d\n", n_args);
	if (i > 0)
	{
		t->single_cmd[i] = malloc(sizeof(t_parsed_command) * 1);
		t->single_cmd[i]->before_sep = t->single_cmd[i - 1]->after_sep;
	}
	t->single_cmd[i]->args = malloc(sizeof(char *) * n_args + 1);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == '\0')
		{
			printf("I don't have such null flags\n");
			return (NULL);
		}
		if (smashed_cmd->flag == 'c')
		{
			t->single_cmd[i]->args[local_i++] = (char *)smashed_cmd->content;
		}
		else
		{
			//separate function with delabrate work
			if (smashed_cmd->flag == 'g' || smashed_cmd->flag == 'a')
			{
				fill_outliar_redirected_cmd(smashed_cmd, t, &i, &local_i);
			}
			t->single_cmd[i]->after_sep = smashed_cmd->flag;
			break ;
		}
		smashed_cmd = smashed_cmd->next;
	}
	t->single_cmd[i]->args[local_i] = NULL;
	t->single_cmd[i]->cmd = t->single_cmd[i]->args[0];
	t->single_cmd[i]->path = decide_rel_or_abs_path(t->single_cmd[i]->cmd);
	if (!smashed_cmd)
		t->single_cmd[i]->after_sep = '\0';
	return (smashed_cmd);
}

void	fill_outliar_redirected_cmd(
	t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	int	after_red;
	int	j;

	after_red = 0;
	j = 0;
	after_red = count_outliar_redire(smashed_cmd);
	if (after_red == 0)
		return ;
	t->single_cmd[*i + 1] = malloc(sizeof(t_parsed_command) * 1);
	if (!t->single_cmd[*i + 1])
		return ;
	fill_redirec_outliar_cmd_hard_coded(t, i, smashed_cmd);
	smashed_cmd = smashed_cmd->next;
	while (j < after_red)
	{
		smashed_cmd = smashed_cmd->next;
		if(!smashed_cmd || smashed_cmd->flag != 'c')
			break ;
		t->single_cmd[*i]->args[(*local_i)++] = (char *)smashed_cmd->content;
		j++;
	}
}

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

char	decide_rel_or_abs_path(char *cmd)
{
	char	decision;

	if (cmd[0] == '/')
		decision = 'a';
	else
		decision = 'r';
	return (decision);
}

int	count_args_in_cmd(t_list *smashed_cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = smashed_cmd;
	if (!tmp)
		return (0);
	while (tmp->flag != 'c')
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->flag == 'c')
			i++;
		else
		{
			// printf("instead of %d  ", i);
			return (i + count_outliar_redire(tmp));
		}
		tmp = tmp->next;
	}
	return (i);
}

//expand this one to include the take and heredoc if needed
//the i = -1 is potential error for segfualts check for it
int	count_outliar_redire(t_list *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp)
		return (0);
	i = -1;
	if (tmp->flag == 'a' || tmp->flag == 'g')
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
		printf("/nOutliar redirects cmds %d\n", i);
		return (i);
	}
	return (0);
}
/*
t_pipes	*parsing_piped_cmd(char *cmd)
{
	t_parsed_command	*one_cmd;
	t_pipes				*t;
	t_list				*smashed_cmd;
	int					i;

	i = 0;
	t = NULL;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd);
	init_one_cmd(one_cmd);
	one_cmd->before_sep = '\0';
	while(smashed_cmd)
	{
		printf("New parsing in progress");
		smashed_cmd = smashed_cmd->next;
	exit(1);
	}
	return (t);
}

void	init_one_cmd(t_parsed_command *one_cmd)
{
	one_cmd->before_sep = '\0';
	one_cmd->cmd = NULL;
	one_cmd->args = NULL;
	one_cmd->env = NULL;
	one_cmd->splitted_cmd = NULL;
	one_cmd->after_sep = '\0';
	one_cmd->path = '\0';
	one_cmd->index = 0;
	return (one_cmd);
}
*/
/*
t_pipes	*parsing_piped_cmd(char *cmd)
{
	t_pipes	*t;
	char	**cmd_arr;
	int		i;

	i = 0;
	cmd_arr = ft_split(cmd, '|');
	while (cmd_arr[i++])
		;
	t = malloc(sizeof(t_pipes) * 1);
	if (!t)
		return (NULL);
	t->single_cmd = malloc(sizeof (t_parsed_command *) * i);
	if (!t->single_cmd)
		return (NULL);
	i = 0;
	while (cmd_arr[i])
	{	
		t->single_cmd[i] = parse_one_cmd(cmd_arr[i]);
		t->single_cmd[i]->index = i;
		i++;
	}
	t->single_cmd[i] = NULL;
	t->npipes = i;
	return (t);
}
*/
//waiting for the magical function to ignore what is inside the "" and ''
