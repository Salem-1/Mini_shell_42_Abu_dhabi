/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirect_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 03:09:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/25 03:22:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_and_redirect_errors(t_pipes *t, int i, int local_fd, int **fd)
{
	close(local_fd);
	close_files(fd, t->npipes);
	err_printf("minishell: green: Permission denied\n", t->single_cmd[i]->cmd);
	//clean
	exit(1);
}