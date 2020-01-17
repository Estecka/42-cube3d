/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:35:02 by abaur             #+#    #+#             */
/*   Updated: 2020/01/17 16:18:05 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_util.h"
#include "cub_util.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
** Parse the width then height of the screen.
** Extra characters are treated as errors.
** @param const char* line
** @param int* width Output the width of the screen.
** @param int* height Outputs the height of the screen.
*/

void	parseresolution(const char *line, int *width, int *height)
{
	*width = 0;
	*height = 0;
	while (*line && ft_isdigit(*line))
	{
		*width = (*width * 10) + (*line - '0');
		line++;
	}
	while (*line && ft_isspace(*line))
		line++;
	while (*line && ft_isdigit(*line))
	{
		*height = (*height * 10) + (*line - '0');
		line++;
	}
	while (*line && ft_isspace(*line))
		line++;
	if (*line || *height == 0 || *width == 0)
		throw(-1, "Bad resolution format.");
}

/*
** Parse the path to a texture file.
** Makes sure the file exists.
** TODO: actually check that the file is a texture.
** @param const char* line
** @return An allocated copy of the path
*/

char	*parsetexpath(const char *line)
{
	int		fd;
	char	*dst;

	fd = open(line, O_RDONLY);
	if (fd < 0)
		throw(-1, "Invalid texture path");
	else
		close(fd);
	dst = ft_strdup(line);
	if (!dst)
		throw(-1, "Malloc failed in ParseTexturePath");
	return (dst);
}

/*
** Parse the RGB components of a color.
** @param const char* line
** @return A fully opaque color.
*/

t_color	parsecolor(const char *line)
{
	t_color	color;

	color = (t_color){ 0, 0, 0, 1 };
	while (ft_isdigit(*line))
		color.r = (10 * color.r) + *(line++) - '0';
	if (*line != ',' || !ft_isdigit(*(++line)))
		throw(-1, "Invalid character after Red.");
	while (ft_isdigit(*line))
		color.g = (10 * color.g) + *(line++) - '0';
	if (*line != ',' || !ft_isdigit(*(++line)))
		throw(-1, "Invalid character after Green.");
	while (ft_isdigit(*line))
		color.b = (10 * color.b) + *(line++) - '0';
	while (ft_isspace(*line))
		line++;
	if (*line)
		throw(-1, "Invalid character after Blue");
	return (color);
}
