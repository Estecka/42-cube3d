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
	short	r;
	t_v3	p;

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
** Prints on screen a fully computed rendering environnement.
** @param t_renderenv* this
*/

static void		rasterizep(t_renderenv *this, t_v3 *p)
{
	union u_color	color;
	struct s_v2		uv;

	color.rgba.a = 0;
	p->z = planez(&this->plane, p);
	if (getuv(this, &uv, p) && zbuffcmp(p->x, p->y, p->z))
	{
		zbuffset(p->x, p->y, p->z);
		color.rgba.b = 255 - (int)(128 * (p->z + 1));
		color.rgba.r = (int)(255 * uv.y);
		color.rgba.g = (int)(255 * uv.x);
		renderset(p->x, g_screenhgt - p->y, color);
	}
}

void			rasterize(t_renderenv *this)
{
	struct s_v3	p;

	p.x = this->bbox.min.x;
	while (p.x < this->bbox.max.x)
	{
		p.y = this->bbox.min.y;
		while (p.y < this->bbox.max.y)
		{
			rasterizep(this, &p);
			p.y++;
		}
		p.x++;
	}
}
