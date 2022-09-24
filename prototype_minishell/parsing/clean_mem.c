/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:19:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/22 21:20:46 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_parsed_command	*t)
{
	int	i;

	i = 0;
	while (t->splitted_cmd[i])
	{
		free(t->splitted_cmd[i++]);
	}
	free(t);
}
