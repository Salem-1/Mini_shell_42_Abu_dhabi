/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/21 13:11:40 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>

typedef struct t_parsed_command
{
	char	*cmd;
	char	**args;
	char	**env;
	char	**splitted_cmd;
	char	path;
}	t_parsed_command;

t_parsed_command	*parse_one_cmd(char *command, char **envp);
void				execute_one_cmd(char *command, char **envp);
void				free_cmd(struct t_parsed_command *t);
void				visualize_cmd(struct t_parsed_command *t);
void				just_execve(struct t_parsed_command	*t, char **envp);
char				**get_path(char **envp);
void				free_split(char **splited);
size_t				length_of_larger_string(char *str1, char *str2);
char				*search_split(char **splitted_haystack, char *needle);



//testing functions, delete before submission
void	vis_split(char **arr);
#endif