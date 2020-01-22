/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 14:33:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_printf/ft_printf.h"

#include "cube3d.h"
#include "cub.h"

#include <stdio.h>
int		main(int argc, char **args)
{
	int			fd;
	t_mapfile	map;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file: %d", errno);
	ft_bzero(&map, sizeof(t_mapfile));
	parsefile(fd, &map);

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
		map.screenwdt, map.screenhgt,
		map.north, map.south, map.west, map.east,
		map.sprite,
		map.floorcol.r, map.floorcol.g, map.floorcol.b,
		map.ceilcol.r, map.ceilcol.g, map.ceilcol.b,
		map.mapwdt, map.maphgt
		);

	for (unsigned int y=0; y<map.maphgt; y++)
	{
		for (unsigned int x=0; x<map.mapwdt; x++)
		{
			printf("%c", map.tiles[(map.mapwdt * y) + x]);
		}
		printf("\n");
	}
}
