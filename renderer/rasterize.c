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
** Computes the matrix that transform a pixel from screen space to UV space. (V
** ertical only)
** @param float[2][1]	The natrix to initialize.
** @param float depth	The distance to the wall.
** @param float angle	The x viewing angle. Default shoudl be 0.
** @param float altitude	The viewing altitude. Default should be 0.5.
*/

static void		getremapmx(float this[2][1], float depth, float altitude, float angle)
{
	this[0][0] = -depth;
	this[0][0] *= g_aspect / (0.5 * WALLSIZE);
	this[0][0] *= g_frustrum.min.x / g_frustrum.max.y;
	this[0][0] /= (float)g_screenhgt;
	this[1][0] = 0;
	this[1][0] = (angle - 0.5) * g_screenhgt * this[0][0];
	this[1][0] += altitude;
}

/*
** Actually renders a column on screen.
** @param unsigned int x	The coordinates of the column.
** @param float depth	The distance to the camera in clip space.
** @param float u	The x coordinate on the texture.
*/

static void __attribute__((hot))
				rasterizecol2(unsigned int x, float depth, float u)
{
	union u_color	color;
	unsigned int	y;
	float			remapmx[2][1];
	float			v;

	color.rgba.a = 0;
	color.rgba.r = (int)(255 * u);
	color.rgba.b = 255 - (int)(127.5 * (depth + 1));
	depth = depthunproject2d(depth, g_projmx);
	getremapmx(remapmx, depth, 0.5f, 0);
	y = -1;
	while (++y < g_screenhgt)
	{
		v = (y * remapmx[0][0]) + remapmx[1][0];
		color.rgba.g = 255 * v;
		if (0 <= v && v <= 1)
			renderset(x, g_screenhgt - 1 - y, color);
	}
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
	float	u;

	depth = (x * this->linescalar) + this->lineoffset;
	if (zbuffcmp(x, depth))
	{
		zbuffset(x, depth);
		u = mx2av1(this->figspace, x);
		u = mx2av1(this->umx, u);
		rasterizecol2(x, depth, u);
	}
}

static void __attribute__((hot))
				rasterizecoltopview(t_renderenv *this, unsigned int x)
{
	float	depth;
	float	u;

	depth = (x * this->linescalar) + this->lineoffset;
	if (1 || zbuffcmp(x, depth))
	{
		zbuffset(x, depth);
		u = mx2av1(this->figspace, x);
		depth += 1;
		depth *= 0.5 * g_screenhgt;
		if (0 <= depth && depth < g_screenhgt)
			renderset(x, g_screenhgt - 1 - (int)depth, (union u_color){.rgba={.r=255, .g=u*255, .b=255, .a=0}});
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
