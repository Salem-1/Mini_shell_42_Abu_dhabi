/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirect_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 03:09:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/01 14:49:31 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_redirec_errors(t_pipes *t, int i, int local_fd, int **fd)
{
	close(local_fd);
	close_files(fd, t->npipes);
	err_printf("minishell: %s: No such file or directory\n",
		t->single_cmd[i]->cmd);
	exit(1);
}

void	intake_errors(t_pipes *t, int i, int local_fd, int **fd)
{
	close(local_fd);
	close_files(fd, t->npipes);
	err_printf("minishell: %s: No such file or directory\n",
		t->single_cmd[i]->cmd);
	clean_env(t->env);
	flush_pipes(t);
	exit(1);
}

void	fill_errored_pipe(t_pipes *t, int error, t_list *smashed_cmd)
{
	t->npipes = 1;
	t->parse_error = error;
	t->single_cmd = NULL;
	ft_lstclear(&smashed_cmd, del);
	smashed_cmd = NULL;
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
	else if ((is_r_flag(e->current_flag) && !e->next_flag)
		|| ((is_r_flag(e->current_flag)
				&& is_r_flag(e->next_flag)))
	)
		return (1);
	else
		return (0);
}

int	errord_t_piped(t_pipes *t, int *exit_status)
{
	if (!t)
	{
		throw_parser_error(t, exit_status);
		return (1);
	}
	if (t->parse_error != 0)
	{
		throw_parser_error(t, exit_status);
		return (1);
	}
	return (0);
}
