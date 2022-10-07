/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:20:20 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/07 06:24:22 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_list *cmd)
{
	t_list	*tmp;
	int		n;

	n = 1;
	tmp = cmd;
	while (tmp)
	{
		printf("flag = %c arg = ~%s~,\n", tmp->flag, (char *)tmp->content);
		if (tmp->flag != 'c')
			n++;
		tmp = tmp->next;
	}
	return (n);
}

int	is_piped(char *cmd)
{
	static char	*separeators[5] = {"|", ">", "<", "<<", ">>"};
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

t_pipes	*init_t_struct(t_pipes *t,int n_cmds)
{
	t = malloc(sizeof(t_pipes) * 1);
	if (!t)
		return (NULL);
	t->npipes = n_cmds;
	t->single_cmd = malloc(sizeof(t_parsed_command *) * n_cmds + 1);
	if (!t->single_cmd)
		return (NULL);
	return (t);
}
