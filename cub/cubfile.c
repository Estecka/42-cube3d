/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:22:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub_util.h"

/*
** Parse the one-liner fields of the file.
** @param t_cubfile* this	The cubfile to fill.
** @param int fd	The file descriptor to read from.
** @return char[]	The first line of the map.
*/

static char		*parsefields(t_cubfile *this, int fd)
{
	char	*line;
	short	gnl;

	while (0 < (gnl = get_next_line(fd, &line)) && line[0] != '1')
		parsefield(line, this);
	if (gnl < 0)
		throw(errno, "[FATAL] GNL error.");
	if (gnl == 0)
		throw(-1, "No map found in the file");
	if (this->resolution.x == 0 || this->resolution.y == 0
		|| this->north == NULL || this->south == NULL || this->east == NULL
		|| this->west == NULL || this->sprite == NULL
		|| this->floorcol.rgba.a == 0 || this->ceilcol.rgba.a == 0)
		throw(-1, "Missing cub file fields.");
	return (line);
}

/*
** Parse the map section of a cub file.
** The map's layout is not validated, only the tile palette is verified.
** The very first row is assumed to be already extarcted from the file.
** Checks that the file ends with the grid, empty lines are tolerated.
** @param t_cubfile* this	The object to fill.
** @param int fd	The file descriptor to read from.
** @param char[] firstrow	The first row of the map.
** 	Has to be passed explicitely, because there's no fucking way to detect the
** 	 map without taking off the first row beforehand.
*/

static void		parsemap(t_cubfile *this, int fd, char *firstrow)
{
	t_dynarray	array;
	char		*line;
	short		gnl;

	if (!dyninit(&array, sizeof(char*), 16))
		throw(errno, "[FATAL] Dyinit failed.");
	parsegridrow(this, firstrow, &array);
	while (0 <= (gnl = get_next_line(fd, &line)))
	{
		if (line[0] != '\0')
		{
			parsegridrow(this, line, &array);
			line = NULL;
		}
		else
			break ;
	}
	if (line)
		free(line);
	if (gnl < 0)
		throw(errno, "[FATAL] GNL error.");
	this->tiles = (char**)array.content;
	if (this->mapsize.x == 0 || this->mapsize.y == 0)
		throw(-1, "Map is empty.");
}

/*
** Parses a cub file into a mapfile object.
** @param t_cubfile* this	The mapfile object to fill.
** @param int fd	The file descriptor to read from.
*/

extern void		parsefile(t_cubfile *this, int fd)
{
	char	*mapfirstrow;
	short	gnl;
	char	c;

	mapfirstrow = parsefields(this, fd);
	parsemap(this, fd, mapfirstrow);
	while (0 < (gnl = get_next_char(fd, &c)))
		if (!ft_isspace(c) && c != '\0' && c != (char)EOF)
			throw(-1, "Garbage character after the map: %c", c);
	if (gnl < 0)
		throw(errno, "[FATAL] GNL error.");
}
