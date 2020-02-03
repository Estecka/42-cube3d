/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertexture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:19:42 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 17:06:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

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
	mlx_img_set(&g_rendertex, x, y, color);
}

/*
** Fills the render texture using the given color.
** @param union u_color color The filler color.
*/

extern void	renderclear(union u_color color)
{
	unsigned int x;
	unsigned int y;

	x = 0;
	while (x < g_rendertex.width)
	{
		y = 0;
		while (y < g_rendertex.height)
		{
			mlx_img_set(&g_rendertex, x, y, color);
			y++;
		}
		x++;
	}
}

/*
** Prints the render texture on screen, and clears the Z-buffer.
** Use this method in the MLX loop.
** @param void* mlx The MLX main pointer.
** @return int 0;
*/

extern int	renderflush(void *mlx)
{
	mlx_put_image_to_window(mlx, g_window, g_rendertex.ptr, 0, 0);
	zbuffclear();
	return (0);
}
