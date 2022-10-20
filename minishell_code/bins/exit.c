/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/20 19:42:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(struct t_pipes *all_cmds, int exit_shell)
{
	char	**args;
	int		len;

	args = all_cmds->single_cmd[0]->args;
	forens_printf("should exit with code%d\n", exit_shell);
	// flush_pipes(all_cmds);
	len = length_of_larger_string(args[0], "exit");
	if (all_cmds->npipes == 1 && !ft_strncmp(args[0], "exit", len) && !args[1])
	{
		//remember to flush pipes
		exit(249);
	}
	//flush pipes
	exit(exit_shell);
}


// int	parse_exit_argumetn(t_pipes *t, int i, int *exitshell)
// {
// 	int	last_exit_code;
// 	int	i;

// 	i = 0;
// 	last_exit_code = 0;
// 	if (!t->single_cmd[i]->args[1])
// 		return (*exitshell);
// 	else if (!t->single_cmd[i]->args[3] != NULL)
// 	{
// 		throw_parser_error(t, 1);
// 		return (1);
// 	}
// 	else
// 	{
// 		if (!t->single_cmd[i]->args[2][i] == '+'
// 			|| !t->single_cmd[i]->args[2][i] == '-' )
// 			i++;
// 		while (t->single_cmd[i]->args[2][i])
// 		{
// 			if (!ft_isdigit(t->single_cmd[i]->args[2][i]))
// 			{
// 				throw_parser_error(t, 1);
// 				return (1);
// 			}
// 			i++;
// 		}
// 	}
// }
