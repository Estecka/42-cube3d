SRCS	= \
	character.c character2.c \
	integer.c integer2.c \
	malloc.c \
	memory.c memory2.c \
	put_things.c \
	string.c string2.c string3.c \

SRCS_BONUS = list.c list2.c

OBJS	= ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME	= libft.a

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus: ${OBJS} ${OBJS_BONUS}
	ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

all: bonus

clean:
	rm -f ${OBJS}
	rm -f ${OBJS_BONUS}
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re bonus
