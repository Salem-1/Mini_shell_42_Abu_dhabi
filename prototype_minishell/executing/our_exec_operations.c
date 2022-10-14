/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exec_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:21:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 15:01:57 by ahsalem          ###   ########.fr       */
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
		exec_export(t, &env);
	len = length_of_larger_string(t->cmd, "unset");
	if (!ft_strncmp(t->cmd, "unset", len))
		exec_unset(t, &env, 1);
	len = length_of_larger_string(t->cmd, "cd");
	if (!ft_strncmp(t->cmd, "cd", len))
		exec_cd(t, &env, all_cmds);
	len = length_of_larger_string(t->cmd, "echo");
	if (!ft_strncmp(t->cmd, "echo", len))
	{
		printf("should execute echo\n");
		exec_echo(t);
	}
	len = length_of_larger_string(t->cmd, "exit");
	if (!ft_strncmp(t->cmd, "exit", len))
		exec_exit(all_cmds, 0);
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