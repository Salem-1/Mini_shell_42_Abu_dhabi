/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/21 09:28:07 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//remeber to throw erro for error
void	throw_parser_error(t_pipes *t, int *exit_status)
{
	if (t->parse_error == 2)
	{
		err_printf("minishell: syntax error near unexpected token \n");
		*exit_status = 258;
	}
	else if (t->parse_error == 1)
	{
		err_printf("minishell: parser error \n");
		*exit_status = 258;
	}
	else if (t->parse_error == 3)
	{
		err_printf("minishell: exit: numeric argument required \n");
		*exit_status = 258;
	}
	else if (t->parse_error == 4)
	{
		err_printf("minishell: exit: too many arguments\n");
		*exit_status = 1;
	}
	else if (t->parse_error == 5)
	{
		err_printf("exit: fd: numeric argument required\n");
		*exit_status = 255;
	}
forens_printf("Exit with exit code %d\n", *exit_status);
forens_printf("-------------------------------------------\n");
forens_printf("-------------------------------------------\n");
forens_printf("-------------------------------------------\n");
forens_printf("-------------------------------------------\n");
}

/*
	take car while flushing errod piped make it as simple as possible
*/
void	fill_errored_pipe(t_pipes *t, int error, t_list *smashed_cmd)
{
	t->npipes = 1;
	t->parse_error = error;
	t->single_cmd = NULL;
	ft_lstclear(&smashed_cmd, del);
	smashed_cmd = NULL;
}

int	scan_cmd_for_parsing_errors(t_list *smashed_cmd)
{
	t_list	*tmp;
	char	current_flag;
	char	next_flag;

	current_flag = '\0';
	next_flag = '\0';
	tmp = smashed_cmd;
	while (tmp)
	{
		current_flag = tmp->flag;
		if (tmp->next)
			next_flag = tmp->next->flag;
		else
			next_flag = '\0';
		if ((is_r_flag(current_flag) && !next_flag) || (next_flag && (
					is_r_flag(current_flag) && is_r_flag(next_flag))))
		{
			smashed_cmd->flag = 2;
forens_printf("Parsing error in repetitve or solo redirection\n");
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_r_flag(char flag)
{
	if (flag == 'p' || flag == 'g' || flag == 't'
		|| flag == 'a' || flag == 'h' )
		return (1);
	return (0);
}

void	throw_error_in_exit(
		t_pipes *t, int *exit_code, int error_code,int parse_error)
{
	int	convert_erro;

	convert_erro = error_code;
	t->parse_error = parse_error;
	throw_parser_error(t, &convert_erro);
	*exit_code = 255;
}
