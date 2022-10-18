/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:40:50 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/18 21:31:20 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	remember to do this case
	<< delimeter cmd
	<< trash_delimter_and_heredoc cmd arg[1] arg[2]
	< input_file cmd
	< nonsense_input_sign cmd arg[1] arg[2] ...
*/

//no more heredocs in the execution
//remember to deduct the t->npipes -= heredocs;
void	if_there_is_heredoc_fill_it(t_pipes *t, t_list *env)
{
	int	i;
	int	count_heredocs;

	count_heredocs = 0;
	i = 0;
	while (i < t->npipes)
	{
		if (t->single_cmd[i]->before_sep == 'h')
		{
forens_printf("we have heredoc with deli = %s , let's fill it\n", t->single_cmd[i]->cmd);
			fill_heredoced_cmd(t, env, i);
		}
		i++;
	}
	forens_printf("Number of heredocs = %d\n", count_heredocs);
}



void	fill_heredoced_cmd(t_pipes *t, t_list *env, int i)
{
forens_printf("fill heredoc_cmd deli = %s , let's fill it\n", t->single_cmd[i]->cmd);
	// 	if (t->single_cmd[i]->before_sep == 'h')
	lets_heredoc(t, env, i);
	//expand after filling then add to the argv
}

void	lets_heredoc(t_pipes *t, t_list *env, int i)
{
	char	*line;
	char	*delim;
	char	*filled_heredoc;
	size_t	len;

(void)env;
	filled_heredoc = NULL;
	len = 0;
	delim = t->single_cmd[i]->args[0];
	line = readline("heredoc> ");
	len = length_of_larger_string(line, delim);
	while (ft_strncmp(line, delim, len) != 0)
	{
		filled_heredoc = ft_expand_strjoin(filled_heredoc, line);
		filled_heredoc = ft_expand_strjoin(filled_heredoc, ft_strdup("\n"));
		line = readline("heredoc> ");
		len = length_of_larger_string(line, delim);
	}
	free(line);
	//expand
	free(delim);
	t->single_cmd[i]->args[0] = filled_heredoc;
	forens_printf("heredoc filled with:\n%s\n", t->single_cmd[i]->args[0]);
	//do it's own execution algo
	//hekaito hekaya
}

//case : cat << 1 << 2 << 3
//i--; to make the cat command executed
int	skip_multiple_heredocs(t_pipes *t, int i)
{
	int	original_i;
	original_i = i;
// forens_printf("skipping multiple heredocs\n");
// forens_printf("at begining t->single_cmd[i] = %s i = %d, original_i = %d\n",t->single_cmd[i]->cmd, i, original_i);
	while (t->single_cmd[i]->after_sep == 'h')
		i++;
	i--;
	if (i != original_i)
	{
		// return (i);
		free(t->single_cmd[i]);
		t->single_cmd[i] = t->single_cmd[original_i];
	}
// forens_printf("at the end t->single_cmd[i] = %s i = %d, original_i = %d\n",t->single_cmd[i]->cmd, i, original_i);
	return (i);
}
// void	refractor_heredoced_cmd(t_pipes *t, t_list *env)
// {
// 	//expand environment vars
// }


//this is how the execution will look like in multiple pipes
// void	lets_heredoc(int **fd, int *i, struct t_pipes *t)
// {
// 	char	*line;
// 	char	*delim;
// 	size_t	len;

// 	len = 0;
// 	if (!t->single_cmd[*i + 1] || t->single_cmd[*i + 1]->cmd == NULL)
// 		printf("throw heredoc error and exit\n");
// 	delim = t->single_cmd[*i + 1]->cmd;

// 	line = readline("heredoc> ");
// 	len = length_of_larger_string(line, delim);
// 	while (ft_strncmp(line, delim, len) != 0)
// 	{
// 		write(fd[*i][1], line, ft_strlen(line));
// 		write(fd[*i][1], "\n", 1);
// 		free(line);
// 		line = readline("heredoc> ");
// 		len = length_of_larger_string(line, delim);
// 	}
// 	free(line);

// 	//do it's own execution algo
// 	//hekaito hekaya
// }