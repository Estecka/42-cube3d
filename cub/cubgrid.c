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
		throw(errno, "[FATAL] dynappend failed.");
	this->mapsize.y++;
	if (width > this->mapsize.x)
		this->mapsize.x = width;
}
