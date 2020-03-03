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

const t_seg2	g_spritemesh = {
	{-0.5, 0},
	{+0.5, 0},
};

static void		renderbillboards(void)
{
	size_t			i;
	t_mx3			bboardmx;
	t_billboardmesh	*mesh;

	mx3cpy(g_player.l2wmx, bboardmx);
	i = -1;
	while (++i < g_world.spritecount)
	{
		mesh = g_world.sprites + i;
		mx3pos(bboardmx, &mesh->position);
		mesh->renderinfo.vertices[0] = mx3v2(bboardmx, &g_spritemesh[0]).vec2;
		mesh->renderinfo.vertices[1] = mx3v2(bboardmx, &g_spritemesh[1]).vec2;
		mesh->renderinfo.vertices[0] = mx3v2(g_player.w2lmx, &mesh->renderinfo.vertices[0]).vec2;
		mesh->renderinfo.vertices[1] = mx3v2(g_player.w2lmx, &mesh->renderinfo.vertices[1]).vec2;
		renderqueuestage(mesh->renderinfo.vertices);
	}
	renderqueueflush();
}

/*
** @param t_transform* camera	The position of the camera in the world.
*/

extern void		renderworld(void)
{
	size_t			i;
	t_staticmesh	*wall;

	retransform(&g_player);
	i = -1;
	while (++i < g_world.wallcount)
	{
		wall = g_world.walls + i;
		wall->renderinfo.vertices[0] = mx3v2(g_player.w2lmx, &wall->vertices[0]).vec2;
		wall->renderinfo.vertices[1] = mx3v2(g_player.w2lmx, &wall->vertices[1]).vec2;
		renderqueuestage(wall->renderinfo.vertices);
	}
	zbuffclear();
	renderqueueflush();
	renderbillboards();
}
