SRCS	= main.c \
	throw.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	worldbuilder/worldbuilder.c worldbuilder/transform.c worldbuilder/renderworld.c \
	controller/controller.c \

OBJS	= ${SRCS:.c=.o}

OS		= $(shell uname)

LIBS = \
	mallocspy \
	mlxpp \
	libft \
	ft_printf \
	ft_math \
	dynarray \
	cub \
	renderer \
	bitmap \

NAME	= cub3D.out
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
	-L mallocspy -lmallocspy \
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



${NAME}: minilibx/mlx.h ${OBJS} 
	make libs
	clang ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

libs: minilibx
	for l in ${LIBS}; do \
		make -C $$l ;\
	done

minilibx/mlx.h: minilibx
minilibx: ${MINILIBX}
${MINILIBX}:
	make -C minilibx/
ifeq (${OS}, Darwin)
	cp minilibx/${MINILIBX} ./
endif



all: ${NAME}

clean:
	for l in ${LIBS}; do \
		make clean -C $$l ;\
	done
	rm -f *.o
	rm -f *.gch

fclean:
	for l in ${LIBS}; do \
		make fclean -C $$l ;\
	done
	rm -f *.o
	rm -f *.gch
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	all clean fclean re \
	libs \
	minilibx \
