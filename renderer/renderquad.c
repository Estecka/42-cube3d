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
	subvec3(&this->figoffset, &p[1].vec3, &(t_v3){ 0 });
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
** @param const t_v3* p The pixel's coordinates in cartesian screen space.
** @return bool
** 	true  The pixels lands inside the unit square.
**  false the pixel lands outside the unit square, and the uv were wrapped.
*/

static short	getuv(t_renderenv *this, t_v2 *uv, const t_v3 *pixel)
{
	short r;
	t_v3 p;

	p = *pixel;
	p.x /= 0.5 * g_screenwdt;
	p.y /= 0.5 * g_screenhgt;
	p.x -= 1;
	p.y -= 1;
	p = homegeneous(&p, g_projmx).vec3;
	addvec3(&p, &p, &this->figoffset);
	*uv = mx3v3(this->figspace, &p).vec2;
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
	bbquad(&env.bbox, env.pixvert);
	bbclip(&env.bbox, &env.bbox, &g_screenbb);
	if (!bbisvalid2d(&env.bbox))
		return;
	env.normale = normale(env.pixvert).vec3;
	env.plane = planeeq(&env.normale, env.pixvert).vec4;

	t_mx3			mx;
	mx3cpy(env.figspace, mx);
	mx3inv(mx, env.figspace);

	union u_color color = 
	{
		.rgba = {
			.a = 0,
		}
	};
	struct s_v3	p;
	for (p.x=env.bbox.min.x; p.x<env.bbox.max.x; p.x++)
	for (p.y=env.bbox.min.y; p.y<env.bbox.max.y; p.y++)
	{
		if (quadcontain((t_v2*)&p, env.pixvert))
		{
			p.z = planez(&env.plane, &p);
			if (zbuffcmp(p.x, p.y, p.z))
			{
				t_v2	uv;
				zbuffset(p.x, p.y, p.z);
				color.rgba.b = 255 - (int)(128 * (p.z +1));
				getuv(&env, &uv, &p);
				color.rgba.r = (int)(255 * uv.y);
				color.rgba.g = (int)(255 * uv.x);
				renderset(p.x, g_screenhgt - p.y, color);
			}
		}
	}
}
