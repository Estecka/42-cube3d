/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:53:07 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 17:16:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

#include "cube3d.h"
#include "cub.h"

#include "minilibx/mlx.h"


static t_mlx_img	g_skybox = { 0 };

static void 		mlx_img_set(
	t_mlx_img *img, int x, int y, union u_color color)
{
	img->pixels[(y * img->width) + x] = color;
}

extern int			graphhook(void *null)
{
	(void)null;
	mlx_put_image_to_window(g_mlx, g_window, g_skybox.ptr, 0, 0);
	return (0);
}

extern void			graphicinit(t_mapfile *map)
{
	unsigned int	x;
	unsigned int	y;
	union u_color	color;

	g_skybox.width = map->screenwdt;
	g_skybox.height = map->screenhgt;
	g_skybox.ptr = mlx_new_image(g_mlx, g_skybox.width, g_skybox.height);
	g_skybox.pixels = (union u_color*)mlx_get_data_addr(g_skybox.ptr,
			&g_skybox.bits_per_pixel, &g_skybox.size_line, &g_skybox.endian);
	if (!g_skybox.ptr)
		throw(errno, "[FATAL] Could not create skybox: %d", errno);
	y = -1;
	while (++y < g_skybox.height)
	{
		if (y < (g_skybox.height / 2))
			color = map->ceilcol;
		else
			color = map->floorcol;
		x = -1;
		while (++x < g_skybox.width)
			mlx_img_set(&g_skybox, x, y, color);
	}
}
