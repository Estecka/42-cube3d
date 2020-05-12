/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubgrid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:23:21 by abaur             #+#    #+#             */
/*   Updated: 2020/01/23 14:48:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_util.h"

/*
** Parses a row of the map :
** Validates the tile palette, and updates the map's dimensions.
** The map's layout is not verified.
** @param t_cubfile* this
** @param char[] line	The line to parse.
** 	The reference is stored away, and should not be modified or freed afterward.
** @param t_dynarray* array	The array to where to store the lines.
*/

void		parsegridrow(t_cubfile *this, char *line, t_dynarray *array)
{
	signed int	width;

	spyregpp(&line);
	width = -1;
	while (line[++width] && line[width] != '\n')
		if (!ft_strcontain("012NEWS ", line[width]))
			throw(-1, "[CUB] Invalid character \"%c\"(0x%x) in line: \n%s",
				line[width], line[width], line);
	line[width] = '\0';
	if (!dynappend(array, &line))
		throw(errno, "[FATAL] Dynappend failed in ParseGridRow.");
	this->tiles = (char**)array->content;
	this->mapsize.y++;
	spyunreg(&line);
	spyregpp(&this->tiles[this->mapsize.y - 1]);
	if (width > this->mapsize.x)
		this->mapsize.x = width;
}
