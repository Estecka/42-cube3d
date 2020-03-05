/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertexture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:19:42 by abaur             #+#    #+#             */
/*   Updated: 2020/02/05 15:08:45 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

static short g_i;

/*
** Sets a single texel in the render texture.
** @param unsigned int x,y The coordinates of the texel.
** @param union u_color color The desired color.
*/

extern void	renderset(unsigned int x, unsigned int y, union u_color color)
{
	g_rendertex[g_i].pixels[(y * (g_rendertex[g_i].pixel_line)) + x] = color;
}

/*
** Fills the render texture using the given color.
** @param union u_color color The filler color.
*/

extern void	renderclear(union u_color color)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < g_screenhgt)
	{
		x = 0;
		while (x < g_screenwdt)
		{
			renderset(x, y, color);
			x++;
		}
		y++;
	}
}

/*
** Fills the render texture with two colors.
** @param union u_color f	The floor color.
** @param union u_color c	The sky color.
*/

extern void	rendersky(union u_color f, union u_color c)
{
	unsigned int x;
	unsigned int y;
	unsigned int h;

	if (g_angle > 1)
		g_angle = 1;
	if (g_angle < 0)
		g_angle = 0;
	h = g_screenhgt * g_angle;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < g_screenwdt)
			renderset(x, y, c);
	}
	y--;
	while (++y < g_screenhgt)
	{
		x = -1;
		while (++x < g_screenwdt)
			renderset(x, y, f);
	}
}

/*
** Prints the render texture on screen, and clears the Z-buffer.
** Use this method in the MLX loop.
** @param void* mlx The MLX main pointer.
** @return int 0;
*/

extern void	renderflush(void)
{
	mlx_put_image_to_window(g_mlx, g_window, g_rendertex[g_i].ptr, 0, 0);
	g_i = !g_i;
	rcolclear();
	zbuffclear();
}
