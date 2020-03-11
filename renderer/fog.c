/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:23:47 by abaur             #+#    #+#             */
/*   Updated: 2020/03/11 16:23:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Blends a color with the fog.
** @param t_color src	The source color.
** @param float depth	The depth in view space.
*/

t_color			fogblend(t_color src, float depth)
{
	t_color result;
	int		i;

	if (depth > 0)
		depth = 0;
	if (depth < g_frustrum.min.y)
		depth = g_frustrum.min.y;
	depth /= g_frustrum.min.y;
	result.rgba.a = 0;
	i = -1;
	while (++i < 3)
		result.bytes[i] = (depth * (unsigned char)g_fogcolor.bytes[i])
			+ ((1 - depth) * (unsigned char)src.bytes[i]);
	result.rgba.a = 0;
	return (result);
}
