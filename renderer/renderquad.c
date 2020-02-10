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
** Computes the matrix that transforms a point from figure space to world space
** @param t_renderenv* this The renderenv whose matrix to initialise.
** @param union u_v4* quad The pooints of the figure.
*/

static void	getfigmx(t_renderenv *this, union u_v4 *quad)
{
	this->figspace[0][0] = quad[2].vec3.x - quad[1].vec3.x;
	this->figspace[0][1] = quad[2].vec3.y - quad[1].vec3.y;
	this->figspace[0][2] = quad[2].vec3.z - quad[1].vec3.z;
	this->figspace[1][0] = quad[0].vec3.x - quad[1].vec3.x;
	this->figspace[1][1] = quad[0].vec3.y - quad[1].vec3.y;
	this->figspace[1][2] = quad[0].vec3.z - quad[1].vec3.z;
	this->figspace[2][0] = g_cliporigin.vec4.x - quad[1].vec3.x;
	this->figspace[2][1] = g_cliporigin.vec4.y - quad[1].vec3.y;
	this->figspace[2][2] = g_cliporigin.vec4.z - quad[1].vec3.z;
	subvec3(&this->figoffset, &quad[1].vec3, &(t_v3){ 0 });
}

/*
** Convert a quad's vertices from view space to cartesian screen space.
** In the process, the matrix from UV to homegeneous screen is computed.
** @param t_renderenv* this	The current rendering environnement.
** @param const t_quad src The quad's vertices in view space.
*/

static void	viewtoscreen(t_renderenv *this, const t_quad src)
{
	union u_v4	p[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		p[i] = mx4v3(g_projmx, &src[i]);
	}
	getfigmx(this, p);
	i = -1;
	while (++i < 4)
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
** Renders a quad on screen.
** @param const t_quad the quad's points in clip space.
** @var t_quad pixquad the quad's vectors in screenspace.
*/

extern void	renderquad(const t_quad quad)
{
	t_renderenv		env;
	t_mx3			tmpmx;
	t_v3			normal;

	viewtoscreen(&env, quad);
	bbquad(&env.bbox, env.pixvert);
	bbclip(&env.bbox, &env.bbox, &g_screenbb);
	if (!bbisvalid2d(&env.bbox))
		return ;
	normal = normale(env.pixvert).vec3;
	env.plane = planeeq(&normal, env.pixvert).vec4;
	mx3cpy(env.figspace, tmpmx);
	mx3inv(tmpmx, env.figspace);
	rasterize(&env);
}
