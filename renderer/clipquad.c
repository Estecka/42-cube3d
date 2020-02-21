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
	return (seg[0].x < seg[1].x);
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
	struct s_v2	horto[2];
	t_bbox2		bbox;
	int			i;

	i = -1;
	while (++i < 2)
	{
		horto[i].y = seg[i].y;
		horto[i].x = seg[i].x * g_frustrum.max.y / seg[i].y;
	}
	if (!isfrontfaced(horto))
		return (0);
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
	if (!frustrumculling(quad))
		return (0);
	return (1);
}
