/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpwrite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:37:23 by abaur             #+#    #+#             */
/*   Updated: 2020/03/05 15:37:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "bmp_internals.h"

static short	bmp_write_header(t_mlx_img *this, int fd)
{
	t_bmpheader	header;

	header = (t_bmpheader){ 0 };
	header.filetype[0] = 'B';
	header.filetype[0] = 'M';
	header.pixeldataoffset = sizeof(t_bmpheader) + sizeof(t_bmpinfo);
	header.filesize = header.pixeldataoffset;
	header.filesize += this->width * this->height * 32;
	if (0 > write(fd, &header, sizeof(t_bmpheader)))
		return (0);
	else
		return (1);
}

static short	bmp_write_info(t_mlx_img *this, int fd)
{
	return (1);
}

static short	bmp_write_pixel(t_mlx_img *this, int fd)
{
	return (1);
}

extern short	bmp_write(t_mlx_img *this, const char *path)
{
	int	fd;

	if (0 >	fd  = open(path, O_CREAT | O_WRONLY | O_TRUNC))
		return (0);
	if (!bmp_write_header(this, fd)
		|| !bmp_write_info(this, fd)
		|| !bmp_write_pixel(this, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
