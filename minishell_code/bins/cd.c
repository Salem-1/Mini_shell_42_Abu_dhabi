/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:55:31 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/05 20:19:49 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	flag usage:
	t     Throw an error
	s     Silent the error
*/
int	exec_cd(struct t_parsed_command *t, t_list **env, t_pipes * all_cmds, int flag)
{
	char	*current_path;
	char	*old_path;
	char	*buff;
	char	*destination;

	destination = t->args[1];
	current_path = NULL;
	old_path = NULL;
	(void) all_cmds;
	buff = malloc(sizeof(char) * 4089);
	if (!buff)
		return (1);
	if (!destination)
		destination = search_list(*env, "HOME", 'p');
	else if (t->args[2])
	{
		if (flag == 't')
			cd_error(all_cmds, t->args[1], 'p');
		free(buff);
		return (1);
	}
	old_path = ft_strdup(getcwd(buff, 4089));
	if (chdir(destination) != 0)
	{
		if (flag == 't')
			cd_error(all_cmds, destination, 'n');
		free(buff);
		free(old_path);
		return (1);
	}
	current_path = ft_strdup(getcwd(buff, 4089));
	fill_old_and_current_pwd(env, old_path, current_path);
	free(buff);
	return (0);
}

void	fill_old_and_current_pwd(
		t_list **env, char *current_path, char *old_path)
{
	t_list	*old_node;
	t_list	*current_node;

	old_node = search_env(*env, "PWD", 'c', 't');
	current_node = search_env(*env, "OLDPWD", 'c', 't');
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
	execute_one_cmd(local_cmd, *env, 0);
}