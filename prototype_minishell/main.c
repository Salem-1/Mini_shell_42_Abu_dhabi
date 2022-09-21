/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/20 09:24:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for empty and spaces only cmds not to execute or add to his

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	// printf("Bism Ellah Elrahman Elraheem");
	cmd = NULL;
	if (argc > 1 && argv)
	{
		printf("Error!\n./minishell  cannot take arguments\n");
		return (0);
	}
	while (1)
	{
		cmd = readline("minishel $> ");
		if (cmd )
		{
			// add_history(cmd); // the argv will be env later inshalla
			execute_one_cmd(cmd, envp);
			free(cmd);
		}
	}
}