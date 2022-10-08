/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/08 18:32:11 by ahsalem          ###   ########.fr       */
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
# include <signal.h>

typedef struct t_parsed_command
{
	char	before_sep;
	char	*cmd;
	char	**args;
	char	**env;
	char	**splitted_cmd;
	char	after_sep;
	char	path;
	int		index;
}	t_parsed_command;

typedef struct t_pipes
{
	t_parsed_command	**single_cmd;
	int					npipes;
}	t_pipes;

typedef struct smashing_kit
{
	t_list	*tmp;
	int		i;
	int		start;
	int		end;
	char	flag;
}	t_smash_kit;

//Parsing
t_parsed_command	*init_one_cmd(t_parsed_command *one_cmd);
t_parsed_command	*parse_one_cmd(char *command);
t_list				*parse_env(char **envp, t_list *head);
char				**get_path(t_list *env);
size_t				length_of_larger_string(char *str1, char *str2);
char				*search_list(t_list *t_env, char *needle, char flag);
char				**join_env(t_list *t_env);
int					cmd_not_empty(char *cmd);
int					is_piped(char *cmd);
t_pipes				*parsing_piped_cmd(char *cmd);
void				flush_pipes(t_pipes	*t);
char				**ft_cmd_split(char *raw_cmd);
t_list				*cmd_smasher(char *cmd, t_list **head);
t_list				*fill_cmd_node(char *arg, char type);
void				spaces_smash(t_smash_kit *s, char *cmd, t_list *tmp,
						t_list **head);
char				cmd_classifier(t_smash_kit *s, char *cmd);
t_smash_kit			*init_smash_kit(t_smash_kit *s, t_list **head);
void				double_qoute_smash(t_smash_kit *s, char *cmd,
						t_list *tmp, t_list **head);
void				single_qoute_smach(t_smash_kit *s, char *cmd,
						t_list *tmp, t_list **head);
int					fill_redirection(t_smash_kit *s, char *cmd,
						t_list **head, int i);
int					check_redirection(char *cmd, int i);
void				fill_append(t_smash_kit *s, char *cmd, int i);
void				fill_in_out_app_hered(t_smash_kit *s,
						char *cmd, t_list **head, int i);
int					count_cmds(t_list *cmd);
t_pipes				*init_t_struct(t_pipes *t,int n_cmds);
t_list				*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i);
int					count_args_in_cmd(t_list *smashed_cmd);
char				decide_rel_or_abs_path(char *cmd);
void				visualized_piped_cmd(t_pipes *t);
int					count_outliar_redire(t_list *tmp);
void				fill_outliar_redirected_cmd(
						t_list *smashed_cmd, t_pipes *t, int *i, int *local_i);
void				fill_redirec_outliar_cmd_hard_coded(
						t_pipes *t, int *i, t_list *smashed_cmd);
//Execution
int					execute_one_cmd(char *command, t_list *t_env,
						int exit_shell);
void				free_cmd(t_parsed_command *t);
char				*search_path_for_bin(char *split_command_0,t_list *env);
void				just_execve(t_parsed_command	*t, t_list *t_env);
int					execution_operations(char *cmd, t_list *t_env,
						int exit_shell);
void				exec_with_pipe(char *cmd, t_list *env);
void				exec_to_out(int fd[2], t_pipes *t, t_list *env);
void				exec_to_in(int fd[2], t_pipes *t, t_list *env);
void				close_files(int **fd, int npipes);
int					**open_pipes(int n, int **fd);
void				exec_multiple_pipes(char *cmd, t_list *env);
void				close_files_and_wait(int **fd, struct t_pipes	*t);
void				piping_and_redirections(int *i,
						int **fd, struct t_pipes *t, t_list *env);
//Executables
int					is_in_our_executable(struct t_parsed_command *t
						, t_list *env);
void				exec_our_cmd(t_parsed_command *t, t_list *env);
t_list				*fill_new_export_node(t_list *tmp,
						char **exp_item, int m_size);
char				**fill_export_with_key_val_variables(char *cmd,
						t_list *env, t_list *tmp, char **exp_item);
char				**fill_export_with_key_only(char **exp_item,
						int m_size, char *cmd);
t_list				*parsed_exp_arg(char *cmd, t_list **env, t_list *tmp,
						struct t_parsed_command *t);
int					is_repeated(char *cmd, t_list **env);
void				exec_our_cmd(struct t_parsed_command *t, t_list *env);
void				exec_env(t_list **env);
void				exec_pwd();
void				exec_export(struct t_parsed_command *t, t_list **env);
int					valid_export_arg(char *str);
int					find_msize(char *cmd);
void				raise_export_error(char *cmd);
void				exec_unset(struct t_parsed_command *t, t_list **env, int i);
t_list				*search_env(t_list *t_env, char *env_variable, char flag);
void				clear_var(t_list *delete_me, t_list **env);
void				unset_error(char *env_variable);
void				exec_cd(struct t_parsed_command *t, t_list **env);
void				cd_error(char *error_path, char flag);
void				exec_local_export(char *local_var, t_list **env, char flag);
void				exec_echo(struct t_parsed_command *t);
void				exec_exit(struct t_parsed_command *t, int exit_shell);
int					tedous_n(struct t_parsed_command *t);
void				vis_list(t_list **env, char is_env_or_exp);
//signals handling
void					handle_signals(int sig);

//testing functions,
void				vis_split(char **arr);
void				visualize_cmd(t_parsed_command *t);
void				vis_smached_cmd(t_list **head);
#endif