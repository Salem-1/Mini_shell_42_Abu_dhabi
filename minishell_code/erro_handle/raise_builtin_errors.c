/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_builtin_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 09:13:26 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	raise_export_error(t_pipes *t, char *cmd, char flag)
{
	t->parse_error = 30;
	if (flag == 'c')
		exit(1);
	else
		err_printf("minishell: export: `%s': not a valid identifier\n", cmd);
}

void	unset_error(char *env_variable, int error_code,
			char throw, t_pipes *t)
{
	if (throw == 't')
	{
		exit(error_code);
		if (t)
			(void)t;
	}
	err_printf("minishell: unset: `%s': not a valid identifier\n", env_variable);
}

void	cd_error(t_pipes *t, char *error_path, char flag)
{
	if (flag == 'p')
		err_printf("cd: string not in pwd: %s\n", error_path);
	else if (flag == 'a')
		err_printf("bash: cd: too many arguments\n");
	else
		err_printf("bash: cd: %s: No such file or directory\n", error_path);
	t->parse_error = 10;
}

void	normal_execution_error(struct t_parsed_command *t,
		struct t_pipes *all_cmds, char **envp, int error)
{
	if (!t)
		return ;
	err_printf("minishell: %s: %s\n", t->cmd, strerror(error));
	if (envp)
		free_split((void **)envp);
	if (error == 13)
		exec_exit(all_cmds, 126);
	exec_exit(all_cmds, 127);
}
