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
	t_bmpinfo	info;

	info = (t_bmpinfo){ 0 };
	info.headersize = sizeof(t_bmpinfo);
	info.imagewidth = this->width;
	info.imageheight = this->height;
	info.planes = 1;
	info.bitsperpixel = 32;
	info.imagesize = this->width * 32;
	info.imagesize += info.imagesize % 4;
	info.imagesize *= info.imageheight;
	if (0 > write(fd, &info, sizeof(t_bmpinfo)))
		return (0);
	else
		return (1);
}

static short	bmp_write_pixel(t_mlx_img *this, int fd)
{
	unsigned int	y;
	unsigned int	size;

	y = -1;
	while (++y < this->height)
	{
		size = this->width * 32;
		if (0 > write(fd, mlx_img_getptr(this, 0, y), size))
			return (0);
		size %= 4;
		if (size && write(fd, "\0\0\0", size))
			return (0);
	}
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