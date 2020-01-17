/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/17 12:36:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_util.h"
#include "cub_util.h"
#include "libft/libft.h"

/*
** Finds the first argument of the line and points to it.
** This skips the line identifier and the following spaces.
** @param const char* line The line to skip.
** @return char* A pointer to the character in the source string.
*/

static char		*skip_id(const char *line)
{
	while (*line && !ft_isspace(*line))
		line++;
	if (!*line)
		throw(-1, "Line has no argument.");
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		throw(-1, "Line has no argument.");
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
		throw(-1, "Passed null argument to GetIdentifier.");
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
** Duplicate identifiers are considered an error.
** @param char* line     Assumed non null and non-empty.
** @param t_mapfile* dst The mapfile object to fill.
*/

static void		parseline(char *line, t_mapfile *dst)
{
	unsigned int	id;

	id = getidentifier(line);
	if (line[0] == '1' && dst->map == NULL)
		; //parse grid
	else if (id == C && dst->ceilcol.a == 0)
		dst->ceilcol = parsecolor(skip_id(line));
	else if (id == F && dst->floorcol.a == 0)
		dst->floorcol = parsecolor(skip_id(line));
	else if (id == R && dst->screenwdt == 0 && dst->screenhgt == 0)
		parseresolution(skip_id(line), &dst->screenwdt, &dst->screenhgt);
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
	else
		throw(-1, "Unexpected identifier.");
}

/*
** Parses a *.cub file into a mapfile object.
** @param int fd     File descriptor of the cub file.
** @param t_mapfile* The mapfile object to fill.
*/

void			parsemap(int fd, t_mapfile *dst)
{
	char *line;
	char err;

	while (0 < (err = get_next_line(fd, &line)))
	{
		if (line[0] != '\0')
			parseline(line, dst);
		free(line);
	}
	if (err < 0)
		throw(errno, "GNL error");
	if (dst->screenwdt == 0 || dst->screenhgt == 0 || dst->map == NULL
		|| dst->north == NULL || dst->south == NULL || dst->east == NULL
		|| dst->west == NULL || dst->sprite == NULL || dst->floorcol.a == 0
		|| dst->ceilcol.a == 0)
		throw(-1, "Incomplete cub file.");
}
