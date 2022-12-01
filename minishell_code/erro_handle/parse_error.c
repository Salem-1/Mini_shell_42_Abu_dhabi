/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 09:40:05 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//remeber to throw erro for error
void	throw_parser_error(t_pipes *t, int *exit_status)
{
	if (!t)
	{
		throw_error_exit_code(
			"minishell: parser error \n", exit_status, 258);
		return ;
	}
	if (t->parse_error == 2)
		throw_error_exit_code(
			"minishell: syntax error near unexpected token\n", exit_status, 258);
	else if (t->parse_error == 1)
		throw_error_exit_code(
			"minishell: parser error \n", exit_status, 258);
	else if (t->parse_error == 3)
		throw_error_exit_code(
			"minishell: exit: numeric argument required \n", exit_status, 258);
	else if (t->parse_error == 4)
		throw_error_exit_code(
			"minishell: exit: too many arguments\n", exit_status, 1);
	else if (t->parse_error == 5)
		throw_error_exit_code(
			"exit: fd: numeric argument required\n", exit_status, 255);
	flush_pipes(t);
}

void	throw_error_exit_code(
			char *message, int *exit_status, int exit_code)
{
	err_printf("%s", message);
	*exit_status = exit_code;
}

int	scan_cmd_for_parsing_errors(t_list *smashed_cmd)
{
	t_scan_parse_error	e;

	init_e_args(&e, smashed_cmd);
	while (e.tmp)
	{
		update_e_args(&e);
		if (is_parse_error_inside_smached_cmd(&e))
		{
			smashed_cmd->flag = 2;
			return (2);
		}
		e.tmp = e.tmp->next;
	}
	return (0);
}

void	update_e_args(t_scan_parse_error *e)
{
	e->current_flag = e->tmp->flag;
	if (e->tmp->next)
	{	
		e->next_flag = e->tmp->next->flag;
		if (e->tmp->next->next)
			e->next_next_flag = e->tmp->next->next->flag;
		else
			e->next_next_flag = '\0';
	}
	else
		e->next_flag = '\0';
	e->i++;
}
