/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_quote_cases.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:40:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/11/06 20:14:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fetch_end  figure out wher the arg ends;
char *fill_case_2(t_smash_kit *s,
                            char *cmd, char flag, int *exit_status)
{
    int     fetch_end;
    char    *final_arg;
    char    **splitted_arg;
    int     quote_end;

    splitted_arg = NULL;
    final_arg = NULL;
    fetch_end = 1;
    quote_end = 0;
    while (not_reched_end(cmd, s, fetch_end, &quote_end))
        fetch_end++;
    s->end = s->i + fetch_end;
    s->i += fetch_end - 1;
    final_arg = ft_substr(cmd, s->start, s->end - s->start);
    splitted_arg = ft_split(final_arg, flag);
    if (flag == '"')
        final_arg = fill_double_q(s, splitted_arg, final_arg, exit_status);
    else
        final_arg = outliar_single_fill(splitted_arg, final_arg);
    return (final_arg);
}

int not_reched_end(char *cmd, t_smash_kit *s, int fetch_end, int *quote_end)
{
    if (cmd[s->i] == s->flag && *quote_end == 0)
        *quote_end = 1;
    else if (cmd[s->i] == s->flag && *quote_end == 1)
        *quote_end = 2;
    if (cmd[s->i + fetch_end] != '\0'
            && !check_redirection(cmd, s->i + fetch_end)
            && (cmd[s->i + fetch_end] != '\'')
            && (cmd[s->i + fetch_end] != '"')
        )
     return (1);
    else
        return (0);
}

// int is_quote_ended(char *cmd, t_smash_kit *s)
// {
    

// }
/*
    forens_printf("Case 2 FIll outliar quote, flag = %c\n", flag);
    forens_printf("cmd before expand = %s, start = %d, end = %d, i = %d\n", cmd, s->start, s->end, s->i);

    // while (cmd[s->i + fetch_end] != '\0' && !check_redirection(cmd, s->i + fetch_end)
    // 	&& (cmd[s->i + fetch_end] != ' ') && (cmd[s->i + fetch_end] != '\'')
    // 	&& (cmd[s->i + fetch_end] != '"'))
forens_printf("cmd[%d + %d] = %c\n", s->i, fetch_end, cmd[s->i + fetch_end]);

    forens_printf("final_arg after substr outliar case  = %s, start = %d, end = %d\n", final_arg, s->start, s->end);

    forens_printf("End fill outliar case  = %s, start = %d, end = %d\n", final_arg, s->start, s->end);
*/