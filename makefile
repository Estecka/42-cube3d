SRCS	= main.c \
	cub.c cub1.c cub2.c \

OBJS	= ${SRCS:.c=.o}

NAME	= cube3d.out
LIBFT	= libft/libft.a

CC		= gcc

CFLAGS	= -Wall -Wextra #-Werror


${NAME}: ${OBJS} ${LIBFT}
	gcc ${OBJS} -o ${NAME} \
	-L libft -lft \
	${CFLAGS}

libft: ${LIBFT}
${LIBFT}: 
	make -C libft

all: ${NAME}

clean:
	make clean -C libft
	rm -f ${OBJS}
	rm -f ${OBJS_BONUS}
	rm -f *.gch

fclean: clean
	make fclean -C libft
	rm -f ${LIBFT}
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libft
