SRCS = cubfile.c cubfield.c cubfields.c cubgrid.c
OBJS = ${SRCS:.c=.o}

TEST_SRCS = .test/main.c \
	../throw.c \

NAME	= libcub.a
TEST	= test.out
LIBFT	= ../libft/libft.a
PRINTF	= ../ft_printf/libftprintf.a
DYNARRAY= ../dynarray/libdynarray.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L ./ -lcub \
	-L ../dynarray -ldynarray \
	-L ../ft_printf -lftprintf \
	-L ../libft -lft \



${NAME}: ${OBJS} 
	ar rcs ${NAME} ${OBJS}

${LIBFT}: 
	make -C ../libft
${PRINTF}:
	make -C ../ft_printf
${DYNARRAY}:
	make -C ../dynarray

all: ${NAME} ${TEST}

test: ${TEST}
${TEST}: ${NAME} ${PRINTF} ${LIBFT} ${DYNARRAY} ${TEST_SRCS}
	gcc -o ${TEST} ${TEST_SRCS} \
		${LIBFLAGS} \
		${CFLAGS} \



clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}
	rm -f ${TEST}

re: fclean all

.PHONY: all clean fclean re test
