NAME = minishell
SRC =	main.c \
		executing/execute_one_command.c executing/redirections_exec.c executing/exec_init.c   executing/our_exec_operations.c\
		executing/exec_in_pipe.c executing/exec_give_append.c executing/exec_intake_heredoc.c \
		parsing/parsing_one_command.c parsing/parsing_utils_1.c \
		executing/multiple_pipes.c\
		executing/heredoc.c\
		executing/files_handling.c\
		executing/signals_handling.c\
		parsing/clean_mem.c  parsing/parse_env.c \
		parsing/parsing_piped_cmd.c parsing/parsing_piped_utils.c\
		parsing/outliar_redirect_parse.c\
		parsing/cmd_laundary.c\
		pro_parsing/cmd_smasher.c pro_parsing/classify_cmd.c \
		pro_parsing/smash_redirections.c\
		pro_parsing/expand_dollar.c\
		pro_parsing/outliar_quotes.c\
		pro_parsing/complicated_quote_cases.c \
		bins/cd.c bins/echo.c bins/env_pwd.c \
		bins/exit.c bins/export.c  bins/unset.c \
		bins/export_utils.c \
		erro_handle/raise_builtin_errors.c \
		erro_handle/parse_error.c \
		erro_handle/pipes_redirect_errors.c \
		test_files/vis.c 
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3 
#-fsanitize=address -static-libasan 

CC = gcc 
OBJ = $(SRC:.c=.o)
LIBS =  ./libft/err_printf/err_printf.a ./libft/forensic_printf/forens_printf.a ./libft/libft.a

# LIBS = ./libft/libft.a ./libft/err_printf/err_printf.a 

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	make -C libft/err_printf/.
	make -C libft/forensic_printf/.
	$(CC)  $(CFLAGS)  $(OBJ) -L/usr/local/opt/readline/lib -lreadline $(LIBS) -o $(NAME)
	clear


clean:
	@make clean -C libft/.
	@make clean -C libft/err_printf/.
	@make clean -C ./libft/forensic_printf/.
	@rm -f parsing/*.o
	@rm -f executing/*.o
	@rm -f test_files/*.o
	@rm -f bins/*.o
	@rm -f erro_handle/*.o
	@rm -f pro_parsing/*.o
	@rm -f *.o
	


fclean: clean 
	@make fclean -C libft/.
	@make fclean -C libft/err_printf/.
	@make fclean -C ./libft/forensic_printf/.
	@rm -f $(NAME) 
	
re: fclean all

