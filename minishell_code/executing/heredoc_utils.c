// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredoc_utils.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/10/18 17:40:50 by ahsalem           #+#    #+#             */
// /*   Updated: 2022/12/03 08:01:21 by ahsalem          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// int	skip_multiple_heredocs(t_pipes *t, int i)
// {
// 	int	original_i;

// 	original_i = i;
// 	while (t->single_cmd[i]->after_sep == 'h')
// 		i++;
// 	i--;
// 	if (i != original_i)
// 		cpy_cmd(t->single_cmd[original_i], t->single_cmd[i]);
// 	return (i);
// }

// void	init_s_for_heredoc(t_smash_kit *s, char *filled_heredoc, t_list *env)
// {
// 	s->start = 0;
// 	s->end = ft_strlen(filled_heredoc);
// 	s->env = env;
// }

// char	*expand_heredoc_var(t_smash_kit *s, char *cmd, int *exit_status)
// {
// 	t_dollar_expansion_kit	e;
// 	char					*free_sub_smashed;

// 	e.tmp = NULL;
// 	e.end = 0;
// 	e.new_arg = NULL;
// 	e.smashed_arg = ft_substr(cmd, s->start, s->end - s->start + 1);
// 	free_sub_smashed = e.smashed_arg;
// 	e.start = ft_strnchr(e.smashed_arg, '$');
// 	if (e.start == -1)
// 	{
		
// 		return (e.smashed_arg);
// 	}
// 	e.end = get_end_of_var(e.smashed_arg + e.start + 1);
// 	while (e.start != -1)
// 		e.start = dollar_expan_operation_loop(&e, s, exit_status);
// 	if (free_sub_smashed)
// 		free(free_sub_smashed);
// 	return (e.new_arg);
// }
