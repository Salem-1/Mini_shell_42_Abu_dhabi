/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/24 13:46:58 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check for empty and spaces only cmds not to execute or add to his

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_list	*t_env;

	cmd = NULL;
	t_env = NULL;
	if ((argc > 1 && argv) || (!envp))
	{
		printf("Error!\n./minishell  cannot take arguments\n");
		return (0);
	}
	t_env = parse_env(envp, t_env);
	while (1)
	{
		cmd = readline("minishel $> ");
		execution_operations(cmd, t_env);
	}
}