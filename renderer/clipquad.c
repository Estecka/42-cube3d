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
** Checks whether the quad is backfaced.
** @param t_quad The quad to check.
** @return bool
**  false The quad is either backfaced or sidefaced.
**  true  The quad is frontfaced.
*/

static short	isfrontfaced(const t_quad quad)
{
	struct s_v3	n;

	n = normale(quad).vec3;
	return (dotprod3(&n, &quad[1]) < 0);
}

/*
** Checks whether the quad interects with the frustrum.
** This is a fast approximation, and might yield false positives.
** @param t_quad quad The quad to check.
** @return bool
** 	true  The quad likely intersects the frustrum.
** 	false The quad definitely is outside the frustrum.
*/

static short	frustrumculling(const t_quad quad)
{
	struct s_v3	horto[4];
	t_bbox		bbox;
	int			i;

	i = -1;
	while (++i < 4)
	{
		horto[i].z = quad[i].z;
		scalevec2((t_v2*)&horto[i], (t_v2*)&quad[i],
			g_frustrum.max.z / quad[i].z);
	}
	bbquad(&bbox, horto);
	return (bbinter(&bbox, &g_frustrum));
}

/*
** Checks whether the quad is visible to the camera.
** This might yield false positives.
** @param t_quad The quad to check.
** @return bool
**  true  The quad is most likely visible.
**  false The quad is definitely not visible.
*/

extern short	clipquad(const t_quad quad)
{
	if (!isfrontfaced(quad))
		return (0);
	if (!frustrumculling(quad))
		return (0);
	return (1);
}
