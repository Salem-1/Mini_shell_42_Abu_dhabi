/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:39:51 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/10 18:51:15 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lets_heredoc(int **fd, int *i, struct t_pipes *t)
{
	char	*line;
	char	*delim;
	size_t	len;

	len = 0;
	if (!t->single_cmd[*i + 1] || t->single_cmd[*i + 1]->cmd == NULL)
		printf("throw heredoc error and exit\n");
	delim = t->single_cmd[*i + 1]->cmd;

	line = readline("heredoc> ");
	len = length_of_larger_string(line, delim);
	while (ft_strncmp(line, delim, len) != 0)
	{
		write(fd[*i][1], line, ft_strlen(line));
		write(fd[*i][1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
		len = length_of_larger_string(line, delim);
	}
	free(line);

	//do it's own execution algo
	//hekaito hekaya
}

void	output_append_execution(t_pipes *t, int **fd, int i)
{
	if (t->single_cmd[i]->after_sep == 'g')
	{
		close(fd[i][1]);
		fd[i][1] = open(t->single_cmd[i + 1]->cmd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[i][1] == -1)
			perror("open");
	}
	else if (t->single_cmd[i]->after_sep == 'a')
	{
		close(fd[i][i]);
		fd[i][1] = open(t->single_cmd[i + 1]->cmd,
				O_CREAT | O_APPEND |O_WRONLY, 0644);
		if (fd[i][1] == -1)
			perror("open");
	}
}

void	input_execution(t_pipes *t, int **fd, int i)
{
	if (t->single_cmd[i]->after_sep == 't')
	{
		close(fd[i][0]);
		fd[i][0] = open(t->single_cmd[i + 1]->cmd, O_RDONLY);
		if (fd[i][0] == -1)
			perror("open");
		dup2(fd[i][0], STDIN_FILENO);
		close_files(fd, t->npipes);
	}
}