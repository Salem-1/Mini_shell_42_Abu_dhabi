/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:30:33 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 09:45:52 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_low(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

void	cpy_cmd(struct t_parsed_command *src, struct t_parsed_command *dst)
{
	int	i;

	i = 0;
	if (src->cmd)
		dst->cmd = src->cmd;
	free_split((void **)dst->args);
	while (src->args[i])
		i++;
	dst->args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (src->args[i])
	{
		dst->args[i] = ft_strdup(src->args[i]);
		i++;
	}
	dst->before_sep = src->before_sep;
	dst->after_sep = src->after_sep;
	dst->args[i] = NULL;
}

int	init_exec_multiple_pipes_args(t_pipes *t, t_list *env)
{
	int	sig_or_not;

	sig_or_not = 0;
	t->fd = open_pipes(t->npipes, t->fd);
	sig_or_not = if_there_is_heredoc_fill_it(t, env);
	if (sig_or_not)
		return (-1);
	else
		return (0);
}

int	exec_loop(t_pipes *t,
	int *i, int *parent_exit_status)
{
	int	pid;

	if (*i == -1)
		return (3);
	pid = 0;
	if (t->single_cmd[*i]->after_sep == 'h')
		*i = skip_multiple_heredocs(t, *i);
	*parent_exit_status = exec_exit_export_unset_cd_in_parent(
			i, t, t->env);
	if (update_i_in_case_of_redirection(t, i))
		return (2);
	pid = fork();
	if (pid == 0)
	{
		piping_and_redirections(*i, t->fd, t, t->env);
		return (1);
	}
	if (t->single_cmd[*i]->after_sep == 't')
		*i = *i + 1;
	return (0);
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
