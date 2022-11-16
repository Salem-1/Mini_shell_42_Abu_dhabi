/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/07 09:26:02 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//remeber to throw erro for error
void	throw_parser_error(t_pipes *t, int *exit_status)
{
	if (!t)
	{
		err_printf("minishell: parser error \n");
		*exit_status = 258;
		return ;
	}
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
	flush_pipes(t);
}

void	cd_exit_with_code(t_pipes *t)
{
	if (t->parse_error == 10)
	{
		//clean
		exit (1);
	}
	else
	{
		//clean
		exit(0);
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

int	scan_cmd_for_parsing_errors(t_list *smashed_cmd)
{
	t_scan_parse_error e;

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

void	init_e_args(t_scan_parse_error *e, t_list *smashed_cmd)
{
	e->i = -1;
	e->current_flag = '\0';
	e->next_flag = '\0';
	e->next_next_flag = '\0';
	e->tmp = smashed_cmd;
}

/*
	echo hi >| f  ==  echo hi > f
	cat <> file == cat < file
*/
int	is_parse_error_inside_smached_cmd(t_scan_parse_error *e)
{
	if (e->i != 0 && ((e->current_flag == 'g' && e->next_flag == 'p'
				&& e->next_next_flag == 'c')
			|| (e->current_flag == 't' && e->next_flag == 'g'
				&& e->next_next_flag == 'c')))
	{
		remove_second_redirection(e);
		return (0);
	}
	else if((is_r_flag(e->current_flag) && !e->next_flag) 
		|| ((is_r_flag(e->current_flag)
				&& is_r_flag(e->next_flag)))
	)
	{
		return (1);
	}
	else
	{
		return (0); 
	}
}

void	remove_second_redirection(t_scan_parse_error *e)
{
	t_list *delete_me;

	delete_me = e->tmp->next;
	e->tmp->next = e->tmp->next->next;
	ft_lstdelone(delete_me, del);
}
/*
	//update the conditions here
	//if the first second || last and prelast or 3 consective redire
	//or || consective pipes

int	is_parse_error_inside_smached_cmd(t_scan_parse_error *e)
{	
	if ((is_r_flag(e->current_flag) && !e->next_flag) 
		|| ((e->i == 0 
				&& is_r_flag(e->current_flag) && is_r_flag(e->next_flag)))
		|| (is_r_flag(e->current_flag) && is_r_flag(e->next_flag)
				&& is_r_flag(e->next_next_flag))
		|| (is_r_flag(e->current_flag) && is_r_flag(e->next_flag) 
				&& e->next_next_flag == '\0')
		)
		return (1);
	else
		return (0); 
}
*/
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
