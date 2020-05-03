/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:23:21 by abaur             #+#    #+#             */
/*   Updated: 2020/01/23 14:48:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../ft_math/ft_math.h"
#include "cub_util.h"

#define WMAX 2560
#define HMAX 1440

/*
** Identify the player on the map, and replaces it with a 0.
** Asserts that there is only one player.
** @param union u_cub this
*/

static void	findplayer(union u_cub *this)
{
	int		x;
	int		y;
	char	c;

	this->world.playerspawnangle = NAN;
	y = -1;
	while (++y < this->file.mapsize.y)
	{
		x = -1;
		while ((c = this->file.tiles[y][++x]))
			if (ft_strcontain("NEWS", c))
			{
				throwif(!isnan(this->world.playerspawnangle),
					-1, "Extraneous player at %d %d:\n%s",
					x, y, this->file.tiles[y]);
				this->file.tiles[y][x] = '0';
				this->world.playerspawn = (t_v2i) {x, y};
				this->world.playerspawnangle =
					((c == 'W') * 1) + ((c == 'S') * 2) + ((c == 'E') * 3);
				this->world.playerspawnangle *= 90 * DEG2RAD;
			}
	}
}

/*
** Converts the tile list from an array of strings to a grid of char.
** Empty spaces are filled with '\0'.
** The source arrays are freed.
** @param union u_cub* this
*/

static void	gridify(union u_cub *this)
{
	char*const		*grid;
	signed int		x;
	signed int		y;

	grid = (char*const*)malloc2d(this->file.mapsize.x, this->file.mapsize.y,
	sizeof(char));
	if (!grid)
		throw(errno, "[FATAL] Grid allocation failed.");
	y = -1;
	while (++y < this->file.mapsize.y)
	{
		x = -1;
		while (this->file.tiles[y][++x] != '\0')
			grid[x][y] = this->file.tiles[y][x] == ' ' ?
				0 : this->file.tiles[y][x];
		free(this->file.tiles[y]);
	}
	free(this->file.tiles);
	this->world.tiles = grid;
}

/*
** Converts a cubfile to cubworld.
** @param union u_cub* this
*/

extern void	cubfile2world(union u_cub *this)
{
	if (this->file.resolution.x > WMAX)
		this->world.resolution.x = WMAX;
	if (this->file.resolution.y > HMAX)
		this->world.resolution.y = HMAX;
	this->world.floorcol.rgba.a = 0;
	this->world.ceilcol.rgba.a = 0;
	findplayer(this);
	gridify(this);
	checkfullenclosure(&this->world);
}

/*
** Get a tile at the given coordinates.
** This can safely fetch out of bound.
** @param t_cubworld* this
** @param int x,y	The coordinates to fetch.
** @return	The tile, or '\0' if out of bound.
*/

extern char	tile(t_cubworld *this, int x, int y)
{
	if (x < 0 || y < 0 || x >= this->mapsize.x || y >= this->mapsize.y)
		return (0);
	else
		return (this->tiles[x][y]);
}
