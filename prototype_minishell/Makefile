NAME = minishell
SRC = main.c executing/execute_one_command.c executing/exec_init.c executing/execute_with_pipe.c \
	  parsing/parsing_one_command.c parsing/parsing_utils_1.c executing/multiple_pipes.c\
	  parsing/clean_mem.c  parsing/parse_env.c parsing/parsing_piped_cmd.c\
      test_files/vis.c 
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g3 \
		

CC = gcc 
OBJ = $(SRC:.c=.o)
LIBS = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	$(CC) -L/usr/local/opt/readline/lib -lreadline  $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)



clean:
	@make clean -C libft/.
	@rm -f parsing/*.o
	@rm -f executing/*.o
	@rm -f test_files/*.o
	@rm -f *.o
	


fclean: clean 
	@rm -f libft/libft.a
	@rm -f $(NAME) 
	
re: fclean all
