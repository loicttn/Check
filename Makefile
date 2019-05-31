#
# C Testing Librairy
# Made by Titren Loîc & Ardouin Th&o
#
# compile the testing librairy
#

SHELL	=	/bin/sh

NAME	=	lib_name.a

CC		?=	gcc

RM		?= 	rm -f

SRC 	= 	src/main.c

CFLAGS	=	-iquote./ -Wall -Wextra -Werror=implicit-function-declaration -O2
OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re
