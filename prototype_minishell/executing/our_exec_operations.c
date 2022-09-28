/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exec_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:21:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/28 08:19:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_our_executable(struct t_parsed_command *t, t_list *env)
{
	size_t	len;
	char	*our_execs[6]= {"env", "pwd", "export", "unset", "cd", "exit"};
	int		i;

	i = 0;
	while (i < 6)
	{
		len = length_of_larger_string(t->cmd, our_execs[i]);
		if (!strncmp(t->cmd, our_execs[i], len))
		{
			exec_our_cmd(t, env);
			return (1);
		}
		i++;
	}
	return (0);
}

void	exec_our_cmd(struct t_parsed_command *t, t_list *env)
{
	size_t	len;

	len = length_of_larger_string(t->cmd, "env");
	if (!strncmp(t->cmd, "env", len))
		exec_env(&env);
	len = length_of_larger_string(t->cmd, "pwd");
	if (!strncmp(t->cmd, "pwd", len))
		exec_pwd(env);
	len = length_of_larger_string(t->cmd, "export");
	if (!strncmp(t->cmd, "export", len))
		exec_export(t, &env);
	len = length_of_larger_string(t->cmd, "unset");
	if (!strncmp(t->cmd, "unset", len))
		exec_unset(t, &env, 1);
	len = length_of_larger_string(t->cmd, "cd");
	if (!strncmp(t->cmd, "cd", len))
		exec_cd(t, &env);
	len = length_of_larger_string(t->cmd, "exit");
	if (!strncmp(t->cmd, "exit", len))
		exec_exit(t, &env);
}
