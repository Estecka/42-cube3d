SRCS = mlx_img.c\

OBJS = ${SRCS:.c=.o}

NAME	= libmlxpp.a

CC		= gcc
CFLAGS	= -O3 -Wall -Wextra -Werror



${NAME}: ${OBJS} 
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
