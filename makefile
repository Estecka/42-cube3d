SRCS	= main.c \
	throw.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	worldbuilder/worldbuilder.c worldbuilder/transform.c worldbuilder/renderworld.c \
	controller/controller.c \

OBJS	= ${SRCS:.c=.o}

OS		= $(shell uname)

NAME	= cub3d.out
ifeq (${OS}, Linux)
MINILIBX =	minilibx/libmlx.a
else
MINILIBX = libmlx.dylib
endif

CC		= clang
CFLAGS	= -O3 -Wall -Wextra -Werror
LIBFLAGS = \
	-L cub -lcub \
	-L renderer -lrenderer \
	-L bitmap -lbitmap \
	-L ft_math -lftmath \
	-L dynarray -ldynarray \
	-L ft_printf -lftprintf \
	-L libft -lft \
	-L mlxpp -lmlxpp \

ifeq (${OS}, Linux)
LIBFLAGS += \
	-L minilibx/ -lmlx \
	-lbsd -lX11 -lXext \
	-lm \

else
LIBFLAGS += \
	-L ./ -lmlx\

endif



${NAME}: minilibx libs ${OBJS} 
	clang ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

libs: minilibx
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
	make -C minilibx/
ifeq (${OS}, Darwin)
	cp minilibx/${MINILIBX} ./
endif



all: ${NAME}

clean:
	rm -f *.o
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	all clean fclean re \
	libs \
	minilibx \
