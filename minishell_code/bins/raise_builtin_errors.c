/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_builtin_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/22 20:52:19 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	raise_export_error(t_pipes *t, char *cmd, char flag)
{
	if (flag == 'v')
	{
		err_printf("minishell: export: `%s': not a valid identifier\n", cmd);
		t->parse_error = 30;
	}
	else
	{
		//clean 
		exit(1);
	}
}

void	unset_error(char *env_variable, int error_code,
			char throw, t_pipes * t)
{

	if (throw == 't')
	{
		//clean
		exit(error_code);
		if (t)
			(void)t;
	}
		err_printf("minishell: unset: `%s': not a valid identifier\n", env_variable);
}

void	cd_error(t_pipes *t, char *error_path, char flag)
{
	if (flag == 'p')
	{
		err_printf("cd: string not in pwd: %s\n", error_path);
	}
	else
	{
		err_printf("bash: cd: %s: No such file or directory\n", error_path);
	}
	t->parse_error = 10;
}
