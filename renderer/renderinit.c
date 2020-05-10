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

const t_bbox2	g_clipspace = {
	.min = {
		.x = -1,
		.y = -1,
	},
	.max = {
		.x = 1,
		.y = 1,
	},
};

t_bbox2	g_frustrum = {
	.min = {
		.x = -0.1,
		.y = -20,
	},
	.max = {
		.x = 0.1,
		.y = -0.1,
	},
};

t_bbox2	g_screenbb = {
	.min = {
		.x = 0,
		.y = 0,
	},
};

t_color			g_fogcolor = { 0x888888 };

static void		frustruminit(void)
{
	g_aspect = g_screenhgt / (float)g_screenwdt;
	mxfrust2d(g_projmx, &g_frustrum);
}

static void		textureinit(unsigned int x, unsigned int y)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		g_rendertex[i].ptr = mlx_new_image(g_mlx, x, y);
		if (!g_rendertex[i].ptr)
			throw(errno, "[FATAL] Could not create render texture.");
		spyregpp(&g_rendertex[i].ptr);
		g_rendertex[i].width = x;
		g_rendertex[i].height = y;
		g_rendertex[i].pixels =
			(union u_color*)mlx_get_data_addr(g_rendertex[i].ptr,
				&g_rendertex[i].bits_per_pixel, &g_rendertex[i].size_line,
				&g_rendertex[i].endian);
		g_rendertex[i].pixel_line =
			8 * g_rendertex[i].size_line / g_rendertex[i].bits_per_pixel;
	}
}

extern void		renderinit(unsigned int x, unsigned int y)
{
	g_screenwdt = x;
	g_screenhgt = y;
	g_screenbb.max.x = x;
	g_screenbb.max.y = y;
	if (!zbuffinit(x, y))
		throw(errno, "[FATAL] Could not initialize z-buffer.");
	if (!rcolinit(x))
		throw(errno, "[FATAL] Could not initialize rendercols.");
	renderqueueinit();
	textureinit(x, y);
	frustruminit();
}
