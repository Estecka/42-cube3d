/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderworld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:47:50 by abaur             #+#    #+#             */
/*   Updated: 2020/02/18 16:47:51 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worldbuilder_internals.h"
#include "../renderer/renderer.h"

/*
** @param t_transform* camera	The position of the camera in the world.
*/

extern void	renderworld()
{
	size_t			i;
	t_staticmesh	*wall;

	retransform(&g_player);
	i = -1;
	while (++i < g_world.wallcount)
	{
		wall = g_world.walls + i;
		mxquad3(wall->vertices, wall->renderinfo.vertices, g_player.w2lmx);
		renderqueuestage(wall->renderinfo.vertices);
	}
	renderqueueflush();
}
