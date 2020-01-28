SRCS	= main.c
OBJS	= ${SRCS:.c=.o} ${MISC_OBJS} ${CUB_OBJS}

MISC_SRCS = throw.c \
	stringbuilder/stringbuilder.c \
	mallocspy/mallocspy.c mallocspy/mallocspy_internals.c
MISC_OBJS = ${MISC_SRCS:.c=.o}

CUB_SRCS = cub.c cub1.c cub2.c
CUB_OBJS = ${CUB_SRCS:.c=.o}


NAME	= cube3d.out
CUB		= cub_parser.out
LIBFT	= libft/libft.a
PRINTF	= ft_printf/libftprintf.a
MINILIBX = libmlx.dylib


CC		= gcc
CFLAGS	= -Wall -Wextra #-Werror
LIBFLAGS = \
	-L libft -lft \
	-L ft_printf -lftprintf \
	-L ./ -lmlx \



${NAME}: ${OBJS} ${LIBFT} ${PRINTF} ${MINILIBX}
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
${CUB}: .test/main_cub.o  ${CUB_OBJS} ${MISC_OBJS} ${PRINTF} ${LIBFT}
	gcc .test/main_cub.o ${CUB_OBJS} ${MISC_OBJS} \
	-o ${CUB} \
	${LIBFLAGS} \
	${CFLAGS} \



clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	make clean -C minilibx
	rm -f ${LIBFT}
	rm -f ${PRINTF}
	rm -f ${MINILIBX}
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libft printf cub
