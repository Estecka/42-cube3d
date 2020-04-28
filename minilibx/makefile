OS		= $(shell uname)

ifeq (${OS}, Linux)
NAME = libmlx.a
SUBDIR = linux/
else
NAME = libmlx.dylib
SUBDIR = macos-metal/
endif

all: mlx.h ${NAME}

mlx.h:
	cp ${SUBDIR}/mlx.h ./

${NAME}:
	make -C ${SUBDIR}
	cp ${SUBDIR}${NAME} ./

clean:
	make clean -C ${SUBDIR}
	rm -f ${SUBDIR}${NAME}
fclean: clean
	rm -f ${NAME}
	rm -f ${mlx.h}

re: fclean all

.PHONY: all clean fclean re