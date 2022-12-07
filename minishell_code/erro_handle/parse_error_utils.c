/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:38:00 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/04 22:06:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_e_args(t_scan_parse_error *e, t_list *smashed_cmd)
{
	e->i = -1;
	e->current_flag = '\0';
	e->next_flag = '\0';
	e->next_next_flag = '\0';
	e->tmp = smashed_cmd;
}

void	remove_second_redirection(t_scan_parse_error *e)
{
	t_list	*delete_me;

	delete_me = e->tmp->next;
	e->tmp->next = e->tmp->next->next;
	ft_lstdelone(delete_me, del);
}

int	is_r_flag(char flag)
{
	if (flag == 'p' || flag == 'g' || flag == 't'
		|| flag == 'a' || flag == 'h' )
		return (1);
	return (0);
}

void	throw_error_in_exit(
		t_pipes *t, int *exit_code, int error_code, int parse_error)
{
	int	convert_erro;

	convert_erro = error_code;
	t->parse_error = parse_error;
	close_files(t->fd, t->npipes);
	if (parse_error == 4)
	{
		throw_parser_error(t, &convert_erro);
		return ;
	}
	clean_env(t->env);
	throw_parser_error(t, &convert_erro);
	*exit_code = 255;
	exit (*exit_code);
}

void	stick_error_code_if_it__exists(char *cmd, t_list *head, t_smash_kit *s)
{
	search_for_unclosed_quote(cmd, s);
	if (head)
	{
		if (s->parse_error_code != 0)
			head->flag = s->parse_error_code;
	}
}
