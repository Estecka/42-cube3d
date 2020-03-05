/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:24:24 by abaur             #+#    #+#             */
/*   Updated: 2020/03/05 11:24:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxpp.h"
#include "../minilibx/mlx.h"

extern void		mlx_img_set(t_mlx_img *this, unsigned int x, unsigned int y,
	union u_color color)
{
	this->pixels[(y * (this->pixel_line)) + x] = color;
}

extern t_color	mlx_img_get(t_mlx_img *this, unsigned int x, unsigned int y)
{
	return (this->pixels[(y * (this->pixel_line)) + x]);
}

extern t_color	*mlx_img_getptr(t_mlx_img *this, unsigned int x, unsigned int y)
{
	return (&this->pixels[(y * (this->pixel_line)) + x]);
}

extern short	mlx_img_init(t_mlx_img *this, unsigned int x, unsigned int y)
{
	this->width = x;
	this->height = y;
	this->ptr = mlx_new_image(g_mlx, x, y);
	if (!this->ptr)
		return (0);
	this->pixels =
		(t_color*)mlx_get_data_addr(
			this->ptr,
			&this->bits_per_pixel, &this->size_line,
			&this->endian);
	this->pixel_line = 8 * this->size_line / this->bits_per_pixel;
	return (1);
}
