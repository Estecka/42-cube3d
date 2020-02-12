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