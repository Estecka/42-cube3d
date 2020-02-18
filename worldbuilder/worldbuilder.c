/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldbuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:40:13 by abaur             #+#    #+#             */
/*   Updated: 2020/02/17 14:40:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worldbuilder_internals.h"

#include "../cub/cub.h"

const t_quad	g_wallmesh = {
	{-0.5, -0.5, 0.25},
	{-0.5, -0.5, 0},
	{+0.5, -0.5, 0},
	{+0.5, -0.5, 0.25},
};

t_quad	g_spritemesh = {
	{-1, 0, 1},
	{-1, 0, 0},
	{+1, 0, 0},
	{+1, 0, 1},
};

/*
** The matrices below appear transposed:
** {Xx, Xy, Xz, 0},
** {Yy, Yy, Yz, 0},
** {Zz, Zy, Zz, 0},
** {Tx, Ty, Tz, 1},
*/

static t_mx4	g_south = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
};

static t_mx4	g_east = {
	{ 0, 1, 0, 0},
	{-1, 0, 0, 0},
	{ 0, 0, 1, 0},
	{ 0, 0, 0, 1},
};

static t_mx4	g_north = {
	{-1, +0, 0, 0},
	{ 0, -1, 0, 0},
	{ 0, +0, 1, 0},
	{ 0, +0, 0, 1},
};
static t_mx4	g_west = {
	{0, -1, 0, 0},
	{1, +0, 0, 0},
	{0, +0, 1, 0},
	{0, +0, 0, 1},
};

static void		wallinitone(t_dynarray *array, unsigned int x, unsigned int y,
t_mx4 mx, void *texture)
{
	t_staticmesh	*values;
	t_v3			position;

	if (!dynexpand(array, +1))
		throw(errno, "[FATAL] Wall array expansion failed.");
	values = (t_staticmesh*)array->content;
	position = (t_v3){x, y, 0};
	mx4pos(mx, &position);
	mxquad3(g_wallmesh, values[array->length].vertices, mx);
	values[array->length].renderinfo.texture = texture;
	array->length++;
}

static void wallinit(t_cubworld *info)
{
	t_dynarray		array;
	unsigned int	x;
	unsigned int	y;

	dyninit(&array, sizeof(t_staticmesh), 256);
	y = -1;
	while (++y < info->mapsize.y)
	{
		x = -1;
		while (++x < info->mapsize.x)
			if (info->tiles[x][y] == '1')
			{
				if(tiles(info, x + 1, y) != '1' && tiles(info, x + 1, y) != 0)
					wallinitone(&array, x, y, g_east, info->east);
				if(tiles(info, x - 1, y) != '1' && tiles(info, x - 1, y) != 0)
					wallinitone(&array, x, y, g_west, info->west);
				if(tiles(info, x, y + 1) != '1' && tiles(info, x, y + 1) != 0)
					wallinitone(&array, x, y, g_north, info->north);
				if(tiles(info, x, y - 1) != '1' && tiles(info, x, y - 1) != 0)
					wallinitone(&array, x, y, g_south, info->south);
			}
	}
	g_world.wallcount = array.length;
	g_world.walls = (t_staticmesh*)array.content;
}

static void 	spriteinit(t_cubworld *info)
{
	t_dynarray		array;
	t_billboardmesh	*values;
	unsigned int	x;
	unsigned int	y;

	dyninit(&array, sizeof(t_billboardmesh), 32);
	y = -1;
	while (++y < info->mapsize.y)
	{
		x = -1;
		while (++x < info->mapsize.x)
			if (info->tiles[x][y] == '2')
			{
				if (!dynexpand(&array, +1))
					throw(errno, "[FATAL] Sprite array expansion failed");
				values = (t_billboardmesh*)array.content;
				values[array.length].renderinfo.texture = info->sprite;
				values[array.length].position = (t_v3){x, y, 0};
				array.length += 1;
			}
	}
	g_world.spritecount = array.length;
	g_world.sprites = (t_billboardmesh*)array.content;
}

extern void		worldinit(t_cubworld *info)
{
	g_world.player.position.x = info->playerspawn.x;
	g_world.player.position.y = info->playerspawn.y;
	g_world.player.position.z = 0.5;
	g_world.player.rotation.x = 90 * DEG2RAD;
	g_world.player.rotation.y = info->playerspawnangle;
	g_world.player.rotation.z = 0;
	retransform(&g_world.player);
	spriteinit(info);
	wallinit(info);
}