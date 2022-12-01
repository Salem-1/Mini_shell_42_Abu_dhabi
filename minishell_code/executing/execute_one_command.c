/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 13:30:42 by ahsalem          ###   ########.fr       */
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
// */
int	execute_one_cmd(char *command, t_list *t_env, int exit_shell)
{
	struct t_parsed_command	*t;
	int						pid;
	int						len;

	t = parse_one_cmd(command);
	if (!t)
		return (0);
	len = length_of_larger_string(t->cmd, "exit");
	if (!t->args[1] && !ft_strncmp(t->cmd, "exit", len))
	{
		exec_exit(NULL, exit_shell);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		just_execve(t, t_env, NULL);
	}
	else
		wait(NULL);
	return (0);
}

void	just_execve(struct t_parsed_command *t,
			t_list *t_env, struct t_pipes *all_cmds)
{
	char		**envp;
	char		*old_cmd;

	old_cmd = NULL;
	envp = NULL;
	if (t_env)
	{
		envp = join_env(t_env);
		t->env = envp;
	}
	if (!t->cmd)
		exec_exit(all_cmds, 0);
	if (is_in_our_executable(t, t_env, all_cmds, envp))
	{
		free_split((void **)envp);
		exec_exit(all_cmds, 0);
	}
	else if (t->path == 'r')
	{
		old_cmd = t->cmd;
		t->cmd = search_path_for_bin(ft_low(t->cmd), t_env);
	}
	executing_non_builtin(all_cmds, t, envp, old_cmd);
	exec_exit(all_cmds, 0);
}

void	executing_non_builtin(t_pipes *all_cmds,
		struct t_parsed_command *t, char **envp, char *old_cmd)
{
	extern int	errno ;
	int			error;

	error = 0;
	if (!t->cmd)
	{
		err_printf("minishell: %s: No such file or directory\n", old_cmd);
		free_split((void **)envp);
		exec_exit(all_cmds, 127);
	}
	else
	{
		if (execve(t->cmd, t->args, envp) == -1)
		{
			error = errno;
			normal_execution_error(t, all_cmds, envp, error);
		}
	}
}

char	*search_path_for_bin(char *split_command_0, t_list *t_env)
{
	char	**pathes;
	char	*searched_path;
	int		i;

	i = -1;
	searched_path = NULL;
	pathes = get_path(t_env);
	if (!pathes)
		return (NULL);
	while (pathes[++i])
	{
		searched_path = refractor_searched_path(
				searched_path, pathes, split_command_0, i);
		if (access(searched_path, X_OK) == 0)
		{
			free_split((void **)pathes);
			return (searched_path);
		}
	}
	if (searched_path)
		free(searched_path);
	free_split((void **)pathes);
	return (NULL);
}

char	*refractor_searched_path(
		char *searched_path, char **pathes, char *split_command_0, int i)
{
	char	*add_slash;

	add_slash = NULL;
	if (searched_path)
		free(searched_path);
	add_slash = ft_strjoin(pathes[i], "/");
	searched_path = env_strjoin(add_slash, split_command_0,
			ft_strlen(add_slash) + ft_strlen(split_command_0));
	return (searched_path);
}
