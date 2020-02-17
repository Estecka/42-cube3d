SRCS	= main.c renderer.c
OBJS	= ${SRCS:.c=.o} ${MISC_OBJS} ${CUB_OBJS}

MISC_SRCS = throw.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	mallocspy/mallocspy.c mallocspy/mallocspy_internals.c
MISC_OBJS = ${MISC_SRCS:.c=.o}

NAME	= cube3d.out
CUB		= cub/libcub.a
MATH	= ft_math/libftmath.a
DYNARRAY = dynarray/libdynarray.a
LIBFT	= libft/libft.a
PRINTF	= ft_printf/libftprintf.a
MINILIBX = libmlx.dylib


CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = \
	-L cub -lcub \
	-L ft_math -lftmath \
	-L dynarray -ldynarray \
	-L libft -lft \
	-L ft_printf -lftprintf \
	-L ./ -lmlx \



${NAME}: ${OBJS} ${CUB} ${LIBFT} ${PRINTF} ${MINILIBX} ${MATH}
	gcc ${OBJS} -o ${NAME} \
	${LIBFLAGS} \
	${CFLAGS} \

libft: ${LIBFT}
${LIBFT}: 
	make -C libft

printf: ${PRINTF}
${PRINTF}:
	make -C ft_printf

minilibx: ${MINILIBX}
${MINILIBX}: minilibx/${MINILIBX}
	cp minilibx/${MINILIBX} ./
minilibx/${MINILIBX}:
	make -C minilibx

all: ${NAME} ${CUB}

cub: ${CUB}
${CUB}:
	make -C cub/

math: ${MATH}
${MATH}:
	make -C ft_math
dynarray: ${DYNARRAY}
${DYNARRAY}:
	make -C dynarray



clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libft \
	libft printf minilibx cub math dynarray
