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

void		renderqueueinit(void)
{
	if (!dyninit(&g_renderqueue, sizeof(void*), 32))
		throw(errno, "[FATAL] Renderqueue initialization failed: %d", errno);
}

static void		renderqueueclear(void)
{
	size_t	i;
	void	**queue;

	queue = (void**)g_renderqueue.content;
	i = 0;
	while (i < g_renderqueue.capacity)
	{
		queue[i] = NULL;
		i++;
	}
	g_renderqueue.length = 0;
}

/*
** Renders all quads in the queue, then clears it.
** This DOES NOT print the render texture on-screen.
*/

extern void	renderqueueflush(void)
{
	size_t	i;
	t_v2	**queue;

	queue = (t_v2**)g_renderqueue.content;
	i = -1;
	while (++i < g_renderqueue.length)
	{
		renderquad(queue[i]);
	}
	renderqueueclear();
	extrude();
}

/*
** Stages a quad to be renderered.
** Performs early culling on the quad, and roughly sorts the queue from closest
**  to farthest.
** @param const t_seg2 quad	The quad to queue in view space.
** 	The reference should not be modified or deallocated until after the queue w
** 	as rendered.
*/

extern void __attribute__((hot))
			renderqueuestage(const t_seg2 quad)
{
	t_v2	**queue;
	size_t	i;

	if (!clipquad(quad))
		return ;
	queue = (t_v2**)g_renderqueue.content;
	i = 0;
	while (i < g_renderqueue.length)
	{
		if (queue[i][1].y < quad[1].y)
			break ;
		i++;
	}
	if (!dyninsert(&g_renderqueue, i, &quad))
		throw(errno, "[FATAL] Renderqueue insertion failed: %d", errno);
}
