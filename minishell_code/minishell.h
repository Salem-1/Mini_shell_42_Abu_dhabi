/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 06:35:58 by ahsalem           #+#    #+#             */
/*   Updated: 2022/10/31 06:25:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include "libft/err_printf/ft_printf.h"
# include "./libft/forensic_printf/forens_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/*
	Parse error codes:
	1  parsing error
	2  syntax error
*/
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
	int					**fd;
	int					last_exit_code;
	int					parse_error;
	t_list				*env;
}	t_pipes;

typedef struct smashing_kit
{
	t_list	*tmp;
	t_list	*env;
	int		exit_status;
	int		i;
	int		start;
	int		end;
	char	flag;
	int		parse_error_code;
}	t_smash_kit;

typedef struct dollar_expansion_kit
{
	char	*smashed_arg;
	char	*new_arg;
	char	*var_key;
	char	*var_val;
	char	*tmp;
	int		start;
	int		end;
}	t_dollar_expansion_kit;

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
t_pipes				*parsing_piped_cmd(
						char *cmd, t_list *env, int *exit_status);

char				**ft_cmd_split(char *raw_cmd);
t_list				*cmd_smasher(char *cmd, t_list **head, t_list *env, int *exit_status);
t_list				*fill_cmd_node(char *arg, char type);
void				spaces_smash(t_smash_kit *s, char *cmd,
						t_list **head, int *exit_status);
char				cmd_classifier(t_smash_kit *s, char *cmd);
void				init_smash_kit(t_smash_kit *s, t_list **head, t_list *env);
void				double_qoute_smash(t_smash_kit *s, char *cmd,
						t_list **head, int *exit_status);
void				single_qoute_smach(t_smash_kit *s, char *cmd,
						t_list *tmp, t_list **head);
int					fill_redirection(t_smash_kit *s, char *cmd,
						t_list **head, int i);
int					check_redirection(char *cmd, int i);
void				fill_append(t_smash_kit *s, char *cmd, int i);
void				fill_in_out_app_hered(t_smash_kit *s,
						char *cmd, t_list **head, int i);
int					count_cmds(t_list *cmd);
t_pipes				*init_t_struct(t_pipes *t,int n_cmds, t_list *smashed_cmd, t_list *env);
t_list				*fill_cmd(t_list *smashed_cmd, t_pipes *t, int i);
int					count_args_in_cmd(t_list *smashed_cmd);
char				decide_rel_or_abs_path(char *cmd);
void				visualized_piped_cmd(t_pipes *t);
int					count_outliar_redire(t_list *tmp, int i);
void				fill_outliar_redirected_cmd(
						t_list *smashed_cmd, t_pipes *t, int *i, int *local_i);
void				fill_redirec_outliar_cmd_hard_coded(
						t_pipes *t, int *i, t_list *smashed_cmd);
void				fill_outliar_input(
						t_list *smashed_cmd, t_pipes *t, int *i, int *local_i);
void				decide_rel_abs_fill_cmd_null_arg(
						t_list *smashed_cmd, t_pipes *t, int i, int local_i);
int					add_content_to_single_cmd_arg(t_parsed_command *single_cmd,
						int *local_i, t_list *smashed_cmd);
int					init_fill_cmd(int *local_i, int *i, t_pipes *t,
						t_list *smashed_cmd);
char				*expand_var(t_smash_kit *s, char *cmd, int *exit_status);
int					get_end_of_var(char *var);
char				*search_expanded_var(t_list *t_env,
						char *env_variable, int *exit_status);
int					dollar_expan_operation_loop(t_dollar_expansion_kit *e,
						t_smash_kit *s, int *exit_status);
char				*handle_outliar_remain_after_quote(
						t_smash_kit *s, char flag, char *cmd, int *exit_status);
int					scan_cmd_for_parsing_errors(
						t_list *smashed_cmd);
int					is_r_flag(char flag);
void				parsing_laundry(t_pipes *t);
void				case_take_f1_cat_f2_f3_etc(t_pipes *t);
//quotes handling
char				*figure_out_end_of_quote_and_fill_arg(t_smash_kit *s,
						char *cmd, char flag, int *exit_status);
char				*fill_normal_quote_case(t_smash_kit *s,
						char *cmd, char flag, int *exit_status);
char				*fill_outliar_quote_by_split_expand(
						t_smash_kit *s, char *cmd, char flag, int *exit_status);
char				*outliar_double_with_expand(t_smash_kit *s,
						char **splitted_arg, char *final_arg, int *exit_status);
char				*outliar_single_fill(
						char **splitted_arg, char *final_arg);
char				*multiple_single_and_double_quotes(t_smash_kit *s,
						char *cmd, char flag, int *exit_status);
//Execution
int					exec_to_output_operations(t_pipes *t, t_list *env,int **fd, int i);
int					exec_to_take_operations(t_pipes *t, t_list *env,int **fd, int i);
int					execute_in_pipe(t_pipes *t, t_list *env,int **fd, int i);
int					execute_one_cmd(char *command, t_list *t_env,
						int exit_shell);
char				*search_path_for_bin(char *split_command_0, t_list *env);
void				just_execve(t_parsed_command *t,
						t_list *t_env, struct t_pipes *all_cmds);
int					execution_operations(char *cmd, t_list *t_env,
						int *exit_status);
void				exec_with_pipe(char *cmd, t_list *env);
void				exec_to_out(int fd[2], t_pipes *t, t_list *env);
void				exec_to_in(int fd[2], t_pipes *t, t_list *env);
void				close_files(int **fd, int npipes);
int					**open_pipes(int n, int **fd);
void				exec_multiple_pipes(
						char *cmd, t_list *env, int *exit_status);
void				close_files_and_wait(int **fd,
						struct t_pipes	*t, int *exit_status);
void				piping_and_redirections(
						int i, int **fd, struct t_pipes *t, t_list *env);
void				case_input_file_cat(
						t_list *smashed_cmd, t_pipes *t, int *i, int *local_i);
void				case_input_file_cat_otherfiles(
						t_list *smashed_cmd, t_pipes *t, int *i, int *local_i);
void				malloc_single_cmd_in_t_piped_cmd(t_pipes *t, int i);
void				exec_exit_export_unset_cd_in_parent(
						int *i, struct t_pipes *t, t_list *env, int *exit_status);
char				*ft_low(char *cmd);
//heredoc
void				if_there_is_heredoc_fill_it(t_pipes *t, t_list *env);
void				fill_heredoced_cmd(t_pipes *t, t_list *env, int i);
void				lets_heredoc(t_pipes *t, t_list *env, int i);
int					skip_multiple_heredocs(t_pipes *t, int i);
char				*expand_heredoc_var(
						t_smash_kit *s, char *cmd, int * exit_status);
char				*expand_heredoc_var(
						t_smash_kit *s, char *cmd, int * exit_status);
void				init_s_for_heredoc(
						t_smash_kit *s, char *filled_heredoc, t_list *env);
//Executables
int					is_in_our_executable(struct t_parsed_command *t
						, t_list *env, struct t_pipes *all_cmds);
void				exec_our_cmd(t_parsed_command *t, t_list *env, struct t_pipes *all_cmds);
t_list				*fill_new_export_node(t_list *tmp,
						char **exp_item, int m_size);
char				**fill_export_with_key_val_variables(char *cmd,
						t_list *env, t_list *tmp, char **exp_item);
char				**fill_export_with_key_only(char **exp_item,
						int m_size, char *cmd);
t_list				*parsed_exp_arg(char *cmd, t_list **env, t_list *tmp,
						struct t_parsed_command *t);
int					is_repeated(char *cmd, t_list **env);

void				exec_env(t_list **env);
void				exec_pwd(void);
void				exec_export(t_pipes *all_cmds, struct t_parsed_command *t,
						t_list **env, int flag);
int					valid_export_arg(char *str, char flag);
int					find_msize(char *cmd);
void				raise_export_error(t_pipes *t, char *cmd, char flag);
int					exec_unset(struct t_parsed_command *t, t_list **env,
						int i, char flag);
t_list				*search_env(t_list *t_env, char *env_variable,
						char flag, int throw_error);
void				clear_var(t_list *delete_me, t_list **env, int throw_error);
void				unset_error(char *env_variable,
						int error_code, char throw, t_pipes *t);
int					exec_cd(struct t_parsed_command *t,
						t_list **env, t_pipes *all_cmds, int flag);
void				fill_old_and_current_pwd(t_list **env,
						char *old_path, char *current_path);
void				cd_error(t_pipes *t, char *error_path, char flag);
void				exec_local_export(char *local_var, t_list **env, char flag);
void				exec_echo(struct t_parsed_command *t);
void				exec_exit(struct t_pipes *all_cmds, int exit_shell);
int					tedous_n(struct t_parsed_command *t);
void				vis_list(t_list **env, char is_env_or_exp);
int					output_append_execution(t_pipes *t, int i, int **fd);
int					input_execution(t_pipes *t, t_list *env,int **fd, int i);
char				*clean_export_var_from_quotes(char *val, char quote);
int					exec_exit_in_parent(int *i,  struct t_pipes *t);
int					check_exit_arg(t_parsed_command *t);
void				throw_error_in_exit(t_pipes *t, int *exit_code,
						int error_code,int parse_error);
int					exec_exit_in_child(t_parsed_command *single_cmd,
						t_pipes *t, int exit_code);
//Handling erros
void				throw_parser_error(t_pipes *t, int * exit_status);
void				fill_errored_pipe(
						t_pipes *t, int error, t_list *smashed_cmd);
void				cd_exit_with_code(t_pipes *t);
void				pipes_and_redirect_errors(
						t_pipes *t, int i, int local_fd, int **fd);
void				normal_execution_error(struct t_parsed_command *t,
						struct t_pipes *all_cmds, char **envp);
//signals handling
void					handle_signals(int sig);
void					init_signals();

//testing functions,
void				vis_split(char **arr);
void				visualize_cmd(t_parsed_command *t);
void				vis_smached_cmd(t_list **head);
//cleaning
void				flush_pipes(t_pipes	*t);
void				free_cmd(t_parsed_command *single_cmd);
void				free_fd(t_pipes *t);
/*
	Certified function through testing in real life scenarios
*/
void				freedom(char *cmd, t_list *env, t_list *smashed_cmd);
void				clean_env(t_list *env);

#endif