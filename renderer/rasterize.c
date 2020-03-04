/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:53:01 by abaur             #+#    #+#             */
/*   Updated: 2020/02/10 12:53:03 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"
#define WALLSIZE 1

/*
** Actually renders the column buffer on screen.
*/

void			extrude()
{
	unsigned int 	x;
	unsigned int 	y;
	union u_color	color;
	float			v;

	color.rgba.a = 0;
	y = -1;
	while (++y < g_screenhgt)
	{
		x = -1;
		while (++x < g_screenwdt)
		{
			if (zbuffcmp(x, y, g_rendercols[x].depth))
			{
				color.rgba.r = (int)(255 * g_rendercols[x].u);
				color.rgba.b = 255 - (int)(127.5 * (g_rendercols[x].depth + 1));
				v = mx2av1(g_rendercols[x].vmx, y);
				color.rgba.g = 255 * v;
				if (0 <= v && v <= 1)
					renderset(x, y, color);
			}
		}
	}
}

/*
** Computes the matrix that transform a pixel from screen space to UV space. (V
** ertical only)
** @param float[2][1]	The natrix to initialize.
** @param float depth	The distance to the wall in view space.
*/

void		getvmx(float this[2][1], float depth)
{
	this[0][0] = depth;
	this[0][0] *= g_aspect / (0.5 * WALLSIZE);
	this[0][0] *= g_frustrum.min.x / g_frustrum.max.y;
	this[0][0] /= (float)g_screenhgt;
	this[1][0] = 0;
	this[1][0] = -g_angle * g_screenhgt * this[0][0];
	this[1][0] += g_altitude;
}

/*
** Checks the column against the depth buffer.
** If applicable, computes the U of the UVs and renders the column.
** @param t_renderenv* this
** @param unsigned int x	The coordinate of the column to render.
*/

static void __attribute__((hot))
				rasterizecol(t_renderenv *this, unsigned int x)
{
	float	depth;

	depth = (x * this->linescalar) + this->lineoffset;
	if (rcolzcmp(x, depth))
	{
		g_rendercols[x].depth = depth;
		g_rendercols[x].u = mx2av1(this->umx, mx2av1(this->figspace, x));
		depth = depthunproject2d(depth, g_projmx);
		getvmx(g_rendercols[x].vmx, depth);
	}
}

/*
** Prints on screen a fully computed rendering environnement.
** @param t_renderenv* this
*/

void __attribute__((hot))
			rasterize(t_renderenv *this)
{
	unsigned int	x;
	unsigned int	max;

	if (this->pixvert[0].x < 0)
		x = 0;
	else
		x = (int)this->pixvert[0].x;
	max = this->pixvert[1].x;
	if (max >= g_screenwdt)
		max = g_screenwdt - 1;
	while (x < max)
	{
		rasterizecol(this, x);
		x++;
	}
}
