/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 06:48:46 by ahsalem          ###   ########.fr       */
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

t_list	*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i)
{
	int		n_args;
	int		local_i;

	local_i = 0;
	n_args = count_args_in_cmd(smashed_cmd);
	printf("Single_cmd n_args = %d\n", n_args);
	malloc_single_cmd_in_t_piped_cmd(t, i);
	t->single_cmd[i]->args = malloc(sizeof(char *) * n_args + 1);
	while (smashed_cmd)
	{
		if (smashed_cmd->flag == '\0')
		{
			printf("I don't have such null flags\n");
			return (NULL);
		}
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
	t->single_cmd[i]->args[local_i] = NULL;
	printf("Am I seg here 1\n");
	t->single_cmd[i]->cmd = t->single_cmd[i]->args[0];
	printf("Am I seg here 2 cmd = %s i = %d, local_i = %d \n", t->single_cmd[i]->cmd, i, local_i);
	t->single_cmd[i]->path = decide_rel_or_abs_path(t->single_cmd[i]->cmd);
	printf("Am I seg here 3\n");
	if (!smashed_cmd)
		t->single_cmd[i]->after_sep = '\0';
	printf("Am I seg here 4\n");
	return (smashed_cmd);
}
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

void	fill_outliar_input(t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
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
		
		printf("###Calling case %s 1\n", t->single_cmd[*i]->cmd);
		return ;
	}
}
/*
void	case_input_file_cat_otherfiles(t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	smashed_cmd = smashed_cmd->next->next;
	t->single_cmd[*i]->args = malloc(sizeof(char *) * after_red);
	while ( smashed_cmd && j < after_red - 1)
	{
		if (smashed_cmd->flag == 'c')
			t->single_cmd[*i]->args[j] = (char *)smashed_cmd->content;
		else
			break;
		j++;
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
/*
	convert 
	< file.txt cat
	to 
	cat < file.txt
*/

void	case_input_file_cat(t_list *smashed_cmd, t_pipes *t, int *i, int *local_i)
{
	t->single_cmd[*i]->after_sep = 't';
	t->single_cmd[*i]->args = malloc(sizeof(char *) * 2);
	t->single_cmd[*i]->args[0] =
		(char *)smashed_cmd->next->next->content;
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
