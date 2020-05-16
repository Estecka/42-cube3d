SRCS = fps.c
OBJS = ${SRCS:.c=.o}

NAME = libfps.a

CFLAGS = -O3 -Wall -Wextra


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

re: fclean all

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

.PHONY: all re clean fclean \
