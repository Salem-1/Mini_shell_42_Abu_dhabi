/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/25 04:06:28 by ahsalem          ###   ########.fr       */
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
// # include <editline.h>

typedef struct t_parsed_command
{
	char	*cmd;
	char	**args;
	char	**env;
	char	**splitted_cmd;
	char	path;
	int		index;
}	t_parsed_command;

typedef struct t_pipes
{
	t_parsed_command	**single_cmd;
	int					npipes;
}	t_pipes;

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
int					is_piped(char *cmd);
void				execution_operations(char *cmd, t_list *t_env);
void				exec_with_pipe(char *cmd, t_list *env);
t_pipes				*parsing_piped_cmd(char *cmd);
void				flush_pipes(t_pipes	*t);
void				exec_to_out(int fd[2], t_pipes *t, t_list *env);
void				exec_to_in(int fd[2], t_pipes *t, t_list *env);
void				close_files(int **fd, int npipes);
int					**open_pipes(int n, int **fd);
void				exec_multiple_pipes(char *cmd, t_list *env);
//testing functions, delete before submission
void				vis_split(char **arr);
void				vis_list(t_list **env);
void				visualize_cmd(t_parsed_command *t);
#endif