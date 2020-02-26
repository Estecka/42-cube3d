/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipquad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:04:21 by abaur             #+#    #+#             */
/*   Updated: 2020/02/10 14:04:22 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Checks whether the segment is backfaced.
** @param t_seg2 seg	The segment to check in hotorrmal pace.
** @return bool
**  false The segment is either backfaced or sidefaced.
**  true  The segment is frontfaced.
*/

static short	isfrontfaced(const t_seg2 seg)
{
	t_v2	n;

	n = normale2d(seg).vec2;
	return (dotprod2(&n, &seg[0]) > 0);
}

/*
** Checks whether the segment is visible to the frustrum.
** This is a fast approximation, and might yield false positives.
** @param t_seg2 seg	The segment to check.
** @return bool
** 	true  The segment is most likely visible.
** 	false The segment is definitely invisible.
*/

static short	frustrumculling(const t_seg2 seg)
{
	t_seg2	trunc;
	t_seg2	horto;
	t_bbox2		bbox;
	int			i;

	if ((seg[0].y > g_frustrum.max.y) ^ (seg[1].y > g_frustrum.max.y))
		neartruncate(seg, trunc);
	else
	{
		trunc[0] = seg[0];
		trunc[1] = seg[1];
	}
	i = -1;
	while (++i < 2)
	{
		horto[i].y = trunc[i].y;
		horto[i].x = trunc[i].x * g_frustrum.max.y / trunc[i].y;
	}
	bb2seg(&bbox, horto);
	return (bb2inter(&bbox, &g_frustrum));
}

/*
** Checks whether the quad is visible to the camera.
** This might yield false positives.
** @param t_seg2 The quad to check.
** @return bool
**  true  The quad is most likely visible.
**  false The quad is definitely not visible.
*/

extern short	clipquad(const t_seg2 quad)
{
	if (!isfrontfaced(quad))
		return (0);
	if (!frustrumculling(quad))
		return (0);
	return (1);
}
