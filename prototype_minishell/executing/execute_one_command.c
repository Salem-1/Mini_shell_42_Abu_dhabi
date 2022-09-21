/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/21 11:46:53 by ahsalem          ###   ########.fr       */
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
void execute_one_cmd(char *command, char **envp)
{
	struct t_parsed_command	*t;
	int						pid;

	t = parse_one_cmd(command, envp);
	if (!t)
		return ;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid  == 0)
	{
		visualize_cmd(t);
		just_execve(t, envp);
	}
	else
	{
		wait(NULL);
	}
	free_cmd(t);
}

void	visualize_cmd(struct t_parsed_command *t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	printf("%s ", t->cmd);
	while (t->args[i])
	{
		printf("%s ", t->args[i]);
		i++;
	}
	printf("\n");
}

char	*search_path_for_bin(char *split_command_0, char **envp)
{
	char	**pathes;
	char	*searched_path;
	int		i;

	i = -1;
	searched_path = NULL;
	pathes = get_path(envp);
	if (!pathes)
		return (NULL);
	while (pathes[++i])
	{
		searched_path = ft_strjoin(pathes[i], split_command_0);
		if (access(searched_path, X_OK) == 0)
		{
			free_split(pathes);
			return (searched_path);
		}
		else
			perror("access");
	}
	free(searched_path);
	free_split(pathes);
	return (NULL);
}

void	just_execve(struct t_parsed_command	*t, char **envp)
{
	if (t->path != 'a')
		t->cmd = search_path_for_bin(t->cmd, envp);
	if (execve(t->cmd, t->args, NULL) == -1)
	{
		printf("minishell: %s: command not found\n", t->cmd);
		perror("execve");
	}
}