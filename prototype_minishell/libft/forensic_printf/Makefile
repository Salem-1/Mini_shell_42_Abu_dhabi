NAME	=	forens_printf.a
SRC	=	ft_printf.c param_checker.c  polymorophic_itoa.c unsigned.c signed.c itoh.c ../ft_itoa.c \
		../ft_strlcpy.c ../ft_strlen.c ../ft_putstr.c ../ft_strdup.c itop.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc
OBJ	=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
	ar -rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean 
	@rm -f $(NAME) 

re: fclean all

