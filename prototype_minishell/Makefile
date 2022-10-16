NAME = minishell
SRC =	main.c \
		executing/execute_one_command.c executing/redirections_exec.c executing/exec_init.c   executing/our_exec_operations.c\
		parsing/parsing_one_command.c parsing/parsing_utils_1.c \
		executing/multiple_pipes.c\
		parsing/clean_mem.c  parsing/parse_env.c \
		parsing/parsing_piped_cmd.c parsing/parsing_piped_utils.c\
		parsing/outliar_redirect_parse.c\
		pro_parsing/cmd_smasher.c pro_parsing/classify_cmd.c \
		pro_parsing/smash_redirections.c\
		pro_parsing/expand_dollar.c\
		bins/cd.c bins/echo.c bins/env_pwd.c \
		bins/exit.c bins/export.c  bins/unset.c \
		bins/raise_builtin_errors.c \
		erro_handle/parse_error.c \
		test_files/vis.c 
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3
		

CC = gcc 
OBJ = $(SRC:.c=.o)
LIBS = ./libft/libft.a ./libft/err_printf/err_printf.a ./libft/forensic_printf/forens_printf.a

# LIBS = ./libft/libft.a ./libft/err_printf/err_printf.a 

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	make -C libft/err_printf/.
	make -C libft/forensic_printf/.
	$(CC)  $(CFLAGS)  $(OBJ) -L/usr/local/opt/readline/lib -lreadline $(LIBS) -o $(NAME)
	cp minishell ../sand_box_shell/.
	clear


clean:
	@make clean -C libft/.
	@make clean -C libft/err_printf/.
	@make clean -C ./libft/forensic_printf/.
	@rm -f parsing/*.o
	@rm -f executing/*.o
	@rm -f test_files/*.o
	@rm -f bins/*.o
	@rm -f pro_parsing/*.o
	@rm -f *.o
	


fclean: clean 
	@rm -f libft/libft.a
	@rm -f libft/libftprintf.a
	@rm -f libft/err_printf/err_printf.a
	@rm -f libft/forens_printf.a
	@rm -f $(NAME) 
	
re: fclean all
