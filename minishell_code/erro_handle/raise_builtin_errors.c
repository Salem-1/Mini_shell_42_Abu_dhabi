/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_builtin_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/07 11:58:44 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	raise_export_error(t_pipes *t, char *cmd, char flag)
{
	t->parse_error = 30;
	if (flag == 'c')
	{
		//don't forget to clean for memory leaks
		exit(1);
	}
	else
	{
		err_printf("minishell: export: `%s': not a valid identifier\n", cmd);
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

void	normal_execution_error(struct t_parsed_command *t,
		struct t_pipes *all_cmds, char **envp, int error)
{
	(void)all_cmds;
	if (!t)
		return ;
	// if (t->path == 'r' || t->cmd[0] == '\0')
	// // 	err_printf("minishell: %s: command not found\n", t->cmd);
	// // else
		err_printf("minishell: %s: %s\n", t->cmd, strerror(error));
	//consider flushing pipes here
	if (envp)
		free_split((void **)envp);
	if (error == 13)
		exec_exit(all_cmds, 126);
	exec_exit(all_cmds, 127);
}

void	throw_error_in_exit(
		t_pipes *t, int *exit_code, int error_code,int parse_error)
{
	int	convert_erro;

	convert_erro = error_code;
	t->parse_error = parse_error;
	close_files(t->fd, t->npipes);
	if (parse_error == 4)
	{
		throw_parser_error(t, &convert_erro);
		return ;
	}
	clean_env(t->env);
	throw_parser_error(t, &convert_erro);
	*exit_code = 255;
	exit (*exit_code);
}
