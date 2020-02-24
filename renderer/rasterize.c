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
** Prints on screen a fully computed rendering environnement.
** @param t_renderenv* this
*/

static void __attribute__((hot))
				rasterizecol(t_renderenv *this, unsigned int x)
{
	union u_color	color;
	struct s_v2		p;
	struct s_v2		uv;

	color.rgba.a = 0;
	color.rgba.r = 0;
	p.x = (float)x;
	p.y = (p.x * this->linescalar) + this->lineoffset;
	if (zbuffcmp(x, p.y))
	{
		zbuffset(x, p.y);
		uv.x = (p.x * this->figspace[0][0]) + this->figspace[1][0];
		color.rgba.b = 255 - (int)(128 * (p.y + 1));
		color.rgba.g = (int)(255 * uv.x);
		for (unsigned int y=0; y<g_screenhgt; y++)
			renderset(x, g_screenhgt - 1 - y, color);
	}
}

void __attribute__((hot))
			rasterize(t_renderenv *this)
{
	unsigned int	x;
	unsigned int	max;

	x = (int)this->pixvert[0].x;
	if (x < 0)
		x = 0;
	max = this->pixvert[1].x;
	if (max > g_screenwdt)
		max = 0;
	while (x < max)
	{
		rasterizecol(this, x);
		x++;
	}
}
