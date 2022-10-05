/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:10:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/01 13:54:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO free all the malloced staff after pipes inshalla
//do function to parse the pipe, return pipe count ant splitted piped cmd

//modify this to handle other sep operations like > < >> <<
//mdoify the split to ignore what is inside the "" and ''
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