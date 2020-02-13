/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubefield.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:28:04 by abaur             #+#    #+#             */
/*   Updated: 2020/02/13 13:28:07 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_util.h"

/*
** Finds the first argument of the line and points to it.
** This skips the line identifier and the following spaces.
** @param const char* line The line to skip.
** @return char* A pointer to the character in the source string.
*/

static char		*skip_id(const char *line)
{
	const char *src;

	src = line;
	while (*line && !ft_isspace(*line))
		line++;
	if (!*line)
		throw(-1, "Line has no argument: \n%s", src);
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		throw(-1, "Line has no argument: \n%s", src);
	return ((char*)line);
}

/*
** Computes the first few characters of a string into a single int value
** to make comparison easier.
** Evaluates up to 4 characters, and stops before the first white space.
** @param char* line The line to compute.
** @return The computed identifier.
*/

static t_uint	getidentifier(char *line)
{
	unsigned int	result;
	unsigned int	i;

	if (!line)
		throw(-1, "Fatal: Passed null argument to GetIdentifier.");
	result = 0;
	i = 0;
	while (i < 4 && line[i] && !ft_isspace(line[i]))
	{
		result |= line[i] << (i * 8);
		i++;
	}
	return (result);
}

/*
** Parse a single line to fill the given mapfile object.
** Automatically frees the line.
** Duplicate identifiers are considered an error.
** @param t_cubfile* this	The mapfile object to fill.
** @param char* line	Assumed non null. May be empty.
*/

void			parsefield(char *line, t_cubfile *dst)
{
	unsigned int	id;

	id = getidentifier(line);
	if (id == C && dst->ceilcol.rgba.a == 0)
		dst->ceilcol.rgba = parsecolor(skip_id(line));
	else if (id == F && dst->floorcol.rgba.a == 0)
		dst->floorcol.rgba = parsecolor(skip_id(line));
	else if (id == R && dst->resolution.x == 0 && dst->resolution.y == 0)
		parseresolution(skip_id(line), &dst->resolution.x, &dst->resolution.y);
	else if (id == S && dst->sprite == NULL)
		dst->sprite = parsetexpath(skip_id(line));
	else if (id == NO && dst->north == NULL)
		dst->north = parsetexpath(skip_id(line));
	else if (id == SO && dst->south == NULL)
		dst->south = parsetexpath(skip_id(line));
	else if (id == WE && dst->west == NULL)
		dst->west = parsetexpath(skip_id(line));
	else if (id == EA && dst->east == NULL)
		dst->east = parsetexpath(skip_id(line));
	else if (id != 0)
		throw(-1, "Unexpected identifier: \n%s", line);
	free(line);
}
