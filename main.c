/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/02/12 17:27:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_printf/ft_printf.h"

#include "cube3d.h"
#include "cub/cub.h"
#include "renderer/renderer.h"

#include "minilibx/mlx.h"
#include "keycode.h"

void		*g_mlx = NULL;
void		*g_window = NULL;

static int	exitonx(void *null)
{
	(void)null;
	exit(0);
	return (0);
}

static int	exitonesc(int keycode, void *null)
{
	(void)null;
	if (keycode == KCESC)
		exit(0);
	return (0);
}


extern int	main(int argc, char **args)
{
	int			fd;
	t_cubfile	map;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file: %d", errno);
	ft_bzero(&map, sizeof(t_cubfile));
	parsefile(fd, &map);
	if (!(g_mlx = mlx_init()))
		throw(errno, "[FATAL] MinilibX init failed : %d", errno);
	graphicinit(&map);
	g_window = mlx_new_window(g_mlx, map.screenwdt, map.screenhgt, "Cube3D : The Reckoning");
	mlx_key_hook(g_window, exitonesc, NULL);
	mlx_expose_hook(g_window, graphhook, NULL);
	mlx_hook(g_window, 17, 1<<17, exitonx, NULL);
	mlx_loop(g_mlx);
}
