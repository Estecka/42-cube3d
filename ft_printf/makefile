SRCS = bufferutil.c ft_printf.c libft/character.c libft/character2.c libft/integer.c libft/integer2.c libft/list.c libft/list2.c libft/memory.c libft/memory2.c libft/put_things.c libft/put_things_fd.c libft/string.c libft/string2.c libft/string3.c tag_parser.c w_character.c w_intbase.c w_integer.c w_pointer.c w_string.c

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

CC   = gcc
CFLAGS = -Wall -Wextra -Werror


printf: ${NAME}
${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re printf
