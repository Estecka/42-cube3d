/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:23:47 by abaur             #+#    #+#             */
/*   Updated: 2020/03/11 16:23:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Blends a color with the fog.
** @param t_color src	The source color.
** @param float depth	The depth in view space.
*/

t_color			fogblend(t_color src, float depth)
{
	t_color result;
	int		i;

	if (depth > 0)
		depth = 0;
	if (depth < g_frustrum.min.y)
		depth = g_frustrum.min.y;
	depth /= g_frustrum.min.y;
	result.rgba.a = 0;
	i = -1;
	while (++i < 3)
		result.bytes[i] = (depth * (unsigned char)g_fogcolor.bytes[i])
			+ ((1 - depth) * (unsigned char)src.bytes[i]);
	result.rgba.a = 0;
	return (result);
}

static float	getdepth(unsigned int y)
{
	float altitude;
	float r;

	r = y - (g_angle * g_screenhgt);
	r = (2 * r / (float)g_screenhgt);
	altitude = r < 0 ? WALLSIZE - g_altitude : g_altitude;
	r = r < 0 ? r : -r;
	r = altitude * g_frustrum.max.y / (g_aspect * g_frustrum.min.x * r);
	return (r);
}

/*
** Fills the render texture with two colors.
** @param union u_color f	The floor color.
** @param union u_color c	The sky color.
*/

extern void		rendersky(union u_color f, union u_color c)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	horizon;
	t_color			color;

	g_angle = g_angle < 0 ? 0 : g_angle;
	g_angle = g_angle > 1 ? 1 : g_angle;
	horizon = g_screenhgt * g_angle;
	y = -1;
	while (++y < g_screenhgt)
	{
		color = fogblend(y < horizon ? c : f, getdepth(y));
		x = -1;
		while (++x < g_screenwdt)
			renderset(x, y, color);
	}
}
