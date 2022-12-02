/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_quote_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:39:12 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/02 12:22:05 by ahsalem          ###   ########.fr       */
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
	if (is_not_end_quote_case_3(cmd, s, fetch_end))
	{
		forens_printf("fetching end cmd[%d + %d] = <%c>, flag = %c\n",
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
		&& !(s->start == 0 && cmd[s->i + fetch_end] == ' '))
		return (1);
	else
		return (0);
}
