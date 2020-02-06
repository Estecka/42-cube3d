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
** Convert a quad's vertices from view space to screen space.
** @param const t_quad src The quad's vertices in view space.
** @param t_quad dst Outputs the points pixel coordinates.
*/

static void	viewtopix(const t_quad src, t_quad dst)
{
	union u_v4 p;

	for (int i=0; i<4; i++)
	{
		p = mx4v3(g_projmx, &src[i]);
		p.vec3 = cartesian(&p.vec4).vec3;
		p.vec3.x = (1 + p.vec3.x) * 0.5 * g_screenwdt;
		p.vec3.y = (1 + p.vec3.y) * 0.5 * g_screenhgt;
		dst[i] = p.vec3;
	}
}


/*
** Renders a quad on screen.
** @param const t_quad the quad's points in clip space.
** @var t_quad pixquad the quad's vectors in screenspace.
*/

extern void	renderquad(const t_quad quad)
{
	t_renderenv		env;
	union u_v3	p;
	union u_color color = 
	{
		.rgb = {
			.r = 0,
			.g = 0,
			.b = 0,
		}
	};

	viewtopix(quad, env.pixvert);
	env.normale = normale(env.pixvert).vec3;
	env.plane = planeeq(&env.normale, env.pixvert).vec4;
	for (unsigned int x=0; x<g_screenwdt; x++)
	for (unsigned int y=0; y<g_screenhgt; y++)
	{
		float z;

		p.vec2.x = (float)x;
		p.vec2.y = (float)y;
		if (quadcontain(&p.vec2, env.pixvert))
		{
			z = planez(&env.plane, &p.vec3);
			if (zbuffcmp(x, y, z))
			{
				zbuffset(x, y, z);
				color.rgba.b = (int)(128 * (z +1));
				renderset(x, g_screenhgt - y, color);
			}
		}
	}
}
