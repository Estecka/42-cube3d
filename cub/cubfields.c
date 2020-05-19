/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfields.c                                        :+:      :+:    :+:   */
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

void			parseresolution(const char *line, int *width, int *height)
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
		throw(-1, "[CUB] Bad resolution format: \n%s", src);
}

/*
** Parses a string.
** Does not actually check any kind of format.
** @param const char* line
** @return An allocated copy of the path
*/

void			parsetexpath(const char *line, char **dst)
{
	*dst = ft_strdup(line);
	if (!*dst)
		throw(errno, "[FATAL] strdup failed in ParseTexturePath: \n%s", line);
	spyregpp(dst);
}

/*
** Parses a single RGB component of a color, and moves the cursor forward as ne
** eded.
** @param const char** line	A pointer to the current cursor.
** @param const char*	src	The full line. Required only for error messages.
** @return short	The color component
*/

static short	parsecolorrgb(char rgb, const char **line, const char *src)
{
	short value;

	value = 0;
	while (ft_isdigit(**line))
	{
		value = (10 * value) + *((*line)++) - '0';
		if (value < 0 || value > 255)
			throw(-1, "[CUB] Invalid %c color component : \n%s", rgb, src);
	}
	if (rgb == 'B')
	{
		while (ft_isspace(**line))
			(*line)++;
		if (**line)
			throw(-1, "[CUB] Garbage character after color: \n%s", src);
	}
	else if (**line != ',' || !ft_isdigit(*(++*line)))
		throw(-1, "[CUB] Invalid character after %c: \n%s", rgb, src);
	return (value);
}

/*
** Parse the RGB components of a color.
** @param const char* line
** @return A fully opaque color.
*/

t_rgba			parsecolor(const char *line)
{
	t_rgba		color;
	const char	*src;

	src = line;
	color = (t_rgba){ 0, 0, 0, 1 };
	color.r = parsecolorrgb('R', &line, src);
	color.g = parsecolorrgb('G', &line, src);
	color.b = parsecolorrgb('B', &line, src);
	return (color);
}
