/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/25 16:32:51 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//all perror for debugging only delete them before submission
//debug the searching for path as follows
/*
printf environment varibles (visualize)
printf the fount PATH=/////.
printf the searching the path
printf when found or not
*/
void	execute_one_cmd(char *command, t_list *t_env)
{
	struct t_parsed_command	*t;
	int						pid;

	t = parse_one_cmd(command);
	if (!t)
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		just_execve(t, t_env);
	}
	else
	{
		wait(NULL);
	}
	free_cmd(t);
}

void	just_execve(struct t_parsed_command *t, t_list *t_env)
{
	char	**envp;
	char	*old_cmd;

	old_cmd = NULL;
	envp = NULL;
	envp = join_env(t_env);
	if (is_in_our_executable(t, t_env))
		return ;
	else if (t->path == 'r')
	{
		old_cmd = t->cmd;
		t->cmd = search_path_for_bin(t->cmd, t_env);
	}
	if (!t->cmd || (execve(t->cmd, t->args, envp) == -1))
	{
		printf("minishell: %s: command not found\n", old_cmd);
		return ;
	}
}

char	*search_path_for_bin(char *split_command_0, t_list *t_env)
{
	char	**pathes;
	char	*searched_path;
	char	*add_slash;
	int		i;

	i = -1;
	searched_path = NULL;
	add_slash = NULL;
	pathes = get_path(t_env);
	if (!pathes)
		return (NULL);
	while (pathes[++i])
	{
		add_slash = ft_strjoin(pathes[i], "/");
		searched_path = ft_strjoin(add_slash, split_command_0);
		free(add_slash);
		if (access(searched_path, X_OK) == 0)
		{
			free_split((void **)pathes);
			return (searched_path);
		}
	}
	free(searched_path);
	free_split((void **)pathes);
	return (NULL);
}