/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/09 06:13:30 by ahsalem          ###   ########.fr       */
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
	int					i;
	t_list				*smashed_head;

	i = 0;
	t = NULL;
	smashed_cmd = NULL;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd, env, exit_status);
	if (!smashed_cmd)
	{
		forens_printf("strangely enough we are returning NUll from parsing\n");
		return (NULL);
	}
	smashed_head = smashed_cmd;
	t = init_t_struct(t, smashed_cmd, env);
	if (t->parse_error != 0)
	{
		forens_printf("Inside parsing piped cmd, We have parse error, \n");
		return (t);
	}
	while (smashed_cmd)
	{
		smashed_cmd = fill_cmd(smashed_cmd, t, i);
		if (smashed_cmd)
			smashed_cmd = smashed_cmd->next;
		else
			break ;
		i++;
	}
	forens_printf("filling t finished\n");
	t->single_cmd[i + 1] = NULL;
	// parsing_laundry(t);
	forens_printf("laundry t finished\n");
	clean_env(smashed_head);
	free(cmd);
	forens_printf("returning t\n");
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
	// int		n_args;
	int		local_i;

	// n_args = init_fill_cmd(&local_i, &i, t, smashed_cmd);
forens_printf("#########################\ninside fill_cmd\n");
	init_fill_cmd(&local_i, &i, t, smashed_cmd);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == 'c')
		{
forens_printf("fill command type smashed_arg, i= %d, local_i = %d, smashed_cont = %s\n", i, local_i, smashed_cmd->content);
			t->single_cmd[i]->args[local_i++] = ft_strdup((char *)smashed_cmd->content);
		}
		else
		{
			if (smashed_cmd->flag == 'g' || smashed_cmd->flag == 'a')
			{
forens_printf("Have give ot append,i = %dm local i=%d, smashed = %s \n", i, local_i, smashed_cmd->content);
				fill_outliar_redirected_cmd(smashed_cmd, t, &i, &local_i);
			}
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
//forens_printf("decide_rel_abs_fill_cmd_null_arg i = %d, local_i = %d\n", i, local_i);
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
	//forens_printf("New parsing in progress");
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
