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

t_dynarray g_renderqueue;

void		renderqueueinit(void)
{
	if (!dyninit(&g_renderqueue, sizeof(void*), 32))
		throw(errno, "[FATAL] Renderqueue initialization failed: %d", errno);
}

void		renderqueueclear(void)
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
** Stages a quad to be renderered.
** Performs early culling on the quad, and roughly sorts the queue from closest
**  to farthest.
** @param const t_quad quad	The quad to queue in view space.
** 	The reference should not be modified or deallocated until after the queue w
** 	as rendered.
*/

extern void	renderqueuestage(const t_quad quad)
{
	t_quad	*queue;
	size_t	i;

	if (!clipquad(quad))
		return ;
	queue = (t_quad*)g_renderqueue.content;
	i = 0;
	while (i < g_renderqueue.length)
	{
		if (queue[i][1].z > quad[1].z)
			break ;
		i++;
	}
	if (!dyninsert(&g_renderqueue, i, quad))
		throw(errno, "[FATAL] Renderqueue insertion failed: %d", errno);
}