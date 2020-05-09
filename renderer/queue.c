/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:28:51 by abaur             #+#    #+#             */
/*   Updated: 2020/02/12 13:28:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

t_dynarray	g_renderqueue;
t_dynarray	g_bboardqueue;

void		renderqueueinit(void)
{
	if (!dyninit(&g_renderqueue, sizeof(void*), 32)
		&& !spyregpp(g_renderqueue.content))
		throw(errno, "[FATAL] Renderqueue initialization failed.");
	if (!dyninit(&g_bboardqueue, sizeof(t_v2), 32)
		&& !spyregpp(g_bboardqueue.content))
		throw(errno, "[FATAL] Bboardqueue initialization failed.");
}

static void	renderqueueclear(void)
{
	size_t	i;
	void	**queue;
	t_v2	*bbqueue;

	queue = (void**)g_renderqueue.content;
	i = 0;
	while (i < g_renderqueue.capacity)
	{
		queue[i] = NULL;
		i++;
	}
	g_renderqueue.length = 0;
	bbqueue = (t_v2*)g_bboardqueue.content;
	i = 0;
	while (i < g_bboardqueue.capacity)
	{
		bbqueue[i] = (t_v2){ 0 };
		i++;
	}
	g_bboardqueue.length = 0;
}

/*
** Renders all quads in the queue, then clears it.
** This DOES NOT print the render texture on-screen.
*/

extern void	renderqueueflush(void *spritetexture)
{
	size_t	i;
	t_mesh	**queue;
	t_v2	*bbqueue;

	queue = (t_mesh**)g_renderqueue.content;
	i = -1;
	while (++i < g_renderqueue.length)
	{
		renderquad(queue[i]);
	}
	bbqueue = (t_v2*)g_bboardqueue.content;
	i = -1;
	while (++i < g_bboardqueue.length)
	{
		renderbboard(&bbqueue[i], spritetexture);
	}
	renderqueueclear();
}

/*
** Stages a quad to be renderered.
** Performs early culling on the quad, and roughly sorts the queue from closest
**  to farthest.
** @param const t_mesh* quad	The mesh to enqueue in view space.
** 	The reference should not be modified or deallocated until after the queue w
** 	as rendered.
*/

extern void	renderqueuestage(const t_mesh *mesh)
{
	t_mesh	**queue;
	size_t	i;

	if (!clipquad(mesh->vertices))
		return ;
	queue = (t_mesh**)g_renderqueue.content;
	i = 0;
	while (i < g_renderqueue.length)
	{
		if (queue[i]->vertices[1].y < mesh->vertices[1].y)
			break ;
		i++;
	}
	if (!spyunreg(g_renderqueue.content) 
		&& !dyninsert(&g_renderqueue, i, &mesh)
		&& !spyregpp(g_renderqueue.content))
		throw(errno, "[FATAL] Renderqueue insertion failed.");
}

/*
** Stages a billboard to be renderered.
** Performs early culling, and roughly sorts the queue from closest to farthest
** @param const t_v2* pos	The position of the billboard in view space.
*/

extern void	bboardqueuestage(const t_v2 pos)
{
	t_seg2	quad;
	t_v2	*queue;
	size_t	i;

	quad[0] = (t_v2){pos.x - 0.5f, pos.y};
	quad[1] = (t_v2){pos.x + 0.5f, pos.y};
	if (!clipquad(quad))
		return ;
	queue = (t_v2*)g_bboardqueue.content;
	i = 0;
	while (i < g_bboardqueue.length)
	{
		if (queue[i].y < pos.y)
			break ;
		i++;
	}
	if (!spyunreg(g_bboardqueue.content)
		&& !dyninsert(&g_bboardqueue, i, &pos)
		&& !spyregpp(g_bboardqueue.content))
		throw(errno, "[FATAL] Bboardqueue insertion failed.");
}
