/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:23:21 by abaur             #+#    #+#             */
/*   Updated: 2020/01/20 11:22:50 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub.h"

/*
** Allocates a two dimensional array in a single memory space.
** The array's elements are accessible via `array[x][y]`
** @param unsigned int width  The number of columns in the grid. (x)
** @param unsigned int height The number of rows in the grid. (y)
** @param char value The default vaalue to initialize the array with.
** @return A pointer to the grid, or NULL if allocation failed.
*/

char*const	*gridmalloc(unsigned int width, unsigned int height, char value)
{
	char			**result;
	char			*values;
	unsigned int	i;

	if (width == 0 || height == 0)
		return (NULL);
	result = malloc(
		(sizeof(void*) * width)
		+ (sizeof(char) * height * width));
	if (!result)
		return (NULL);
	values = (char*)(result + width);
	i = 0;
	while (i < (width * height))
		values[i++] = value;
	i = 0;
	while (i < width)
	{
		result[i] = values + (i * height);
		i++;
	}
	return (result);
}
