/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:30:33 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 13:44:03 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_low(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

void	cpy_cmd(struct t_parsed_command *src, struct t_parsed_command *dst)
{
	int	i;

	i = 0;
	if (src->cmd)
		dst->cmd = src->cmd;
	free_split((void **)dst->args);
	while (src->args[i])
		i++;
	dst->args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (src->args[i])
	{
		dst->args[i] = ft_strdup(src->args[i]);
		i++;
	}
	dst->before_sep = src->before_sep;
	dst->after_sep = src->after_sep;
	dst->args[i] = NULL;
}
