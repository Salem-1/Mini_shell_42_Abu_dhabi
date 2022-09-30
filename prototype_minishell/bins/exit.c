/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 11:39:30 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(struct t_parsed_command *t, int exit_shell)
{
	exit_shell = 1;
	(void)t;
	// if (t)
	// 	free(t);
}
