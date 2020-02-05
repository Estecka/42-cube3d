/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderquad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:40:44 by abaur             #+#    #+#             */
/*   Updated: 2020/02/05 16:11:56 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Convert a quad's point from clip space to screen space.
** @param const t_quad src The quad's points in clip space.
** @param t_quad dst Outputs the points pixel coordinates.
*/

static void	cliptopix(const t_quad src, t_quad dst)
{
	for (int i=0; i<4; i++)
	{
		dst[i].vec2.x = (1 + src[i].vec2.x) * 0.5 * g_screenwdt;
		dst[i].vec2.y = (1 + src[i].vec2.y) * 0.5 * g_screenhgt;
	}
}


/*
** Renders a quad on screen.
** @param const t_quad the quad's points in clip space.
** @var t_quad pixquad the quad's vectors in screenspace.
*/

extern void	renderquad(const t_quad quad)
{
	t_quad		pixquad;
	union u_v2	p;
	union u_color magenta = 
	{
		.rgb = {
			.r = 255,
			.g = 0,
			.b = 255,
		}
	};

	cliptopix(quad, pixquad);
	for (unsigned int x=0; x<g_screenwdt; x++)
	for (unsigned int y=0; y<g_screenhgt; y++)
	{
		p.vec2.x = (float)x;
		p.vec2.y = (float)y;
		if (quadcontain(p.array, pixquad))
		{
			renderset(x, g_screenhgt - y, magenta);
		}
	}
}
