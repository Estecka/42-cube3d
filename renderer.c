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

static void 		mlx_img_set(t_mlx_img *img, int x, int y, union u_color color)
{
	char *addr;

	addr = img->content + (y * img->size_line) + (x * img->bits_per_pixel / 8);
	if (img->endian)
		*(t_rgba*)addr = color.rgba;
	else
		*(t_rgb*)addr = color.rgb;
}

extern int			graphhook(void *null)
{
	(void)null;
	mlx_put_image_to_window(g_mlx, g_window, g_skybox.content, 0, 0);
	return (0);
}

extern void			graphicinit(t_mapfile *map)
{
	unsigned int	x;
	unsigned int	y;
	union u_color	color;

	g_skybox.width = map->screenwdt;
	g_skybox.height = map->screenhgt;
	g_skybox.content = 
		(char*)mlx_new_image(g_mlx, g_skybox.width, g_skybox.height);
	if (!g_skybox.content)
		throw(errno, "[FATAL] Could not create skybox: %d", errno);
	y = -1;
	return;
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
