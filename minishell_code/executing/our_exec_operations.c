/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exec_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:21:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/22 20:50:44 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_our_executable(
	struct t_parsed_command *t, t_list *env, struct t_pipes *all_cmds)
{
	size_t	len;
	char	*our_execs[7]= {
		"env", "pwd", "export", "unset", "cd", "exit", "echo"};
	int		i;

	i = 0;
	while (i < 7)
	{
		len = length_of_larger_string(t->cmd, our_execs[i]);
		if (!ft_strncmp(t->cmd, our_execs[i], len))
		{
			exec_our_cmd(t, env, all_cmds);
			return (1);
		}
		i++;
	}
	return (0);
}

void	exec_our_cmd(struct t_parsed_command *t, t_list *env,
			struct t_pipes *all_cmds)
{
	size_t	len;

	len = length_of_larger_string(t->cmd, "env");
	if (!ft_strncmp(t->cmd, "env", len))
		exec_env(&env);
	len = length_of_larger_string(t->cmd, "pwd");
	if (!ft_strncmp(t->cmd, "pwd", len))
		exec_pwd();
	len = length_of_larger_string(t->cmd, "export");
	if (!ft_strncmp(t->cmd, "export", len))
		exec_export(all_cmds, t, &env, 't');
	len = length_of_larger_string(t->cmd, "unset");
	if (!ft_strncmp(t->cmd, "unset", len))
		unset_error(NULL, exec_unset(t, &env, 1, 't'), 't', all_cmds);
	len = length_of_larger_string(t->cmd, "cd");
	if (!ft_strncmp(t->cmd, "cd", len))
		cd_exit_with_code(all_cmds);
		// exec_cd(t, &env, all_cmds, 't');
	len = length_of_larger_string(t->cmd, "echo");
	if (!ft_strncmp(t->cmd, "echo", len))
		exec_echo(t);
	len = length_of_larger_string(t->cmd, "exit");
	if (!ft_strncmp(t->cmd, "exit", len))
		exec_exit_in_child(t, all_cmds, 0);
}

void	vis_list(t_list **env, char is_env_or_exp)
{
	t_list	*tmp;

	if (!env)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (is_env_or_exp == 'x')
		{
			if ((tmp)->flag == 'v')
				printf("declare -x %s=\"%s\"\n", tmp->key_val[0], tmp->key_val[1]);
			else
				printf("declare -x %s\n", tmp->key_val[0]);
		}
		else if (((tmp)->flag) == 'v')
			printf("%s=%s\n", tmp->key_val[0], tmp->key_val[1]);
		tmp = tmp->next;
	}
}

void	exec_exit_export_unset_cd_in_parent(
		int *i,  struct t_pipes *t, t_list *env, int *exit_status)
{
	int	redirec;

	redirec = 0;
	if (!t->single_cmd[*i] || !t->single_cmd[*i]->cmd)
		return ;
	while (t->single_cmd[redirec] && redirec < t->npipes)
	{
		if (t->single_cmd[redirec]->after_sep == 'p'
			|| t->single_cmd[redirec]->after_sep == 'g'
			|| t->single_cmd[redirec]->after_sep == 'a')
			return ;
		redirec++;
	}
	if (!ft_strncmp(t->single_cmd[*i]->cmd, "cd", 3))
		*exit_status = exec_cd(t->single_cmd[*i], &env, t, 't');
	else if (!ft_strncmp(t->single_cmd[*i]->cmd, "export", 7))
		exec_export(t, t->single_cmd[*i], &env, 's');
	else if (!ft_strncmp(t->single_cmd[*i]->cmd, "unset", 6))
		exec_unset(t->single_cmd[*i], &env, 1, 's');
	else if (!ft_strncmp(t->single_cmd[*i]->cmd, "exit", 5))
		exec_exit_in_parent(i, t);
}
