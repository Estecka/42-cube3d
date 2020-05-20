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

#include "cube3d.h"
#include "cub/cub.h"
#include "renderer/renderer.h"
#include "worldbuilder/worldbuilder.h"
#include "controller/controller.h"
#include "mallocspy/mallocspy.h"

#include "minilibx/mlx.h"
#include "keycode.h"

void		*g_mlx = NULL;
void		*g_window = NULL;

static int	exitonx(void *null)
{
	(void)null;
	spyflush();
	exit(0);
	return (0);
}

static int	update(t_cubworld *cub)
{
	controllerloop();
	rendersky(cub->floorcol, cub->ceilcol);
	renderworld();
	renderflush();
	g_log = 0;
	return (0);
}

static void	play(t_cubworld *world)
{
	g_window = mlx_new_window(g_mlx, world->resolution.x, world->resolution.y,
		"Cube3D : The Reckoning");
	spyregpp(&g_window);
	mlx_hook(g_window, 2, 1L << 0, keypressevent, NULL);
	mlx_hook(g_window, 3, 1L << 1, keyreleaseevent, NULL);
	mlx_hook(g_window, 33, 1L << 17, exitonx, NULL);
	mlx_loop_hook(g_mlx, update, world);
	mlx_loop(g_mlx);
}

static void	save(t_cubworld *world, const char *path)
{
	rendersky(world->floorcol, world->ceilcol);
	renderworld();
	rendersave(path);
}

extern int	main(int argc, char **args)
{
	int			fd;
	union u_cub	cub;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	if (argc != 2 && (argc != 4 || ft_strncmp("--save", args[2], 7)))
		throw(-1, "Invalid synopsis.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file.");
	cub.world = (t_cubworld){0};
	parsefile(&cub.file, fd);
	cubfile2world(&cub);
	if (!(g_mlx = mlx_init()))
		throw(errno, "[FATAL] MinilibX init failed.");
	if (argc < 3)
		clampresolution(&cub.world);
	spyregpp(&g_mlx);
	renderinit(cub.world.resolution.x, cub.world.resolution.y);
	worldinit(&cub.world);
	if (argc == 2)
		play(&cub.world);
	else
		save(&cub.world, args[3]);
	spyflush();
}
