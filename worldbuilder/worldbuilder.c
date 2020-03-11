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
#include "../bitmap/bitmap.h"

const t_seg2	g_wallmesh = {
	{-0.5, 0.5},
	{+0.5, 0.5},
};

/*
** The matrices below appear transposed:
** {Xx, Xy, 0},
** {Yy, Yy, 0},
** {Tx, Ty, 1},
*/

static t_mx3	g_south = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
};

static t_mx3	g_east = {
	{ 0, 1, 0},
	{-1, 0, 0},
	{ 0, 0, 1},
};

static t_mx3	g_north = {
	{-1, +0, 0},
	{ 0, -1, 0},
	{ 0, +0, 1},
};
static t_mx3	g_west = {
	{0, -1, 0},
	{1, +0, 0},
	{0, +0, 1},
};

static void		wallinitone(t_dynarray *array, t_v2i pos,
t_mx3 mx, t_mlx_img *texture)
{
	t_staticmesh	*values;
	struct s_v2		position;

	if (!dynexpand(array, +1))
		throw(errno, "[FATAL] Wall array expansion failed.");
	values = (t_staticmesh*)array->content;
	position = (t_v2){pos.x, pos.y};
	mx3pos(mx, &position);
	values[array->length].vertices[0] =  mx3v2(mx, &g_wallmesh[0]).vec2;
	values[array->length].vertices[1] =  mx3v2(mx, &g_wallmesh[1]).vec2;
	values[array->length].renderinfo.texture = texture;
	array->length++;
}

static void		wallinitfour(t_cubworld *info, t_dynarray *array, t_v2i i)
{
	if (tile(info, i.x + 1, i.y) != '1' && tile(info, i.x + 1, i.y) != '\0')
		wallinitone(array, i, g_west, &info->west);
	if (tile(info, i.x - 1, i.y) != '1' && tile(info, i.x - 1, i.y) != '\0')
		wallinitone(array, i, g_east, &info->east);
	if (tile(info, i.x, i.y + 1) != '1' && tile(info, i.x, i.y + 1) != '\0')
		wallinitone(array, i, g_south, &info->south);
	if (tile(info, i.x, i.y - 1) != '1' && tile(info, i.x, i.y - 1) != '\0')
		wallinitone(array, i, g_north, &info->north);
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
	t_v2			*values;
	signed int		x;
	signed int		y;

	dyninit(&array, sizeof(t_v2), 32);
	y = -1;
	while (++y < info->mapsize.y)
	{
		x = -1;
		while (++x < info->mapsize.x)
			if (info->tiles[x][y] == '2')
			{
				if (!dynexpand(&array, +1))
					throw(errno, "[FATAL] Sprite array expansion failed");
				values = (t_v2*)array.content;
				values[array.length] = (t_v2){x, y};
				array.length += 1;
			}
	}
	g_world.spritecount = array.length;
	g_world.sprites = (t_v2*)array.content;
}

extern void		worldinit(t_cubworld *info)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (!bmp_read(&(&info->north)[i], (&info->northpath)[i]))
			throw(errno ? errno : -1, "Failed to read texture: \n%s",
			info->northpath);
	}
	g_player.position.x = info->playerspawn.x;
	g_player.position.y = info->playerspawn.y;
	g_player.rotation = info->playerspawnangle;
	g_world.spritetexture = &info->sprite;
	retransform(&g_player);
	spriteinit(info);
	wallinit(info);
}
