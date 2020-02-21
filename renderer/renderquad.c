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
	t_renderenv		env;

	viewtoscreen(&env, quad);
	env.linescalar = (env.pixvert[1].y - env.pixvert[0].y)
		/ (env.pixvert[1].x - env.pixvert[0].x);
	rasterize(&env);
}
