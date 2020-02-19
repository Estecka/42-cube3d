/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:58:52 by abaur             #+#    #+#             */
/*   Updated: 2020/02/17 12:58:53 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Allocates a two dimensional array in a single memory space.
** The array's elements are accessible via `array[x][y]`.
** The array's elements are initialized with 0's;
** @param size_t width	The number of columns. (x)
** @param size_t height	The number of rows. (y)
** @param size_t type	The size of the elements' type. (sizeof(type))
** @return void*const*	A pointer to the grid, or NULL if allocation failed.
*/

extern void*const	*malloc2d(size_t width, size_t height, size_t type)
{
	char			**result;
	char			*values;
	size_t			i;

	result = malloc(
		(sizeof(void*) * width)
		+ (type * height * width));
	if (!result)
		return (NULL);
	values = (char*)(result + width);
	i = -1;
	while (++i < (width * height * type))
		values[i] = 0;
	i = -1;
	while (++i < width)
		result[i] = values + (i * height * type);
	return ((void**)result);
}
