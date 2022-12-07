/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 09:10:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 10:25:33 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_multiple_heredocs(t_pipes *t, int i)
{
	int	original_i;

	original_i = i;
	while (t->single_cmd[i]->after_sep == 'h')
		i++;
	i--;
	if (i != original_i)
		cpy_cmd(t->single_cmd[original_i], t->single_cmd[i]);
	return (i);
}

void	init_s_for_heredoc(t_smash_kit *s, char *filled_heredoc, t_list *env)
{
	s->start = 0;
	s->end = ft_strlen(filled_heredoc);
	s->env = env;
}

char	*append_to_heredoc_buffer(char *filled_heredoc, char *line)
{
	filled_heredoc = ft_expand_strjoin(filled_heredoc, line);
	return (ft_expand_strjoin(filled_heredoc, ft_strdup("\n")));
}

int	reached_delimeter(char *line, char *delim)
{
	size_t	len;

	len = 0;
	len = length_of_larger_string(line, delim);
	if (!ft_strncmp(line, delim, len))
		return (1);
	else
		return (0);
}
