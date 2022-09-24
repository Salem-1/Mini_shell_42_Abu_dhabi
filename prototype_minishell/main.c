/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/23 07:56:18 by ahsalem          ###   ########.fr       */
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
		if (cmd && cmd_not_empty(cmd))
		{
			add_history(cmd);
			execute_one_cmd(cmd, t_env);
			free(cmd);
		}
	}
}

int	cmd_not_empty(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (!ft_isspace(&cmd[i]))
			return (1);
		i++;
	}
	return (0);
}