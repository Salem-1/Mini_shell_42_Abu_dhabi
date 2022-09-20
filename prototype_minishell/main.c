/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/20 07:06:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*cmd;

	if (argc > 0)
	{
		return (1);
	}
	while (1)
	{
		cmd = readline("minishel $>");
		if (cmd )  //check for empty and spaces only cmds not to execute or add to his
		{
			add_history(cmd);
			execute_one_cmd(cmd);
		}
		free(cmd);
	}
}