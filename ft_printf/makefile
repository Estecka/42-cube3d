SRCS = ft_printf.c \
	bufferutil.c \
	tag_parser.c \
	w_character.c \
	w_intbase.c \
	w_integer.c \
	w_pointer.c \
	w_string.c\

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

LIBFTDIR = ../libft/

CC   = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -I${LIBFTDIR}


printf: ${NAME}
${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}
	rm -rf *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re printf
