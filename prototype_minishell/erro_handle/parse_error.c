/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/16 20:54:46 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	throw_parser_error(t_pipes *t,int * exit_status)
{
	if (t->parse_error == 1)
	{
		err_printf("minishell: syntax error near unexpected token `newline'\n");
		*exit_status = 258;
		forens_printf("Exit with exit code %d\n", *exit_status);
	}
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