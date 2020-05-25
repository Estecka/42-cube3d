SRCS	= main.c \
	throw.c \
	clampresolution.c \
	stringbuilder/stringbuilder.c \
	get_next_line/get_next_line.c \
	worldbuilder/worldbuilder.c worldbuilder/transform.c worldbuilder/renderworld.c \
	controller/controller.c \

OBJS	= ${SRCS:.c=.o}

OS		= $(shell uname)

LIBS = \
	mallocspy/libmallocspy.a \
	mlxpp/libmlxpp.a \
	libft/libft.a \
	ft_printf/libftprintf.a \
	ft_math/libftmath.a \
	dynarray/libdynarray.a \
	cub/libcub.a \
	renderer/librenderer.a \
	bitmap/libbitmap.a \


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



${NAME}: minilibx/mlx.h ${MINILIBX} ${LIBS} ${OBJS}
	clang ${OBJS} -o ${NAME} \
		${LIBFLAGS} \
		${CFLAGS} \

%.a: force_check
	make $(@F) -C $(@D)

minilibx/mlx.h:
	make mlx.h -C minilibx

ifeq (${OS}, Darwin)
${MINILIBX}:
	make -C minilibx/
	cp minilibx/${MINILIBX} ./
endif



all: ${NAME}

clean:
	for l in ${LIBS}; do \
		make clean -C $$(dirname $$l) ;\
	done
	rm -f *.o
	rm -f *.gch

fclean:
	for l in ${LIBS}; do \
		make fclean -C $$(dirname $$l) ;\
	done
	rm -f *.o
	rm -f *.gch
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: \
	force_check \
	all clean fclean re \
	minilibx \
