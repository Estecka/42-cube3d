/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/16 15:27:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_util.h"
#include "cub_util.h"
#include "libft/libft.h"

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
	while (i < 4)
	{
		if (ft_isspace(line[i]))
			break ;
		result |= line[i] << (i * 8);
		i++;
	}
	return (result);
}

/*
** Parse a single line to fill the given mapfile object.
** @param char* line     Assumed non null and non-empty.
** @param t_mapfile* dst The mapfile object to fill.
*/

static void		parseline(char *line, t_mapfile *dst)
{
	unsigned int	id;

	id = getidentifier(line);
	if (line[0] == '1')
		; //parse grid
	else if (id == C)
		; //parse color
	else if (id == F)
		; // parse color
	else if (id == R)
		; //parse resolution
	else if (id == S)
		; //parse texture
	else if (id == NO)
		; //parse texture
	else if (id == SO)
		; //parse texture
	else if (id == WE)
		; //parse texture
	else if (id == EA)
		; //parse texture
	else
		throw(-1, "Unexpected identifier.");
}

/*
** Parses a *.cub file into a mapfile object.
** @param int fd     File descriptor of the cub file.
** @param t_mapfile* The mapfile object to fill.
** @return
** 	true  OK
** 	false Invalid cub file
*/

short			parsemap(int fd, t_mapfile *dst)
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
	return (1);
}
