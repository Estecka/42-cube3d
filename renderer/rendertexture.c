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

static short	g_i;

/*
** Sets a single texel in the render texture.
** @param unsigned int x,y The coordinates of the texel.
** @param union u_color color The desired color.
*/

extern void		renderset(unsigned int x, unsigned int y, union u_color color)
{
	g_rendertex[g_i].pixels[(y * (g_rendertex[g_i].pixel_line)) + x] = color;
}

/*
** Fills the render texture using the given color.
** @param union u_color color The filler color.
*/

extern void		renderclear(union u_color color)
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
** Prints the render texture on screen, and clears the Z-buffer.
** Use this method in the MLX loop.
** @param void* mlx The MLX main pointer.
** @return int 0;
*/

extern void		renderflush(void)
{
	mlx_put_image_to_window(g_mlx, g_window, g_rendertex[g_i].ptr, 0, 0);
	g_i = !g_i;
	rcolclear();
	zbuffclear();
}

/*
** Saves the current rendertexture in a bitmap file.
** @param const char[] path	The path to the file to write.
*/

extern void		rendersave(const char *path)
{
	if (!bmp_write(&g_rendertex[g_i], path))
		throw(errno, "[BMP] Failed saving file output.");
}
