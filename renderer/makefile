SRCS = renderinit.c \
	rendertexture.c rendercol.c renderbboard.c zbuffer.c queue.c \
	clipquad.c truncate.c renderquad.c rasterize.c \

OBJS = ${SRCS:.c=.o}

NAME = librenderer.a
TEST = renderer.out
MLX = libmlx.dylib

CC     = gcc
CFLAGS = -Wall -Wextra -Ofast #-Werror
LIBFLAGS = \
		-L ./ -lmlx -lrenderer \
		-L ../libft -lft \
		-L ../ft_printf -lftprintf \
		-L ../ft_math -lftmath \
		-L ../dynarray -ldynarray \

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

test: ${TEST}
${TEST}: ${NAME} ${MLX} .test/main.c ../throw.c
	make libs -C ../
	gcc .test/main.c ../throw.c -o ${TEST} \
		${LIBFLAGS} \
		${CFLAGS} \

${MLX}: ../minilibx/${MLX}
	cp ../minilibx/${MLX} ./

../minilibx/${MLX}:
	make -C ../minilibx/


all: ${NAME} ${TEST}

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re test
