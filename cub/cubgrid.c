/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubgrid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:23:21 by abaur             #+#    #+#             */
/*   Updated: 2020/01/23 14:48:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub_util.h"

/*
** Allocates a two dimensional array in a single memory space.
** The array's elements are accessible via `array[x][y]`
** @param unsigned int width  The number of columns in the grid. (x)
** @param unsigned int height The number of rows in the grid. (y)
** @param char value The default vaalue to initialize the array with.
** @return char*const* A pointer to the grid, or NULL if allocation failed.
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

/*
** Parses a row of the map.
** Only invalid characters are being checked.
** @param t_cubfile* this
** @param char[] line	The line to parse.
** 	The reference is stored away, and should not be modified or freed afterward.
** @param t_dynarray* array	The array to where to store the lines.
*/

void		parsegridrow(t_cubfile *this, char *line, t_dynarray *array)
{
	char		*src;
	signed int	width;

	src = line;
	width = 0;
	while (*line)
	{
		if (ft_strcontain("012NEWS", *line))
		{
			src[width] = *line;
			width++;
		}
		else if (!ft_isspace(*line))
			throw(-1, "Invalid character in map: %c", *line);
		line++;
	}
	src[width] = '\0';
	if (!dynappend(array, &src))
		throw(errno, "[FATAL] dynappend failed: %d", errno);
	this->mapsize.y++;
	if (width > this->mapsize.x)
		this->mapsize.x = width;
}
