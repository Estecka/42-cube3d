SRCS	= main.c \
	cub.c cub1.c \

OBJS	= ${SRCS:.c=.o}

NAME	= cube3d.out
LIBFT	= libft/libft.a
PRINTF	= ft_printf/libftprintf.a

CC		= gcc

CFLAGS	= -Wall -Wextra #-Werror


${NAME}: ${OBJS} ${LIBFT} ${PRINTF}
	gcc ${OBJS} -o ${NAME} \
	-L libft -lft \
	-L ft_printf -lftprintf \
	${CFLAGS}

libft: ${LIBFT}
${LIBFT}: 
	make -C libft

printf: ${PRINTF}
${PRINTF}:
	make -C ft_printf

all: ${NAME}

clean:
	rm -f ${OBJS}
	rm -f ${OBJS_BONUS}
	rm -f *.gch

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -f ${LIBFT}
	rm -f ${PRINTF}
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re libft printf
