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

/*
** Actually renders the column buffer on screen.
*/

void		extrude(void)
{
	unsigned int	x;
	unsigned int	y;
	float			v;

	y = -1;
	while (++y < g_screenhgt)
	{
		x = -1;
		while (++x < g_screenwdt)
		{
			if (g_rendercols[x].ymin <= y && y <= g_rendercols[x].ymax
				&& zbuffcmp(x, y, g_rendercols[x].depth))
			{
				v = mx2av1(g_rendercols[x].vmx, y);
				renderset(x, y, fogblend(
					mlx_img_sample(g_rendercols[x].texture,
						g_rendercols[x].u, 1 - v),
					g_rendercols[x].realdepth));
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

static void	rasterizecol(t_renderenv *this, unsigned int x)
{
	union u_v3	p;
	t_mx2a		vmxi;

	p.vec2.x = (2 * x / (float)g_screenwdt) - 1;
	p.vec2.y = (x * this->linescalar) + this->lineoffset;
	if (rcolzcmp(x, p.vec2.y))
	{
		g_rendercols[x].texture = this->texture;
		g_rendercols[x].depth = p.vec2.y;
		g_rendercols[x].realdepth = depthunproject2d(p.vec2.y, g_projmx);
		getvmx(g_rendercols[x].vmx, g_rendercols[x].realdepth);
		mx2ainv(g_rendercols[x].vmx, vmxi);
		g_rendercols[x].ymin = mx2av1(vmxi, 1);
		g_rendercols[x].ymax = mx2av1(vmxi, 0);
		p = homegeneous2d(&p.vec2, g_projmx);
		g_rendercols[x].u =
			mx2av1(this->umx, mx3v2(this->figspace, &p.vec2).vec2.x);
	}
}

/*
** Prints on screen a fully computed rendering environnement.
** @param t_renderenv* this
*/

void		rasterize(t_renderenv *this)
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
