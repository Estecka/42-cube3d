/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 12:52:06 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_printf/ft_printf.h"

#include "cube3d.h"
#include "cub.h"

#include "minilibx/mlx.h"
#include "keycode.h"

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
	t_mapfile	map;
	void		*mlx;
	void		*win;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file: %d", errno);
	ft_bzero(&map, sizeof(t_mapfile));
	parsefile(fd, &map);
	if (!(mlx = mlx_init()))
		throw(errno, "[FATAL] MinilibX init failed : %d", errno);
	win = mlx_new_window(mlx, map.screenwdt, map.screenhgt, "Cube3D : The Reckoning");
	mlx_key_hook(win, exitonesc, NULL);
	mlx_hook(win, 17, 1<<17, exitonx, NULL);
	mlx_loop(mlx);
}
