NAME = minishell
SRC = main.c executing/execute_one_command.c parsing/parsing_one_command.c parsing/parsing_utils_1.c \
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
	@rm -f *.o
	@rm -f parsing/*.o
	@rm -f executing/*.o
	@make clean -C libft/.
	


fclean: clean 
	@rm -f $(NAME) 
	@rm -f libft/libft.a
	
re: fclean all
