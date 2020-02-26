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
** Computes the matrix that transforms from screenspace to figure space.
** @param t_renderenv* this The renderenv whose matrix to initialise.
** @param union u_v4* quad The pooints of the figure.
*/

static void	getfigmx(t_renderenv *this)
{
	this->figspace[0][0] = 1 / (this->pixvert[1].x - this->pixvert[0].x);
	this->figspace[1][0] = -this->pixvert[0].x * this->figspace[0][0];
}

/*
** Convert a segment's vertices from view space to cartesian screen space.
** The screen to UV matrix is computed in the process.
** @param t_renderenv* this	The current rendering environnement.
** @param const t_seg2 src The quad's vertices in view space.
*/

static void	viewtoscreen(t_renderenv *this, const t_seg2 src)
{
	t_seg2	p;
	int		i;
	float	perspective;

	i = -1;
	while (++i < 2)
	{
		p[i].y = src[i].y;
		perspective = g_frustrum.max.y / p[i].y;
		p[i].x = perspective * src[i].x;
		p[i] = mx3v2(g_projmx, &p[i]).vec2;
		p[i].x += 1;
		p[i].x *= 0.5 * g_screenwdt;
		this->pixvert[i] = p[i];
	}
	getfigmx(this);
}

/*
** Renders a quad on screen.
** @param const t_seg2 the quad's points in clip space.
** @var t_seg2 pixquad the quad's vectors in screenspace.
*/

extern void __attribute__((hot))
			renderquad(const t_seg2 quad)
{
	t_renderenv	env;
	t_seg2		truncquad;

	neartruncate(quad, truncquad);
	if (g_log)
	{
		printf("Truncated fig:\n");
		printf("%f %f \t %f %f\n", quad[0].x,      quad[0].y,      quad[1].x,      quad[1].y     );
		printf("%f %f \t %f %f\n", truncquad[0].x, truncquad[0].y, truncquad[1].x, truncquad[1].y);
		// printf("Matrix:\n[%f %f]\n\n", env.umx[0][0], env.umx[1][0]);
	}
	truncateuv(quad, truncquad, env.umx);
	viewtoscreen(&env, truncquad);
	env.linescalar = (env.pixvert[1].y - env.pixvert[0].y)
		/ (env.pixvert[1].x - env.pixvert[0].x);
	env.lineoffset = env.pixvert[0].y - (env.linescalar * env.pixvert[0].x);
	rasterize(&env);
}
