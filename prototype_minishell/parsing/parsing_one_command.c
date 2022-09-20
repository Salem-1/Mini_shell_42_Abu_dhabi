/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/20 07:02:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsed_command	*parse_one_cmd(char *command)
{
	struct t_parsed_command	*t;
	char					**split_command;

	split_commad = ft_split(command, ' ');
	if (!split_commad)
		return (NULL);
	t->cmd = &split_commad[0];
	t->args = split_commad++;
	t->env = NULL;
	t->split_commad = split_command;
}

void	free_cmd(struct t_parsed_command	*t)
{
	int	i;

	i = 0;
	while (t->split_command[i])
	{
		free(t->split_command[i++]);
	}
	free(t->split_command);
}