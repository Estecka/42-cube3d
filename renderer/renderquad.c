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
** Computes the fig-to-UV matrix of a truncated figure.
** Considering context (near plane truncation), assumption is made that the fig
** ure cannot be parallel to the X axis.
** @param const t_seg2 src	The original figure.
** @param const t_seg2 dst	The truncated figure.
** @param const t_mx2a mx	Outputs the corresponding matrix.
*/

static void	truncateuv(const t_seg2 src, const t_seg2 dst, t_mx2a mx)
{
	float uv[2];

	if (src[0].y == src[1].y)
	{
		mx[0][0] = 1;
		mx[1][0] = 0;
		return ;
	}
	mx[0][0] = src[1].y - src[0].y;
	mx[1][0] = src[0].y;
	mx2ainv(mx, mx);
	uv[0] = mx2av1(mx, dst[0].y);
	uv[1] = mx2av1(mx, dst[1].y);
	mx[0][0] = uv[1] - uv[0];
	mx[1][0] = uv[0];
}

/*
** Computes the matrix that transforms from homogeneous clip space to figure sp
** ace.
** @param t_renderenv* this The renderenv whose matrix to initialise.
** @param union u_v3* quad	The points of the figure in homogemeous clip sace.
*/

static void	getfigmx(t_renderenv *this, union u_v3 fig[2])
{
	t_mx3	f2wmx;

	mx3init(f2wmx);
	f2wmx[0][0] = fig[1].vec2.x - fig[0].vec2.x;
	f2wmx[0][1] = fig[1].vec2.y - fig[0].vec2.y;
	f2wmx[1][0] = -f2wmx[0][1];
	f2wmx[1][1] = f2wmx[0][0];
	f2wmx[2][0] = fig[0].vec2.x;
	f2wmx[2][1] = fig[0].vec2.y;
	mx3invaff(f2wmx, this->figspace);
}

/*
** Convert a segment's vertices from view space to cartesian screen space.
** The screen to UV matrix is computed in the process.
** @param t_renderenv* this	The current rendering environnement.
** @param const t_seg2 src The quad's vertices in view space.
*/

static void	viewtoscreen(t_renderenv *this, const t_seg2 src)
{
	union u_v3	p[2];
	int			i;

	p[0] = mx3v2(g_projmx, &src[0]);
	p[1] = mx3v2(g_projmx, &src[1]);
	getfigmx(this, p);
	i = -1;
	while (++i < 2)
	{
		p[i].vec2 = cartesian2d(&p[i].vec3).vec2;
		p[i].vec2.x += 1;
		p[i].vec2.x *= 0.5 * g_screenwdt;
		this->pixvert[i] = p[i].vec2;
	}
}

/*
** Renders a mesh on screen.
** @param const t_mesh*	The mesh in clip space.
*/

extern void	renderquad(const t_mesh *mesh)
{
	t_renderenv	env;
	t_seg2		truncquad;

	env.texture = mesh->texture;
	neartruncate(mesh->vertices, truncquad);
	truncateuv(mesh->vertices, truncquad, env.umx);
	viewtoscreen(&env, truncquad);
	env.linescalar = (env.pixvert[1].y - env.pixvert[0].y)
		/ (env.pixvert[1].x - env.pixvert[0].x);
	env.lineoffset = env.pixvert[0].y - (env.linescalar * env.pixvert[0].x);
	rasterize(&env);
}
