NAME	=	libftprintf.a
SRC	=	err_printf/ft_printf.c err_printf/param_checker.c  err_printf/polymorophic_itoa.c err_printf/unsigned.c err_printf/signed.c err_printf/itoh.c \
		 err_printf/itop.c
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

