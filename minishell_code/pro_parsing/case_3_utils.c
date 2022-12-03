/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_3_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:39:12 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 20:07:45 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	I hard coded a lot of staff here to fix those 3 cases
	ech""o hi
	e"cho" hi
	echo"" hi
*/
int	not_reched_end_3(char *cmd, t_smash_kit *s, int fetch_end)
{
	forens_printf("fetching end cmd[%d + %d] = <%c>, flag = %c\n",
		s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
	if (is_not_end_quote_case_3(cmd, s, fetch_end))
	{
		forens_printf("not end cmd[%d + %d] = <%c>, flag = %c\n",
			s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
		return (1);
	}
	else
	{
		if (fixing_start_quote_case_3_edge_case(cmd, s, fetch_end))
			return (1);
		else
		{
			forens_printf("\nreached end cmd[%d + %d] = <%c>, flag = %c",
				s->i, fetch_end, cmd[s->i + fetch_end], s->flag);
			forens_printf(" start = %d\n\n", s-> start);
			return (0);
		}
	}
}

int	fixing_start_quote_case_3_edge_case(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	forens_printf("fixing start qutoe 3\n");
	if ((middle_case_check(cmd, s, fetch_end)
			&& check_redirection(cmd, s->last_end))
		|| case_start_3_edge_conditions(cmd, s, fetch_end))
	{
		forens_printf("fix said 1 (not end)\n");
		return (1);
	}
	else
	{
		forens_printf("fix said 0 (end)\n");
		return (0);
	}
}

/*
	ls|gr""ep h
	now it's copy paste, work on it tommorow inshalla
*/
int	middle_case_check(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	int	tmp_check;

	forens_printf("inside middle_csase\n");
	tmp_check = s->i + fetch_end;
	if ((cmd[tmp_check + 1] != '\0')
		&& !check_redirection(cmd, tmp_check)
		&& (cmd[tmp_check + 1] != '\'')
		&& (cmd[tmp_check + 1] != '"' || (cmd[tmp_check + 1] == '"'
				&& cmd[tmp_check + 2] != ' '))
		&& ((cmd[tmp_check + 1] != ' ')
			&& ((cmd[tmp_check] != ' '))))
	{
		forens_printf("middle case returned (1)\n");
		return (1);
	}
	else
	{
		forens_printf("middle case returned (0)\n");
		return (0);
	}
}

int	case_start_3_edge_conditions(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	if ((s->start == 0)
		&& (cmd[s->i + fetch_end + 1] != '\0'
			&& !check_redirection(cmd, s->i + fetch_end)
			&& (cmd[s->i + fetch_end + 1] != '\'')
			&& (cmd[s->i + fetch_end + 1] != '"')
			&& ((cmd[s->i + fetch_end + 1] != ' ')
				&& ((cmd[s->i + fetch_end] != ' ')))))
		return (1);
	else
		return (0);
}

int	is_not_end_quote_case_3(
	char *cmd, t_smash_kit *s, int fetch_end)
{
	if (cmd[s->i + fetch_end] != '\0'
		&& !check_redirection(cmd, s->i + fetch_end)
		&& (cmd[s->i + fetch_end] != '\'')
		&& (cmd[s->i + fetch_end] != '"')
		&& !((s->start == 0 || check_redirection(cmd, s->last_end))
			&& cmd[s->i + fetch_end] == ' '))
		return (1);
	else
		return (0);
}
