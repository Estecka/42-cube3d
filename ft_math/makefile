SRCS = \
	mxinit.c mxcpy.c \
	mxdet.c mxtrans.c mxadj.c mxinv.c \
	mxm.c mxv.c mxav.c mxfig.c \
	mxeuler.c mxangle.c mxproj.c \
	mxremap.c \
	cartesian.c \
	addvec.c subvec.c scalevec.c \
	dotprod.c crossp.c \
	floatminmax.c \
	figcontain.c \
	plane.c line2d.c\
	boundingbox.c boundingbox2.c \
	boundingbox2d.c boundingbox2dinter.c \

OBJS = ${SRCS:.c=.o}

NAME = libftmath.a

CC     = clang
CFLAGS = -O3 -Wall -Wextra -Werror


${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}
	rm -f *.gch

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
