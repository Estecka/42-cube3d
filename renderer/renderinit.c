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

static void		projmxinit()
{
	t_bbox frustrum;
	float aspect;

	aspect = g_screenhgt / (float)g_screenwdt;
	frustrum.min.vec3.x = 1;
	frustrum.max.vec3.x = -1;
	frustrum.min.vec3.y =  aspect;
	frustrum.max.vec3.y = -aspect;
	frustrum.min.vec3.z = 1;
	frustrum.max.vec3.z = 10;
	mxprojbb(g_projmx, &frustrum);

	//test
	union u_v4 min, max;
	min = mx4v3(g_projmx, (float*)&frustrum.min);
	max = mx4v3(g_projmx, (float*)&frustrum.max);
	min.vec3 = cartesian(min).vec3;
	max.vec3 = cartesian(max).vec3;
	printf("Calculated clip space: \n %f %f %f \n %f %f %f \n", 
		min.vec3.x, min.vec3.y, min.vec3.z
		max.vec3.x, max.vec3.y, max.vec3.z);
}

extern void		renderinit(unsigned int x, unsigned int y)
{
	int i;

	g_screenwdt = x;
	g_screenhgt = y;
	i = -1;
	while(++i < 2)
	{
		g_rendertex[i].width = x;
		g_rendertex[i].height = y;
		g_rendertex[i].ptr = mlx_new_image(g_mlx, x, y);
		g_rendertex[i].pixels = (union u_color*)mlx_get_data_addr(g_rendertex[i].ptr,
		&g_rendertex[i].bits_per_pixel, &g_rendertex[i].size_line,
		&g_rendertex[i].endian);
		g_rendertex[i].pixel_line =
			8 * g_rendertex[i].size_line / g_rendertex[i].bits_per_pixel;
		if (!g_rendertex[i].ptr)
			throw(errno, "[FATAL] Could not create render texture: %d", errno);
	}
	if (!zbuffinit(x, y))
		throw(errno, "[FATAL] Could not initialize z-buffer: %d", errno);
}
