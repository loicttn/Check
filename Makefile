#
# C Testing Librairy
# Made by Titren Loïc & Ardouin Théo
#
# compile the testing librairy
#

SHELL	=	/bin/sh

NAME	=	libCheck.a

CC		?=	gcc

RM		?= 	rm -f

SRC 	= 	src/main.c						\
			src/check_init.c				\
			src/find_test_ptr.c				\
			src/run/run_tests.c				\
			src/run/timeout.c				\
			src/run/check_test_success.c	\
			src/assert/asserts.c

CFLAGS	=	-iquote./include/ -Wall -Wextra -Werror=implicit-function-declaration -O2

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
