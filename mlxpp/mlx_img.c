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

static unsigned int	g_xcache;
static unsigned int	g_ycache;
static t_mlx_img	*g_texcache;
static t_color		g_colorcache;

extern t_color	mlx_img_sample(t_mlx_img *this, float u, float v)
{
	unsigned int	x;
	unsigned int	y;

	if (u <= 0)
		x = 0;
	else if (u >= 1)
		x = this->width - 1;
	else
		x = u * (this->width - 1);
	if (v <= 0)
		y = 0;
	else if (v >= 1)
		y = this->height - 1;
	else
		y = v * (this->height - 1);
	if (x != g_xcache || y != g_ycache || this != g_texcache)
	{
		g_xcache = x;
		g_ycache = y;
		g_texcache = this;
		g_colorcache = this->pixels[(y * (this->pixel_line)) + x];
	}
	return (g_colorcache);
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
