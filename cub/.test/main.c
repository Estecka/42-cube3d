/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 15:24:33 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "../../ft_printf/ft_printf.h"

#include "../../cube3d.h"
#include "../cub.h"


int		main(int argc, char **args)
{
	int			fd;
	union u_cub	map;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file: %d", errno);
	ft_bzero(&map.file, sizeof(t_cubfile));
	parsefile(&map.file, fd);

	printf("\
R %d %d \n\
NO %s \n\
SO %s \n\
WE %s \n\
EA %s \n\
S  %s \n\
F  %d,%d,%d \n\
C  %d,%d,%d \n\
\
Map size: %u %u \n\
Map content: \n\
",
		map.file.resolution.x, map.file.resolution.y,
		map.file.north, map.file.south, map.file.west, map.file.east,
		map.file.sprite,
		map.file.floorcol.rgb.r, map.file.floorcol.rgb.g, map.file.floorcol.rgb.b,
		map.file.ceilcol.rgb.r, map.file.ceilcol.rgb.g, map.file.ceilcol.rgb.b,
		map.file.mapsize.x, map.file.mapsize.y
		);

	for (int y=0; y<map.file.mapsize.y; y++)
	{
		for(char* c=map.file.tiles[y]; *c != '\0'; c++)
			printf("%c ", *c);
		printf("\n");
	}


	cubfile2world(&map);
	printf("\
R %d %d \n\
NO %p \n\
SO %p \n\
WE %p \n\
EA %p \n\
S  %p \n\
F  %d,%d,%d \n\
C  %d,%d,%d \n\
\n\
Player pos: %d %d\n\
Player dir: %f\n\
\n\
Map size: %u %u \n\
Map content: \n\
",
		map.world.resolution.x, map.world.resolution.y,
		map.world.north, map.world.south, map.world.west, map.world.east,
		map.world.sprite,
		map.world.floorcol.rgb.r, map.world.floorcol.rgb.g, map.world.floorcol.rgb.b,
		map.world.ceilcol.rgb.r, map.world.ceilcol.rgb.g, map.world.ceilcol.rgb.b,
		map.world.playerspawn.x, map.world.playerspawn.y,
		map.world.playerspawnangle,
		map.world.mapsize.x, map.world.mapsize.y
		);
		
	for (int y=map.world.mapsize.y-1; 0<=y; y--)
	{
		for (int x=0; x<map.world.mapsize.x; x++)
			printf("%c ", map.world.tiles[x][y]);
		printf("\n");
	}
}
