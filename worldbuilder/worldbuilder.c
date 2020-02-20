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
	{-0.5, 1, 0.5},
	{-0.5, 0, 0.5},
	{+0.5, 0, 0.5},
	{+0.5, 1, 0.5},
};

t_quad	g_spritemesh = {
	{-1, 1, 0},
	{-1, 0, 0},
	{+1, 0, 0},
	{+1, 1, 0},
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
	{ 0, 0, 1, 0},
	{ 0, 1, 0, 0},
	{-1, 0, 0, 0},
	{ 0, 0, 0, 1},
};

static t_mx4	g_north = {
	{-1, 0, +0, 0},
	{ 0, 1, +0, 0},
	{ 0, 0, -1, 0},
	{ 0, 0, +0, 1},
};
static t_mx4	g_west = {
	{0, 0, -1, 0},
	{0, 1, +0, 0},
	{1, 0, +0, 0},
	{0, 0, +0, 1},
};

static void		wallinitone(t_dynarray *array, t_v2i pos,
t_mx4 mx, void *texture)
{
	t_staticmesh	*values;
	t_v3			position;

	if (!dynexpand(array, +1))
		throw(errno, "[FATAL] Wall array expansion failed.");
	values = (t_staticmesh*)array->content;
	position = (t_v3){pos.x, 0, pos.y};
	mx4pos(mx, &position);
	mxquad3(g_wallmesh, values[array->length].vertices, mx);
	values[array->length].renderinfo.texture = texture;
	array->length++;
}

static void		wallinitfour(t_cubworld *info, t_dynarray *array, t_v2i i)
{
	if (tile(info, i.x + 1, i.y) != '1' && tile(info, i.x + 1, i.y) != '\0')
		wallinitone(array, i, g_west, info->west);
	if (tile(info, i.x - 1, i.y) != '1' && tile(info, i.x - 1, i.y) != '\0')
		wallinitone(array, i, g_east, info->east);
	if (tile(info, i.x, i.y + 1) != '1' && tile(info, i.x, i.y + 1) != '\0')
		wallinitone(array, i, g_south, info->south);
	if (tile(info, i.x, i.y - 1) != '1' && tile(info, i.x, i.y - 1) != '\0')
		wallinitone(array, i, g_north, info->north);
}

static void		wallinit(t_cubworld *info)
{
	t_dynarray		array;
	t_v2i			i;

	dyninit(&array, sizeof(t_staticmesh), 256);
	i.y = -1;
	while (++i.y < info->mapsize.y)
	{
		i.x = -1;
		while (++i.x < info->mapsize.x)
			if (info->tiles[i.x][i.y] == '1')
				wallinitfour(info, &array, i);
	}
	g_world.wallcount = array.length;
	g_world.walls = (t_staticmesh*)array.content;
}

static void		spriteinit(t_cubworld *info)
{
	t_dynarray		array;
	t_billboardmesh	*values;
	signed int		x;
	signed int		y;

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
				values[array.length].position = (t_v3){x, 0, y};
				array.length += 1;
			}
	}
	g_world.spritecount = array.length;
	g_world.sprites = (t_billboardmesh*)array.content;
}
extern void		worldinit(t_cubworld *info)
{
	g_player.position.x = info->playerspawn.x;
	g_player.position.z = info->playerspawn.y;
	g_player.position.y = 0.5;
	g_player.rotation.x = 0;
	g_player.rotation.y = info->playerspawnangle;
	g_player.rotation.z = 0;
	retransform(&g_player);
	spriteinit(info);
	wallinit(info);
}
