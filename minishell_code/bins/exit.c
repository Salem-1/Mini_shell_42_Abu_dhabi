/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:56:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 07:17:38 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_exit(struct t_pipes *all_cmds, int exit_shell)
{
	char	**args;
	int		len;

	args = all_cmds->single_cmd[0]->args;
	len = length_of_larger_string(args[0], "exit");
	if (!all_cmds)
		len++;
	else if (all_cmds->npipes == 1
		&& !ft_strncmp(args[0], "exit", len) && !args[1])
	{
		clean_env(all_cmds->env);
		flush_pipes(all_cmds);
		exit(249);
	}
	clean_env(all_cmds->env);
	flush_pipes(all_cmds);
	exit(exit_shell);
}

int	exec_exit_in_parent(int *i, struct t_pipes *t)
{
	int	exit_code;

	exit_code = 1;
	if (t->single_cmd[*i]->args[1] == NULL)
		exit_code = 0;
	else if (t->single_cmd[*i]->args[1])
	{
		if (t->single_cmd[*i]->args[2] != NULL)
			return (1);
		exit_code = 3;
		if (check_exit_arg(t->single_cmd[*i]))
			throw_error_in_exit(t, &exit_code, 255, 3);
		else
			exit_code = ft_atoi(t->single_cmd[*i]->args[1]);
	}
	close_files(t->fd, t->npipes);
	clean_env(t->env);
	flush_pipes(t);
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
			free_split((void **)single_cmd->env);
			clean_env(t->env);
			throw_error_in_exit(t, &exit_code, 1, 4);
			exit(1);
		}
		exit_code = 3;
		if (check_exit_arg(single_cmd))
			throw_error_in_exit(t, &exit_code, 255, 3);
		else
			exit_code = ft_atoi(single_cmd->args[1]);
	}
	if (single_cmd->env)
		free_split((void **)single_cmd->env);
	clean_env(t->env);
	flush_pipes(t);
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
		if (!ft_isdigit(arg[k]))
			return (1);
		k++;
	}
	if (arg[0] == '+' || arg[0] == '-' || (k > 19 && ft_atoi(arg) < 0))
		return (1);
	else
		return (0);
}
