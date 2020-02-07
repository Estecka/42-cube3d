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
	this->figoffset = subvec3(&p[1].vec3, &(t_v3){0, 0, 0 }).vec3;
	for (int i=0; i<4; i++)
	{
		p[i].vec3 = cartesian(&p[i].vec4).vec3;
		p[i].vec3.x += 1;
		p[i].vec3.y += 1;
		p[i].vec4.x *= 0.5 * g_screenwdt;
		p[i].vec4.y *= 0.5 * g_screenhgt;
		this->pixvert[i] = p[i].vec3;
	}
}

/*
** Computes the pixels position in UV space.
** @param t_renderenv* this
** @param t_v2* uv Outputs the UV, wrapped around the [0; 1] range.
** @param t_v2* p The pixel's coordinates in cartesian screen space.
** 	The pixel coordinates are directly worked onto for optimization purpose.
** @return bool
** 	true  The pixels lands inside the unit square.
**  false the pixel lands outside the unit square, and the uv were wrapped.
*/

static short	getuv(t_renderenv *this, t_v2 *uv, t_v3 *p)
{
	short r;

	p->x /= 0.5 * g_screenwdt;
	p->y /= 0.5 * g_screenhgt;
	p->x -= 1;
	p->y -= 1;
	*p = homegeneous(p, g_projmx).vec3;
	*p = addvec3(p, &this->figoffset).vec3;
	*uv = mx3v3(this->figspace, p).vec2;
	r = (uv->x <= 1) && (uv->y <= 1) && (uv->x >= 0) && (uv->y >= 0);
	return (r);
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
		.rgba = {
			.a = 0,
		}
	};
	for (unsigned int x=0; x<g_screenwdt; x++)
	for (unsigned int y=0; y<g_screenhgt; y++)
	{
		p.vec2.x = (float)x;
		p.vec2.y = (float)y;
		if (quadcontain(&p.vec2, env.pixvert))
		{
			p.vec3.z = planez(&env.plane, &p.vec3);
			if (zbuffcmp(x, y, p.vec3.z))
			{
				t_v2	uv;
				zbuffset(x, y, p.vec3.z);
				color.rgba.b = 255 - (int)(128 * (p.vec3.z +1));
				getuv(&env, &uv, &p.vec3);
				color.rgba.r = (int)(255 * uv.y);
				color.rgba.g = (int)(255 * uv.x);
				renderset(x, g_screenhgt - y, color);
			}
		}
	}
}
