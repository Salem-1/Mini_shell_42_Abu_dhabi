/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:19:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/05 23:52:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_echo(struct t_parsed_command *t)
{
	char	nl;
	int		i;
// //forens_printf("inside echo our cmd, t->cmd = ~%s~\n", t->cmd);
	i = tedous_n(t);
	nl = '\n';
	if (i != 1)
	{
		nl = '\0';
	}
	while (t->args[i])
	{
		printf("%s", t->args[i]);
		if (t->args[i + 1])
			printf(" ");
		i++;
	}
	printf("%c", nl);
}

int	tedous_n(struct t_parsed_command *t)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (t->args[i])
	{
		if (t->args[i][0] != '-')
			return (i);
		while (t->args[i][j])
		{
			if (t->args[i][j] != 'n')
				return (i);
			j++;
		}
		j = 1;
		i++;
	}
	return (i);
}