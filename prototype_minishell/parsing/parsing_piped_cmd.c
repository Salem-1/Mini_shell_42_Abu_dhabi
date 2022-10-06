/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/06 17:07:48 by ahsalem          ###   ########.fr       */
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

	t = NULL;
	n_cmds = 0;
	smashed_cmd = cmd_smasher(cmd, &smashed_cmd);
	n_cmds = count_cmds(smashed_cmd);
	printf("n_cmds = %d\n", n_cmds);
	smashed_cmd = NULL;
	// ft_lstclear(&smashed_cmd, del);
	return (t);
}

int	count_cmds(t_list *cmd)
{
	t_list	*tmp;
	int		n;

	n = 1;
	tmp = cmd;
	while(tmp)
	{
		printf("flag = %c arg = ~%s~,\n", tmp->flag, (char *)tmp->content);
		if (tmp->flag != 'c')
			n++;
		tmp = tmp->next;
	}
	return (n);
	
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
int	is_piped(char *cmd)
{
	static char *separeators[5] = {"|", ">", "<", "<<", ">>"};
	int			i;
	int			len_cmd;

	i = 0;
	len_cmd = ft_strlen(cmd);
	while (i < 5)
	{
		if (ft_strnstr(cmd, separeators[i], len_cmd) != NULL)
			return (1);
		i++;
	}
	return (0);
}