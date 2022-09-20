NAME = minishell
SRC = main.c executing/execute_one_command.c parsing/parsing_one_command.c

CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc
OBJ = $(SRC:.c=.o)
LIBS = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)



clean:
	@rm -f *.o
	@make clean -C libft/.
	


fclean: clean 
	@rm -f $(NAME) 
	@rm -f libft/libft.a
	
re: fclean all
