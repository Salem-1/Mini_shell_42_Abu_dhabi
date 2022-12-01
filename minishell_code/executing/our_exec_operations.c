/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exec_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:21:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 16:21:23 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_our_executable(struct t_parsed_command *t,
	t_list *env, struct t_pipes *all_cmds, char **envp)
{
	size_t		len;
	int			i;
	static char	*our_execs[7] = {
		"env", "pwd", "export", "unset", "cd", "exit", "echo"};

	i = 0;
	while (i < 7)
	{
		len = length_of_larger_string(t->cmd, our_execs[i]);
		if (!ft_strncmp(t->cmd, our_execs[i], len))
		{
			exec_our_cmd(t, env, all_cmds, envp);
			return (1);
		}
		i++;
	}
	return (0);
}

//if executing in parent don't execute 
void	exec_our_cmd(struct t_parsed_command *t, t_list *env,
			struct t_pipes *all_cmds, char **envp)
{
	size_t	len;
	int		exit_code;

	exit_code = 0;
	len = length_of_larger_string(t->cmd, "echo");
	if (!ft_strncmp(t->cmd, "echo", len))
		exec_echo(t);
	len = length_of_larger_string(t->cmd, "exit");
	if (!ft_strncmp(t->cmd, "exit", len))
		exec_exit_in_child(t, all_cmds, 0);
	len = length_of_larger_string(t->cmd, "env");
	if (!ft_strncmp(t->cmd, "env", len))
		exec_env(&env);
	len = length_of_larger_string(t->cmd, "pwd");
	if (!ft_strncmp(t->cmd, "pwd", len))
		exec_pwd();
	len = length_of_larger_string(t->cmd, "export");
	if (!ft_strncmp(t->cmd, "export", len) && t->args[1] == NULL)
		exec_export(all_cmds, t, &env, 't');
	exit_code = exec_export_unset_cd_in_child(t, env, all_cmds, len);
	if (exit_code)
	{
		free_split((void **)envp);
		exec_exit(all_cmds, exit_code);
	}
}

//if executing here don't execute in the child okay
int	exec_exit_export_unset_cd_in_parent(
		int *i, struct t_pipes *t, t_list *env)
{
	int	exit_code;

	exit_code = 0;
	if (!can_exec_in_parent(i, t))
		return (0);
	if (!ft_strncmp(t->single_cmd[*i]->cmd, "exit", 5))
		exec_exit_in_parent(i, t);
	if (t->npipes == 1 || (t->npipes > 1))
	{
		if (!ft_strncmp(t->single_cmd[*i]->cmd, "cd", 3))
			exit_code = exec_cd(t->single_cmd[*i], &env, t, 't');
		else if (!ft_strncmp(t->single_cmd[*i]->cmd, "export", 7)
			&& t->single_cmd[*i]->args[1] != NULL)
			exit_code = exec_export(t, t->single_cmd[*i], &env, 'p');
		else if (!ft_strncmp(t->single_cmd[*i]->cmd, "unset", 6))
			exit_code = exec_unset(t->single_cmd[*i], &env, 1, 't');
	}
	return (exit_code);
}

int	can_exec_in_parent(int *i, struct t_pipes *t)
{
	int	redirec;

	redirec = 0;
	if (!t->single_cmd[*i] || !t->single_cmd[*i]->cmd)
		return (0);
	while (t->single_cmd[redirec] && redirec < t->npipes)
	{
		if (t->single_cmd[redirec]->after_sep == 'p'
			|| t->single_cmd[redirec]->before_sep == 'p' )
			return (0);
		redirec++;
	}
	return (1);
}

/*
	now cd unset export should execute once, weather in parent or child
*/
int	exec_export_unset_cd_in_child(struct t_parsed_command *t, t_list *env,
			struct t_pipes *all_cmds, int len)
{
	int	there_is_pipe;
	int	redirec;

	redirec = 0;
	there_is_pipe = 0;
	while (all_cmds->single_cmd[redirec] && redirec < all_cmds->npipes)
	{
		if (all_cmds->single_cmd[redirec]->after_sep == 'p'
			|| all_cmds->single_cmd[redirec]->before_sep == 'p' )
			there_is_pipe = 1;
		redirec++;
	}
	len = length_of_larger_string(t->cmd, "export");
	if (!there_is_pipe)
		return (0);
	if (!ft_strncmp(t->cmd, "export", len))
		exec_export(all_cmds, t, &env, 't');
	len = length_of_larger_string(t->cmd, "unset");
	if (!ft_strncmp(t->cmd, "unset", len))
		return (exec_unset(t, &env, 1, 't'));
	len = length_of_larger_string(t->cmd, "cd");
	if (!ft_strncmp(t->cmd, "cd", len))
		return (exec_cd(t, &env, all_cmds, 't'));
	return (0);
}

//remember to protect the env variables in the linked list 
//to avoid segfaults and invalid free staff