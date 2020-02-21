/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:19:27 by abaur             #+#    #+#             */
/*   Updated: 2020/02/05 15:43:19 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

const t_bbox	g_clipspace = {
	.min = {
		.x = -1,
		.y = -1,
		.z = -1,
	},
	.max = {
		.x = 1,
		.y = 1,
		.z = 1,
	},
};

t_bbox	g_frustrum = {
	.min = {
		.x = -0.1,
		.z = -100,
	},
	.max = {
		.x = 0.1,
		.z = -0.1,
	},
};

t_bbox	g_screenbb = {
	.min = {
		.x = 0,
		.y = 0,
		.z = -1,
	},
	.max = {
		.z = 1,
	},
};

static void		frustruminit(void)
{
	float aspect;

	aspect = g_screenhgt / (float)g_screenwdt;
	g_frustrum.min.y = g_frustrum.min.x * aspect;
	g_frustrum.max.y = g_frustrum.max.x * aspect;
	mxfrust(g_projmx, &g_frustrum);
	g_cliporigin = mx4v3(g_projmx, &(t_v3){0, 0, 0});
}

static void		textureinit(unsigned int x, unsigned int y)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		g_rendertex[i].width = x;
		g_rendertex[i].height = y;
		g_rendertex[i].ptr = mlx_new_image(g_mlx, x, y);
		g_rendertex[i].pixels =
			(union u_color*)mlx_get_data_addr(g_rendertex[i].ptr,
				&g_rendertex[i].bits_per_pixel, &g_rendertex[i].size_line,
				&g_rendertex[i].endian);
		g_rendertex[i].pixel_line =
			8 * g_rendertex[i].size_line / g_rendertex[i].bits_per_pixel;
		if (!g_rendertex[i].ptr)
			throw(errno, "[FATAL] Could not create render texture: %d", errno);
	}
}

extern void		renderinit(unsigned int x, unsigned int y)
{
	g_screenwdt = x;
	g_screenhgt = y;
	g_screenbb.max.x = x - 1;
	g_screenbb.max.y = y - 1;
	if (!zbuffinit(x, y))
		throw(errno, "[FATAL] Could not initialize z-buffer: %d", errno);
	renderqueueinit();
	textureinit(x, y);
	frustruminit();
}
