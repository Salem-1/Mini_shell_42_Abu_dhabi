/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:55:31 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/30 11:27:04 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(struct t_parsed_command *t, t_list **env)
{
	char	*current_path;
	char	*buff;
	char	*new_path;

	buff = malloc(sizeof(char) * 4089);
	if (!t->args[1])
		t->args[1] = ft_strdup(search_list(*env, ft_strdup("HOME"), 'p'));
	else if (t->args[2])
	{
		cd_error(t->args[1], 'p');
	}
	current_path = getcwd(buff, 4089);
	exec_local_export(current_path, env, 'o');
	if (chdir(t->args[1]) == -1)
	{
		cd_error(t->args[1], 'n');
	};
	new_path = getcwd(buff, 4089);
	exec_local_export(new_path, env, 'c');
	free(buff);
}

void	cd_error(char *error_path, char flag)
{
	if (flag == 'p')
	{
		printf("cd: string not in pwd: %s\n", error_path);
		printf("remeber to set the exit code to 1\n");
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n", error_path);
		printf("remeber to set the exit code to 1\n");
	}
}

//update old and new pwd
void	exec_local_export(char *local_var, t_list **env, char flag)
{
	char					*local_cmd;

	if (flag == 'c')
		local_cmd = ft_strjoin("export ", "PWD=");
	else
		local_cmd = ft_strjoin("export ", "OLDPWD=");
	local_cmd = ft_strjoin(local_cmd, local_var);
	execute_one_cmd(local_cmd,* env, 0);
}