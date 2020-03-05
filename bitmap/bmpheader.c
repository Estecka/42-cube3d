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