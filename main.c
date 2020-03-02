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
	onkeypress(keycode);
	return (0);
}

#include ".fps/fps.c"
static int	update(t_cubworld *cub)
{
	rendersky(0 + 0.5f, cub->floorcol, cub->ceilcol);
	renderworld();
	renderflush();
	FpsLoop();
	g_log = 0;
	return (0);
}

extern int	main(int argc, char **args)
{
	int			fd;
	union u_cub	cub;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file: %d", errno);
	cub.world = (t_cubworld){0};
	parsefile(&cub.file, fd);
	cubfile2world(&cub);
	if (!(g_mlx = mlx_init()))
		throw(errno, "[FATAL] MinilibX init failed : %d", errno);
	renderinit(cub.world.resolution.x, cub.world.resolution.y);
	worldinit(&cub.world);
	g_window = mlx_new_window(g_mlx, cub.world.resolution.x, cub.world.resolution.y, "Cube3D : The Reckoning");
	mlx_key_hook(g_window, exitonesc, NULL);
	mlx_hook(g_window, 17, 1<<17, exitonx, NULL);
	mlx_loop_hook(g_mlx, update, &cub);
	mlx_loop(g_mlx);
}
