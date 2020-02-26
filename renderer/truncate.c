/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:04:00 by abaur             #+#    #+#             */
/*   Updated: 2020/02/26 16:04:02 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Truncates a figure intersecting with the near culling plane.
** Assumption is made that the figure won't be completely culled.
** @param const t_seg2 src	The figure's vertices in view space.
** @param t_seg2 dst	Outputs the truncated figure.
*/

void	neartruncate(const t_seg2 src, t_seg2 dst)
{
	t_mx2a	line;
	short	i;

	if (src[0].y > g_frustrum.max.y)
		i = 0;
	else if (src[1].y > g_frustrum.max.y)
		i = 1;
	else
	{
		dst[0] = src[0];
		dst[1] = src[1];
		return ;
	}
	line[0][0] = (src[1].x - src[0].x) / (src[1].y - src[0].y);
	line[1][0] = src[0].x - (line[0][0] * src[0].y);
	dst[i].y = g_frustrum.max.y;
	dst[i].x = (g_frustrum.max.y * line[0][0]) + line[1][0];
	dst[1 - i] = src[1 - i];
}
