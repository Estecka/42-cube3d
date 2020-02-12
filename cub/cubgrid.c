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
** Parses and validates the first row of a cub map.
** Fills the tiles into a new stringbuilder.
** Sets `mapWidth` on the mapfile accordingly.
** Sets `mapHeight` to 1.
** @param const char* line The first map row from the cub file
** @param t_mapfile* file The file to fill in.
** @return t_strbd* A pointer to a new String Builder
*/

t_strb		*parsegridwidth(const char *line, t_mapfile *file)
{
	const char	*src;
	t_strb		*builder;

	src = line;
	builder = createstrbuilder();
	while (*line)
	{
		if (*line == '1')
		{
			file->mapwdt++;
			strbappend(builder, '1');
		}
		else if (!ft_isspace(*line))
			throw(-1, "Unexpected tile in first row: \n%s", src);
		line++;
	}
	file->maphgt = 1;
	return (builder);
}

/*
** Validates the format of a middle row of a cub map.
** Checks for walls on both sides, and width.
** Does not check for duplicate player.
** @param const char* line the string to parse
** @return short
** 	throw Invalid row
** 	0 Valid middle row
** 	1 Valid final row
*/

short		validategridrow(const char *line, t_mapfile *file)
{
	const char		*src;
	short			islastrow;
	char			lasttile;
	unsigned int	width;

	islastrow = 1;
	lasttile = 0;
	src = line;
	width = 0;
	if (*line != '1')
		throw(-1, "Missing western wall:\n%s", src);
	while (*line)
	{
		if (ft_strcontain("012NEWS", *line))
		{
			islastrow &= ('1' == (lasttile = *line));
			width++;
		}
		else if (!ft_isspace(*line))
			throw(-1, "Invalide tile \"%c\" in:\n%s", *line, src);
		line++;
	}
	if (lasttile != '1' || width != file->mapwdt)
		throw(-1, "Missing eastern wall, or unexpected width :\n%s", src);
	return (islastrow);
}

/*
** Parses a middle row of a cube map. The format is assumed valid.
** Fills the tiles into a stringbuilder.
** @param const char* line The string to parse.
** @param t_mapfile* file The mapfile to fill.
** @param t_strb* builder The stringbuilder to use while building the grid.
** @return int The amount of players found on this row.
*/

int			parsegridrow(const char *line, t_mapfile *file, t_strb *builder)
{
	int count;

	(void)file;
	count = 0;
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			strbappend(builder, *line);
			if (ft_strcontain("NEWS", *line))
				count++;
		}
		line++;
	}
	return (count);
}
