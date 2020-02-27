/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:26:14 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 14:55:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internals.h"

/*
** Initializes the z-buffer with the given size.
** @param unsigned int width,height The dimensions of the buffer.
** @return bool
** 	true  OK
** 	false Allocation failed.
*/

short	zbuffinit(unsigned int width)
{
	g_zbuffer = malloc(sizeof(float) * width);
	if (g_zbuffer)
	{
		zbuffclear();
		return (1);
	}
	else
		return (0);
}

/*
** Gets a texel from the z-buffer.
** @param unsigned int x,y The coordinates of the texel.
** @return float The depth of the texel.
*/

float	zbuffget(unsigned int x)
{
	return (g_zbuffer[x]);
}

/*
** Sets a texel into the z-buffer.
** @param float value The desired depth of the texel.
** @pqrqm unsigned int x,y The coordinates of the texel.
*/

void	zbuffset(unsigned int x, float value)
{
	g_zbuffer[x] = value;
}

/*
** Resets all texels of the z-buffer to the minimal depth.
*/

void	zbuffclear(void)
{
	unsigned int x;

	x = -1;
	while (++x < g_screenwdt)
		g_zbuffer[x] = g_clipspace.max.y;
}

/*
** Compares a given depth to the z-buffer.
** @param float value The depth to compare against the buffer.
** @param unsigned int x,y The coordinates of the texel.
** @return bool
** 	true  The value appears in front of the z-buffer.
** 	false The value appears behind the z-buffer.
*/

short	zbuffcmp(unsigned int x, float value)
{
	return (value > g_clipspace.min.y && value < zbuffget(x));
}
