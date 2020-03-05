/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpheader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:37:23 by abaur             #+#    #+#             */
/*   Updated: 2020/03/05 15:37:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp_internals.h"

/*
** Extract the different headers from the file.
** @param int fd	The file descriptor to read from.
** 	The cursor is moved until before the first texel.
** @return bool
** 	true 	OK
**  false	The filestream ended unexpectedly.
*/

static short	get_bmp_headers(int fd, t_bmpheader *header, t_bmpinfo *info)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = (unsigned char*)header;
	i = -1;
	while (++i < sizeof(t_bmpheader))
		if (1 > get_next_char(fd, bytes + i))
			return (0);
	bytes = (unsigned char*)info;
	i = -1;
	while (++i < sizeof(t_bmpinfo))
		if (1 > get_next_char(fd, bytes + i))
			return (0);
	i--;
	while (++i < info->headersize)
		if (1 > get_next_char(fd, NULL))
			return (0);
	return (1);
}

static short	bmp_validate_headers(t_bmpheader *header, t_bmpinfo *info)
{
	if (header->filetype[0] != 'B' || header->filetype[1] != 'M'
		|| header->pixeldataoffset != sizeof(t_bmpheader) + info->headersize
		|| info->imagewidth <= 0 || info->imagewidth <= 0
		|| info->planes != 1
		|| (info->bitsperpixel != 32 && info->bitsperpixel != 24)
		|| info->totalcolors != 0 || info->importantcolors != 0)
		return (0);
	else
		return (1);
}

static short	get_bmp_texels(int fd, t_mlx_img *dst, t_bmpinfo *info)
{
	unsigned int	x;
	unsigned int	y;
	unsigned char	*color;

	y = -1;
	while(++y < info->imageheight)
	{
		x = -1;
		while (++x < info->imagewidth)
		{
			c = (unsigned char*)mlx_img_getptr(dst, x, y);
			if (1 > get_next_char(fd, color + 0)
				|| 1 > get_next_char(fd, color + 1)
				|| 1 > get_next_char(fd, color + 2))
				return (0);
			if (info->bitsperpixel == 32 && 1 > get_next_char(fd, color + 3))
				return (0);
		}
		x *= info->bitsperpixel / 8;
		while (x++ % 4)
			if (1 > get_next_char(fd, NULL))
				return (0);
	}
	return (1);
}
