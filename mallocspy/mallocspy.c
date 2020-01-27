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

#include "mallocspy.h"

extern void	*spymalloc(size_t size)
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

extern void	spyfree(void *ptr)
{
	if (!ptr)
		return ;
	if (spyunreg(ptr))
		free(ptr);
	else if (SPYVERBOSE && SPYBRAVE)
	{
		ft_printf("Attempting to free the pointer anyway.\n");
		free(ptr);
	}
	else if (SPYVERBOSE)
		ft_printf("The pointer was not freed.\n");
}
