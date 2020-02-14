/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubworld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:23:21 by abaur             #+#    #+#             */
/*   Updated: 2020/01/23 14:48:09 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include "cub_util.h"

#define WMAX 2560
#define HMAX 1440

/*
** Fetches the texture at the given path.
** The reference to the path is automatically free.
** TODO This a dummy, and for now and only checks that the file exists.
** @param char[] path	The path to the texture.
** @return t_mlg_img*	The texture at the path.
*/

static void *gettexture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("Could not open file: %d\n\t%s\n", errno, path);
	else
		close(fd);
	free(path);
	return (NULL);
}

/*
** Converts a cubfile to cubworld.
** @param union u_cub* this
*/

extern void	cubfile2world(union u_cub *this)
{
	if (this->file.resolution.x > WMAX)
		this->world.resolution.x = WMAX;
	if (this->file.resolution.y > HMAX)
		this->world.resolution.y = HMAX;
	this->world.floorcol.rgba.a = 0;
	this->world.ceilcol.rgba.a = 0;
	this->world.north = gettexture(this->file.north);
	this->world.south = gettexture(this->file.south);
	this->world.east = gettexture(this->file.east);
	this->world.west = gettexture(this->file.west);
	this->world.sprite = gettexture(this->file.sprite);
};
