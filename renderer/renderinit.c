/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:19:27 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 17:17:31 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

const t_bbox	g_clipspace = {
	.min = {
		.vec3 = {
			.x = -1,
			.y = -1,
			.z = -1,
		}
	},
	.max = {
		.vec3 = {
			.x = 1,
			.y = 1,
			.z = 0,
		}
	},
};

extern void		renderinit(unsigned int x, unsigned int y)
{
	g_rendertex.width = x;
	g_rendertex.height = y;
	g_rendertex.ptr = mlx_new_image(g_mlx, x, y);
	g_rendertex.pixels = (union u_color*)mlx_get_data_addr(g_rendertex.ptr,
		&g_rendertex.bits_per_pixel, &g_rendertex.size_line,
		&g_rendertex.endian);
	g_rendertex.pixel_line =
		8 * g_rendertex.size_line / g_rendertex.bits_per_pixel;
	if (!g_rendertex.ptr)
		throw(errno, "[FATAL] Could not create render texture: %d", errno);
	if (!zbuffinit(x, y))
		throw(errno, "[FATAL] Could not initialize z-buffer: %d", errno);
}
