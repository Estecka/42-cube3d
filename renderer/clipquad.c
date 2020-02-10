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

static short    isfrontfaced(const t_quad quad)
{
    struct s_v3 n;

    n = normale(quad).vec3;
	return (dotprod3(&n, &quad[1]) < 0);
}

/*
** Checks whether the quad is visible to the camera.
** This might return false positives.
** @param t_quad The quad to check.
** @return bool
**  true  The quad is most likely visible.
**  false The quad is definitely not visible.
*/

extern short    clipquad(const t_quad quad)
{
	if (!isfrontfaced(quad))
		return (0);
	return (1);
}