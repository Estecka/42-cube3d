#!/bin/zsh

DIRS=(
	.
	bitmap
	controller
	cub
	dynarray
	ft_math
	ft_printf
	get_next_line
	libft
	mallocspy
	mlxpp
	renderer
	stringbuilder
	worldbuilder
	);

for d in $DIRS;
do;
	~/.norminette/norminette.rb \
		${d}/*.c \
		${d}/*.h \
		;
done;