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
** Convert a quad's vertices from view space to cartesian screen space.
** In the process, the matrix from UV to homegeneous screen is computed.
** @param t_renderenv* this	The current rendering environnement.
** @param const t_quad src The quad's vertices in view space.
*/

static void	viewtoscreen(t_renderenv *this, const t_quad src)
{
	union u_v4 p[4];

	for (int i=0; i<4; i++)
	{
		p[i] = mx4v3(g_projmx, &src[i]);
		p[i].vec4.x *= 0.5 * g_screenwdt;
		p[i].vec4.y *= 0.5 * g_screenhgt;
	}
	this->figspace[0][0] = p[2].vec4.x - p[1].vec4.x;
	this->figspace[0][1] = p[2].vec4.y - p[1].vec4.y;
	this->figspace[0][2] = p[2].vec4.z - p[1].vec4.z;
	this->figspace[1][0] = p[0].vec4.x - p[1].vec4.x;
	this->figspace[1][1] = p[0].vec4.y - p[1].vec4.y;
	this->figspace[1][2] = p[0].vec4.z - p[1].vec4.z;
	this->figspace[2][0] = g_cliporigin.vec4.x - p[1].vec4.x;
	this->figspace[2][1] = g_cliporigin.vec4.y - p[1].vec4.y;
	this->figspace[2][2] = g_cliporigin.vec4.z - p[1].vec4.z;
	for (int i=0; i<4; i++)
	{
		p[i].vec3 = cartesian(&p[i].vec4).vec3;
		p[i].vec3.x += 0.5 * g_screenwdt;
		p[i].vec3.y += 0.5 * g_screenhgt;
		this->pixvert[i] = p[i].vec3;
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

	viewtoscreen(&env, quad);
	env.normale = normale(env.pixvert).vec3;
	env.plane = planeeq(&env.normale, env.pixvert).vec4;

	t_mx3			mx;
	mx3cpy(env.figspace, mx);
	mx3inv(mx, env.figspace);

	union u_v3	p;
	union u_color color = 
	{
		.rgb = {
			.r = 0,
			.g = 0,
			.b = 0,
		}
	};
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
