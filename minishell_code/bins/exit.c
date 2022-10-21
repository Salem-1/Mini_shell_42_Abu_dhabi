/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/21 10:29:49 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//throw the exit error hthere in case of multiple pipes
//refractor the error code in a separate function
//don't touch this function untill memory cleaning task
void	exec_exit(struct t_pipes *all_cmds, int exit_shell)
{
	char	**args;
	int		len;

	args = all_cmds->single_cmd[0]->args;
	forens_printf("should exit with code%d\n", exit_shell);
	// flush_pipes(all_cmds);
	len = length_of_larger_string(args[0], "exit");
	if (!all_cmds)
		len++;
	else if (all_cmds->npipes == 1 && !ft_strncmp(args[0], "exit", len) && !args[1])
	{
		//remember to flush pipes
		exit(249);
	}
	//flush pipes
	exit(exit_shell);
}

//throw the error message here in case of one pipe
int	exec_exit_in_parent(int *i,  struct t_pipes *t)
{
	int	exit_code;

	exit_code = 1;
	forens_printf("exec_exit_in parent :\n");
	if (t->npipes > 1)
		return (0);
	if (t->single_cmd[*i]->args[1] == NULL)
		exit_code = 0;
	else if (t->single_cmd[*i]->args[1])
	{
		if (t->single_cmd[*i]->args[2] != NULL)
		{
			//throw this exit code later inshalla in the upcoming 
			//exit code function geenrator
			// throw_error_in_exit(t, &exit_code, 1,4);
			return (1);
		}
		exit_code = 3;
		forens_printf("check_exit_arg:\n");
		if (check_exit_arg(t->single_cmd[*i]))
			throw_error_in_exit(t, &exit_code, 255, 3);
		else
			exit_code = ft_atoi(t->single_cmd[*i]->args[1]);
	}
	//clean
	exit(exit_code);
	return (0);
}

int	exec_exit_in_child(
		t_parsed_command *single_cmd, t_pipes *t, int exit_code)
{
	if (single_cmd->args[1] == NULL)
		exit_code = 0;
	else if (single_cmd->args[1])
	{
		if (single_cmd->args[2] != NULL)
		{
			err_printf("exit\n");
			throw_error_in_exit(t, &exit_code, 1, 4);
			//clean
			exit(1);
		}
		exit_code = 3;
		forens_printf("local_exit_ in childcheck_exit_arg:\n");
		if (check_exit_arg(single_cmd)) 
			throw_error_in_exit(t, &exit_code, 255, 3);
		else
			exit_code = ft_atoi(single_cmd->args[1]);
	}
	//clean
	exit(exit_code);
	return (0);
}

int	check_exit_arg(struct t_parsed_command *single_cmd)
{
	char	*arg;
	int		k;

	k = 0;
	arg = single_cmd->args[1];
	if (arg[k] == '+' || arg[k] == '-')
		k++;
	while (arg[k])
	{
		forens_printf("check_exit_arg char =  %c\n", arg[k]);
		if (!ft_isdigit(arg[k]))
			return (1);
		k++;
	}
	if (arg[0] == '+' || arg[0] == '-')
		return (1);
	else
		return (0);
}