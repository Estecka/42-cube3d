/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:35:02 by abaur             #+#    #+#             */
/*   Updated: 2020/01/17 11:53:13 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_util.h"
#include "cub_util.h"

#include <stdlib.h>

/*
** Parse the width then height of the screen.
** @param const char* line
** @param int* width Output the width of the screen.
** @param int* height Outputs the height of the screen.
*/

void	parseresolution(const char *line, int *width, int *height)
{
}

/*
** Parse the path to a texture file.
** TODO: actually check that the file is a texture.
** @param const char* line
** @return An allocated copy of the path
*/

char	*parsetexpath(const char *line)
{
	return (NULL);
}

/*
** Parse the RGB components of a color
** @param const char* line
** @return A fully opaque color.
*/

t_color	parsecolor(const char *line)
{
	return (t_color){ 0 };
}
