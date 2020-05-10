SRCS = cubfile.c cubfield.c cubfields.c cubgrid.c \
	cubworld.c pathfinder.c \

OBJS = ${SRCS:.c=.o}

TEST_SRCS = .test/main.c \
	../throw.c \
	../get_next_line/get_next_line.c \

NAME	= libcub.a
TEST	= test.out
LIBS = \
	../libft/libft.a \
	../ft_printf/libftprintf.a \
	../dynarray/libdynarray.a \
	../mallocspy/libmallocspy.a \

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L ./ -lcub \
	-L ../dynarray -ldynarray \
	-L ../ft_printf -lftprintf \
	-L ../libft -lft \
	-L ../mallocspy -lmallocspy \



${NAME}: ${OBJS} 
	ar rcs ${NAME} ${OBJS}

libs: ${LIBS}
${LIBS}:
	make -C ../libft
	make -C ../ft_printf
	make -C ../dynarray
	make -C ../mallocspy

all: ${NAME} ${TEST}

test: ${TEST}
${TEST}: ${NAME} ${LIBS} ${TEST_SRCS}
	clang -o ${TEST} ${TEST_SRCS} \
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
