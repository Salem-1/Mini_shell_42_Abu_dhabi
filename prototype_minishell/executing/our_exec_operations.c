/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exec_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:21:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 20:50:32 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_our_executable(struct t_parsed_command *t, t_list *env)
{
	size_t	len;
	char	*our_execs[7]= {"env", "pwd", "export", "unset", "cd", "exit", "echo"};
	int		i;

	i = 0;
	while (i < 7)
	{
		len = length_of_larger_string(t->cmd, our_execs[i]);
		if (!ft_strncmp(t->cmd, our_execs[i], len))
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
		exec_cd(t, &env);
	len = length_of_larger_string(t->cmd, "echo");
	if (!ft_strncmp(t->cmd, "echo", len))
		exec_echo(t);
}
