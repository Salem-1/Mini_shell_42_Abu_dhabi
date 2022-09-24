/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/23 07:56:11 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
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

t_parsed_command	*parse_one_cmd(char *command);
t_list				*parse_env(char **envp, t_list *head);
void				execute_one_cmd(char *command, t_list *t_env);
void				free_cmd(t_parsed_command *t);
void				just_execve(t_parsed_command	*t, t_list *t_env);
char				**get_path(t_list *env);
size_t				length_of_larger_string(char *str1, char *str2);
char				*search_list(t_list *env, char *needle);
char				*search_path_for_bin(char *split_command_0,t_list *env);
char				**join_env(t_list *t_env);
int					cmd_not_empty(char *cmd);

//testing functions, delete before submission
void				vis_split(char **arr);
void				vis_list(t_list **env);
void				visualize_cmd(t_parsed_command *t);
#endif