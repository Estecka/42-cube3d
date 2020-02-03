/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:32:44 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 16:29:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../renderer.h"
#include "../../minilibx/mlx.h"

#include <math.h>

void *g_mlx;
void *g_window;

int	width, height;

int	loop(void* null)
{
	static int blue = 0;

	blue++;
	while (blue > 255)
		blue -= 255;
	for (int x=0; x<width;  x++)
	for (int y=0; y<height; y++)
	{
		union u_color color;
		color.rgba.a = 1;
		color.rgba.b = blue;
		color.rgba.g = (x * 255) / width;
		color.rgba.r = (y * 255) / height;
		renderset(x, y, color);
	}
	renderflush(null);
	return (0);
}

int main(int argc, char **args)
{
	if (argc < 3)
		exit(-1);

	(void)argc;
	width  = atoi(args[1]);
	height = atoi(args[2]);

	g_mlx = mlx_init();
	g_window = mlx_new_window(g_mlx, width, height, "Renderer Test");
	renderinit(width, height);

	mlx_loop_hook(g_mlx, loop, NULL);
	mlx_loop(g_mlx);
}
