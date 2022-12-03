/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:40:50 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/03 08:09:56 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	remember to do this case
	<< delimeter cmd
	<< trash_delimter_and_heredoc cmd arg[1] arg[2]
	< input_file cmd
	< nonsense_input_sign cmd arg[1] arg[2] ...
*/

//no more heredocs in the execution
//remember to deduct the t->npipes -= heredocs;
int	if_there_is_heredoc_fill_it(t_pipes *t, t_list *env)
{
	int	i;
	int	count_heredocs;

	count_heredocs = 0;
	i = 0;
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->before_sep == 'h')
		{
			lets_heredoc(t, env, i);
			count_heredocs++;
		}
		i++;
	}
	return (0);
}

		//do the signal handling var here inshall
		//when it change return 1 to free t and break the 
		//execution and change exit code
int	lets_heredoc(t_pipes *t, t_list *env, int i)
{
	t_smash_kit	s;
	char		*line;
	char		*delim;
	char		*filled_heredoc;
	size_t		len;

	filled_heredoc = NULL;
	len = 0;
	delim = t->single_cmd[i]->args[0];
	line = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		init_s_for_heredoc(&s, line, env);
		line = expand_heredoc_var(&s, line, 0);
		len = length_of_larger_string(line, delim);
		if (!ft_strncmp(line, delim, len))
			break ;
		filled_heredoc = ft_expand_strjoin(filled_heredoc, line);
		filled_heredoc = ft_expand_strjoin(filled_heredoc, ft_strdup("\n"));
	}
	free(line);
	write(t->fd[i - 1][1], filled_heredoc,
		ft_strlen(filled_heredoc));
	free(filled_heredoc);
	return (0);
}

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

char	*expand_heredoc_var(t_smash_kit *s, char *cmd, int *exit_status)
{
	t_dollar_expansion_kit	e;
	char					*free_sub_smashed;

	e.tmp = NULL;
	e.end = 0;
	e.new_arg = NULL;
	e.smashed_arg = ft_substr(cmd, s->start, s->end - s->start + 1);
	free_sub_smashed = e.smashed_arg;
	e.start = ft_strnchr(e.smashed_arg, '$');
	if (e.start == -1)
		return (e.smashed_arg);
	e.end = get_end_of_var(e.smashed_arg + e.start + 1);
	while (e.start != -1)
		e.start = dollar_expan_operation_loop(&e, s, exit_status);
	if (free_sub_smashed)
		free(free_sub_smashed);
	return (e.new_arg);
}

// int	check_delim_end(
// 		char *line, t_smash_kit	*s, char *delim)
// {
// 	size_t	len;

// 	len = 0;
// 	line = expand_heredoc_var(s, line, 0);
// 	len = length_of_larger_string(line, delim);
// 	if (!ft_strncmp(line, delim, len))
// 		return (1);
// 	return (0);
// }

// void	save_heredoc_in_file_and_free_line(
// 	char *line, int i, t_pipes *t, char *filled_heredoc)
// {
// 	if (line != NULL)
// 		free(line);
// 	write(t->fd[i - 1][1], filled_heredoc, ft_strlen(filled_heredoc));
// 	free(filled_heredoc);
// }
