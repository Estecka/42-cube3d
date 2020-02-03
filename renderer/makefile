SRCS = renderinit.c \
	rendertexture.c zbuffer.c \

OBJS = ${SRCS:.c=.o}

NAME = librenderer.a
TEST = renderer.out
MLX = libmlx.dylib

CC     = gcc
CFLAGS = -Wall -Wextra #-Werror


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

test: ${TEST}
${TEST}: ${NAME} ${MLX}
	gcc .test/main.c -o ${TEST} \
	-L ./ -lmlx -lrenderer \
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
