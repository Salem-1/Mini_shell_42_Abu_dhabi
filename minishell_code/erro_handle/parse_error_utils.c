/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:05:21 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/19 19:26:02 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
