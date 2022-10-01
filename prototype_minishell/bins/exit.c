/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/01 08:47:23 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(struct t_parsed_command *t, int exit_shell)
{
	exit_shell = 1;
	(void)t;
	exit(1);
	printf("%d", exit_shell);
	// if (t)
	// 	free(t);
}
