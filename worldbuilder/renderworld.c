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

static void	stagesprites(void)
{
	size_t	i;
	t_v2	p;

	i = -1;
	while (++i < g_world.spritecount)
	{
		p = mx3v2(g_player.w2lmx, &g_world.sprites[i]).vec2;
		bboardqueuestage(p);
	}
}

static void	stagewalls(void)
{
	size_t			i;
	t_staticmesh	*wall;

	i = -1;
	while (++i < g_world.wallcount)
	{
		wall = g_world.walls + i;
		wall->renderinfo.vertices[0] =
			mx3v2(g_player.w2lmx, &wall->vertices[0]).vec2;
		wall->renderinfo.vertices[1] =
			mx3v2(g_player.w2lmx, &wall->vertices[1]).vec2;
		renderqueuestage(&wall->renderinfo);
	}
}

extern void	renderworld(void)
{
	retransform(&g_player);
	stagesprites();
	stagewalls();
	renderqueueflush(g_world.spritetexture);
	extrude();
}
