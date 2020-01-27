SRCS	= mallocspy.c mallocspy_internals.c 
OBJS	= ${SRCS:.c=.o}

LIBFTDIR	= ../libft/
PRINTFDIR	= ../ft_printf/

NAME	= libmallocspy.a
TEST	= mallocspytest.out
LIBFT	= ${LIBFTDIR}libft.a
PRINTF	= ${PRINTFDIR}libftprintf.a


CC		= gcc
CFLAGS	= -Wall -Wextra #-Werror
LIBFLAGS = \
	-L ./ -lmallocspy \
	-L ${LIBFTDIR} -lft \
	-L ${PRINTFDIR} -lftprintf \


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

test: ${TEST}
${TEST}: ./.testmain.c ${NAME} ${LIBFT} ${PRINTF}
	gcc ./.testmain.c -o ${TEST} ${LIBFLAGS}


libft: ${LIBFT}
${LIBFT}: 
	make -C libft

printf: ${PRINTF}
${PRINTF}:
	make -C ft_printf

all: ${NAME} ${TEST}


clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}
	rm -f ${TEST}

re: fclean ${NAME}

.PHONY: all clean fclean re libft printf cub
