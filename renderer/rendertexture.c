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
** Sets a single texel on a mlx image.
** @param t_mlx_img* this Ths image to edit.
** @param unsigned int x,y The coordinates of the texel to set.
** @param union u_color col The color to applyto the texel.
*/

void		mlx_img_set(t_mlx_img *this, unsigned int x, unsigned int y,
	union u_color color)
{
	this->pixels[(y * (this->pixel_line)) + x] = color;
}

/*
** Sets a single texel in the render texture.
** @param unsigned int x,y The coordinates of the texel.
** @param union u_color color The desired color.
*/

extern void	renderset(unsigned int x, unsigned int y, union u_color color)
{
	mlx_img_set(&g_rendertex[g_i], x, y, color);
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
	while (y < g_rendertex[g_i].height)
	{
		x = 0;
		while (x < g_rendertex[g_i].width)
		{
			mlx_img_set(&g_rendertex[g_i], x, y, color);
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
			mlx_img_set(&g_rendertex[g_i], x, y, c);
	}
	y--;
	while (++y < g_screenhgt)
	{
		x = -1;
		while (++x < g_screenwdt)
			mlx_img_set(&g_rendertex[g_i], x, y, f);
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
