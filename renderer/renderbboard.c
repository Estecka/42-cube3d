/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderbboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:23:51 by abaur             #+#    #+#             */
/*   Updated: 2020/03/03 16:23:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

static void		bbrasterize(t_bbox2 *bbox, t_mx3 uvmx, float depth)
{
	unsigned int	x;
	unsigned int	y;
	t_v2			uv;
	union u_color	color;

	color.rgba.a = 0;
	color.rgba.b = (int)(127.5 * (depth + 1));
	y = bbox->min.y;
	while (y < bbox->max.y)
	{
		x = bbox->min.x;
		while (x < bbox->max.x)
		{
			if (zbuffcmp(x, y, depth))
			{
				zbuffset(x, y, depth);
				uv.x = (x * uvmx[0][0]) + uvmx[2][0];
				uv.y = (y * uvmx[1][1]) + uvmx[2][1];
				color.rgb.r = uv.x * 255;
				color.rgb.g = uv.y * 255;
				renderset(x, y, color);
			}
			x++;
		}
		y++;
	}
}

static void		getbboxvert(t_bbox2 *bbox, const t_v2 *pos)
{
	t_mx2a		vmx;

	getvmx(vmx, pos->y);
	mx2ainv(vmx, vmx);
	bbox->max.y = mx2av1(vmx, 0);
	bbox->min.y = mx2av1(vmx, 1);
}

/*
** @return float	The depth in clip space.
*/

static float	getbboxhori(t_bbox2 *bbox, t_v2 pos)
{
	union u_v3	p;
	int		i;

	pos.x -= 0.5;
	i = -1;
	while (++i < 2)
	{
		pos.x += i * 1;
		p = mx3v2(g_projmx, &pos);
		p.vec2.x /= p.vec3.z;
		p.vec2.x += 1;
		p.vec2.x *= 0.5 * g_screenwdt;
		((t_v2*)bbox)[i].x = p.vec2.x;
	}
	return (p.vec3.y / p.vec3.z);
}

static t_bbox2	g_uvbbox = {
	.min = {0, 0},
	.max = {1, 1},
};

/*
** Renders a billboard on screen.
** @param t_v2 pos	The position of the billboard in view space.
*/

void 			renderbboard(const t_v2 *pos)
{
	t_bbox2 bbox;
	t_mx3	uvmx;
	float	depth;

	getbboxvert(&bbox, pos);
	depth = getbboxhori(&bbox, *pos);
	if (depth < -1 || depth > 1 || !bb2inter(&bbox, &g_screenbb))
		return;
	mx3remap(uvmx, &bbox, &g_uvbbox);
	bb2clip(&bbox, &bbox, &g_screenbb);
	uvmx[1][1] *= -1;
	uvmx[2][1] *= -1;
	uvmx[2][1] += 1;
	bbrasterize(&bbox, uvmx, depth);
}
