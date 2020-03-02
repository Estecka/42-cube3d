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
** Computes a pixel's position in UV space.
** @param t_renderenv* this
** @param t_v2* uv Outputs the UV.
** @param const t_v3* p The pixel's coordinates in cartesian screen space.
** @return bool
** 	true  The pixel lands inside the unit square.
**  false the pixel lands outside the unit square.
*/

static short	getuv(t_renderenv *this, t_v2 *uv, const t_v3 *pixel)
{
	t_v3	p;

	p = *pixel;
	p.x /= 0.5 * g_screenwdt;
	p.y /= 0.5 * g_screenhgt;
	p.x -= 1;
	p.y -= 1;
	p = homegeneous(&p, g_projmx).vec3;
	addvec3(&p, &p, &this->figoffset);
	*uv = mx3v3(this->figspace, &p).vec2;
	return (uv->x >= 0 && uv->x <= 1
		&& uv->y >= 0 && uv->y <= 1);
}

/*
** Prints on screen a fully computed rendering environnement.
** @param t_renderenv* this
*/

static void __attribute__((hot))
				rasterizep(t_renderenv *this, unsigned int x, unsigned int y)
{
	union u_color	color;
	struct s_v3		p;
	struct s_v2		uv;

	color.rgba.a = 0;
	p.x = (float)x;
	p.y = (float)y;
	p.z = planez(&this->plane, &p);
	if (zbuffcmp(x, y, p.z) && getuv(this, &uv, &p))
	{
		zbuffset(x, y, p.z);
		color.rgba.b = 255 - (int)(128 * (p.z + 1));
		color.rgba.r = (int)(255 * uv.y);
		color.rgba.g = (int)(255 * uv.x);
		renderset(x, g_screenhgt - 1 - y, color);
	}
}

void __attribute__((hot))
			rasterize(t_renderenv *this)
{
	unsigned int	x;
	unsigned int	y;

	y = (int)this->bbox.min.y;
	while (y < this->bbox.max.y)
	{
		x = (int)this->bbox.min.x;
		while (x < this->bbox.max.x)
		{
			rasterizep(this, x, y);
			x++;
		}
		y++;
	}
}
