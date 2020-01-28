/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:35:02 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:49:06 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	const char *src;

	src = line;
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
		throw(-1, "Bad resolution format: \n%s", src);
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
		throw(errno, "Invalid texture path: %d \n%s", errno, line);
	else
		close(fd);
	dst = ft_strdup(line);
	if (!dst)
		throw(errno, "Fatal: Malloc failed in ParseTexturePath: %d\n%s",
			errno, line);
	return (dst);
}

/*
** Parse the RGB components of a color.
** @param const char* line
** @return A fully opaque color.
*/

t_rgba	parsecolor(const char *line)
{
	t_rgba		color;
	const char	*src;

	src = line;
	color = (t_rgba){ 0, 0, 0, 1 };
	while (ft_isdigit(*line))
		color.r = (10 * color.r) + *(line++) - '0';
	if (*line != ',' || !ft_isdigit(*(++line)))
		throw(-1, "Invalid character after Red: %s", src);
	while (ft_isdigit(*line))
		color.g = (10 * color.g) + *(line++) - '0';
	if (*line != ',' || !ft_isdigit(*(++line)))
		throw(-1, "Invalid character after Green: %s", src);
	while (ft_isdigit(*line))
		color.b = (10 * color.b) + *(line++) - '0';
	while (ft_isspace(*line))
		line++;
	if (*line)
		throw(-1, "Invalid character after Blue: %s", src);
	return (color);
}
