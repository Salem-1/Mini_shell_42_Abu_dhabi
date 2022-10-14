/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:55:31 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/14 16:43:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(struct t_parsed_command *t, t_list **env, t_pipes * all_cmds)
{
	char	*current_path;
	char	*old_path;
	char	*buff;

	current_path = NULL;
	old_path = NULL;
	buff = malloc(sizeof(char) * 4089);
	if (!buff)
		return ;
	if (!t->args[1])
		t->args[1] = ft_strdup(search_list(*env, ft_strdup("HOME"), 'p'));
	else if (t->args[2])
	{
		printf("is this error triggered\n");
		cd_error(t->args[1], 'p');
		free(buff);
	}
	old_path = ft_strdup(getcwd(buff, 4089));
	printf("changing directory = %s\n", t->args[1]);
	if (chdir(t->args[1]) != 0)
	{
		printf("error in executing chdir, will kill this child\n");
		cd_error(t->args[1], 'n');
		free(buff);
		free(old_path);
		exec_exit(all_cmds, 1);
	}
	// exec_local_export(current_path, env, 'o');
	current_path = ft_strdup(getcwd(buff, 4089));
	printf("OLDPWD=%s\nPWD=%s\n", old_path, current_path);
	fill_old_and_current_pwd(env, old_path, current_path);
	// printf("cd is under maintainance for solving local exporting issues\n");
	// exec_local_export(current_path, env, 'c');
	free(buff);
}

void	fill_old_and_current_pwd(
		t_list **env, char *old_path, char *current_path)
{
	t_list	*old_node;
	t_list	*current_node;

	old_node = search_env(*env, "PWD", 'c');
	current_node = search_env(*env, "OLDPWD", 'c');
	if (old_node)
	{
		free(old_node->key_val[1]);
		old_node->key_val[1] = old_path;
	}
	if (current_node)
	{
		free(current_node->key_val[1]);
		current_node->key_val[1] = current_path;
	}
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
//pass it to the exection function as outside handmade command
void	exec_local_export(char *local_var, t_list **env, char flag)
{
	char					*local_cmd;

	if (flag == 'c')
		local_cmd = ft_strjoin("export ", "PWD=");
	else
		local_cmd = ft_strjoin("export ", "OLDPWD=");
	local_cmd = ft_strjoin(local_cmd, local_var);
	// exec_multiple_pipes(local_cmd, *env, 0);

	//end of new code
	execute_one_cmd(local_cmd, *env, 0);
}