/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/17 10:09:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO free all the malloced staff after pipes inshalla
//do function to parse the pipe, return pipe count ant splitted piped cmd

//check the single cmd for errors like / > < ;
//make fuction to scan the smashed list for the silly syntax and parsing errors
//Inshalla in the morning
//use strdup to fill the cmds then free the smashe_cmd linked list before returning 

t_pipes	*parsing_piped_cmd(char *cmd, t_list *env, int *exit_status)
{
	t_list				*smashed_cmd;
	t_pipes				*t;
	int					n_cmds;
	int					i;

	i = 0;
	t = NULL;
	n_cmds = 0;
	smashed_cmd = NULL;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd, env, exit_status);
	n_cmds = count_cmds(smashed_cmd);
	
forens_printf("\nparing_piped_cmd:\n----------\n");
forens_printf("n_cmds = %d\n", n_cmds);
	t = init_t_struct(t, n_cmds, smashed_cmd);
	if (t->parse_error != 0)
		return (t);
	malloc_single_cmd_in_t_piped_cmd(t, i);
	while (smashed_cmd)
	{
forens_printf("round %d\n", i);
		smashed_cmd  = fill_cmd(smashed_cmd, t, i);
forens_printf("i = %d  ", i);
		if (smashed_cmd)
			smashed_cmd = smashed_cmd->next;
		else
			break ;
		i++;
	}
	if (smashed_cmd)
		ft_lstclear(&smashed_cmd, del);
	return (t);
}

t_pipes	*init_t_struct(t_pipes *t, int n_cmds, t_list *smashed_cmd)
{
	forens_printf("inititalizing t_pipes\n");
	t = malloc(sizeof(t_pipes) * 1);
	if (!t)
		return (NULL);
	t->parse_error = scan_cmd_for_parsing_errors(smashed_cmd);
	if (smashed_cmd->flag < 30 || t->parse_error != 0)
	{
		forens_printf("filling erro with local code %d\n", (int)smashed_cmd->flag);
		if (smashed_cmd->flag == 2 || t->parse_error == 2)
			fill_errored_pipe(t, 2, smashed_cmd);
		else if (smashed_cmd->flag == 1 || t->parse_error == 1)
			fill_errored_pipe(t, 1, smashed_cmd);
		else if (smashed_cmd->flag == 3 || t->parse_error == 3)
			fill_errored_pipe(t, 3, smashed_cmd);
	forens_printf("inititalization end with error %d\n", (int)smashed_cmd->flag);
		return (t);
	}
	t->npipes = n_cmds;
	if (smashed_cmd->flag != 'c' && n_cmds == 1)
		t->single_cmd = malloc(sizeof(t_parsed_command *) * n_cmds + 2);
	else
		t->single_cmd = malloc(sizeof(t_parsed_command *) * n_cmds + 1);
	if (!t->single_cmd)
		return (NULL);
	forens_printf("inititalization t_pipe success\n");
	return (t);
}

t_list	*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i)
{
	// int		n_args;
	int		local_i;

	// n_args = init_fill_cmd(&local_i, &i, t, smashed_cmd);
	init_fill_cmd(&local_i, &i, t, smashed_cmd);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == '\0')
		forens_printf("I don't have such null flags\n");
		if (smashed_cmd->flag == 'c')
			t->single_cmd[i]->args[local_i++] = (char *)smashed_cmd->content;
		else
		{
			if (smashed_cmd->flag == 'g' || smashed_cmd->flag == 'a')
				fill_outliar_redirected_cmd(smashed_cmd, t, &i, &local_i);
			else if (smashed_cmd->flag == 't')
				fill_outliar_input(smashed_cmd, t, &i, &local_i);
			else if (smashed_cmd->flag == 'h')
				// fill_outliar_heredoc(smashed_cmd, t, &i, &local_i); // under construction
			if (!smashed_cmd)
				return (smashed_cmd);
			t->single_cmd[i]->after_sep = smashed_cmd->flag;
			break ;
		}
		smashed_cmd = smashed_cmd->next;
	}
forens_printf("decide_rel_abs_fill_cmd_null_arg i = %d, local_i = %d\n", i, local_i);
	decide_rel_abs_fill_cmd_null_arg(smashed_cmd, t, i, local_i);
	return (smashed_cmd);
}

/*
Outliar cases:

Creates the file.txt and put the echo cmd output inside it
	>file.txt echo is this going to be printed
	cat file.txt
	is this going to be printed
	
Create file.txt and put in it echo hello hi
	echo hi > file.txt hello ho
the fill_redirec_outliar_cmd_hard_coded() do the following
	fill this part only  
	> file.txt
	
which means it fills the next command with > file.txt
before filling the current command okay
*/






/*
//Depricated function
//Important to keep as example for filling t_pipes methodology
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
	forens_printf("New parsing in progress");
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
