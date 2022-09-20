/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/20 07:03:18 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_one_cmd(char *command)
{
	int						pid;
	struct t_parsed_command	*t;

	t = parsing(command);
	if (!t)
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid  == 0)
	{
		execve(t->cmd, t->args, t->env);
	}
	else
	{
		wait(NULL);
	}
	free_cmd(t);
}
