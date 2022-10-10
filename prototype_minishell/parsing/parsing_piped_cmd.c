/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 08:16:14 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO free all the malloced staff after pipes inshalla
//do function to parse the pipe, return pipe count ant splitted piped cmd

//check the single cmd for errors like / > < ;

//Inshalla in the morning
//use strdup to fill the cmds then free the smashe_cmd linked list before returning 

//refractor this file to be as follows
 //one file for normal cmds without redirections
 //test
 //one for pipes with all cases and I mean all cases okay?
 //test
 //one for output and append redirections only , deal?
 //test
 //one for input only, am I clear
 //test
 //one utils for the helper funtionss



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
	t = init_t_struct(t, n_cmds, smashed_cmd);
	malloc_single_cmd_in_t_piped_cmd(t, i);
	while (smashed_cmd)
	{
		printf("round %d\n", i);
		smashed_cmd  = fill_cmd(smashed_cmd, t, i);
		printf("i = %d  ", i);
		if (smashed_cmd)
			smashed_cmd = smashed_cmd->next;
		else
			break ;
		i++;
	}
	return (t);
}

//norm = n_lines this fun - 1
t_list	*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i)
{
	int		n_args;
	int		local_i;

	n_args = init_fill_cmd(&local_i, &i, t, smashed_cmd);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == '\0')
			printf("I don't have such null flags\n");
		if (smashed_cmd->flag == 'c')
			t->single_cmd[i]->args[local_i++] = (char *)smashed_cmd->content;
		else
		{
			if (smashed_cmd->flag == 'g' || smashed_cmd->flag == 'a')
				fill_outliar_redirected_cmd(smashed_cmd, t, &i, &local_i);
			else if (smashed_cmd->flag == 't')
				fill_outliar_input(smashed_cmd, t, &i, &local_i);
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
