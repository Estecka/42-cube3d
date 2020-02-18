SRCS	= main.c \
	throw.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	worldbuilder/worldbuilder.c worldbuilder/transform.c \

OBJS	= ${SRCS:.c=.o}

NAME	= cube3d.out
MINILIBX = libmlx.dylib

CC		= gcc
CFLAGS	= -Wall -Wextra #-Werror
LIBFLAGS = \
	-L cub -lcub \
	-L ft_math -lftmath \
	-L dynarray -ldynarray \
	-L libft -lft \
	-L ft_printf -lftprintf \
	-L ./ -lmlx \



${NAME}: ${OBJS} ${MINILIBX} libs
	gcc ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

libs:
	make -C libft
	make -C ft_printf
	make -C ft_math
	make -C dynarray
	make -C cub

minilibx: ${MINILIBX}
${MINILIBX}:
	make -C minilibx
	cp minilibx/${MINILIBX} ./


all: ${NAME}

clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libs
