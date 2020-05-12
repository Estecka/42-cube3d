/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocspy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:55:03 by abaur             #+#    #+#             */
/*   Updated: 2020/01/27 12:06:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mallocspy_internals.h"

#ifndef SPYPROXY

extern void		*spymalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!spyreg(ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

#endif

extern void		spyfree(void **ptr)
{
	if (spyunreg(ptr))
		free(SPYPROXY ? *ptr : ptr);
	else if (ptr && (!SPYPROXY || *ptr) && SPYVERBOSE && SPYBRAVE)
	{
		ft_printf("Attempting to free the pointer anyway.\n");
		free(ptr);
	}
	else if (SPYVERBOSE)
		ft_printf("The pointer was not freed.\n");
}

#if SPYPROXY

extern size_t	spyclean(void)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (++i < g_spycap)
		if (g_spylist[i] && !*g_spylist[i])
		{
			g_spylist[i] = NULL;
			count++;
		}
	return (count);
}

#endif
