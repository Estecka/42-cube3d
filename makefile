SRCS	= main.c \
	throw.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	worldbuilder/worldbuilder.c worldbuilder/transform.c worldbuilder/renderworld.c \
	controller/controller.c \

OBJS	= ${SRCS:.c=.o}

NAME	= cub3d.out
MINILIBX = libmlx.dylib

CC		= gcc
CFLAGS	= -O3 -Wall -Wextra -Werror
LIBFLAGS = \
	-L cub -lcub \
	-L renderer -lrenderer \
	-L bitmap -lbitmap \
	-L ft_math -lftmath \
	-L dynarray -ldynarray \
	-L libft -lft \
	-L ft_printf -lftprintf \
	-L mlxpp -lmlxpp \
	-L minilibx/linux -lmlx \



${NAME}: ${MINILIBX} libs ${OBJS} 
	gcc ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

libs: ${MINILIBX}
	make -C mlxpp
	make -C libft
	make -C ft_printf
	make -C ft_math
	make -C dynarray
	make -C cub
	make -C renderer
	make -C bitmap

minilibx: ${MINILIBX}
${MINILIBX}:
	make -C minilibx/linux
	cp minilibx/linux/mlx.h minilibx/
	#cp minilibx/${MINILIBX} ./ #Used for the metal MLX on mac-os, which builds a dynamic library.


all: ${NAME}

clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libs
