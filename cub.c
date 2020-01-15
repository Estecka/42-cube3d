/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/15 15:38:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft/libft.h"

/*
** Parses a *.cub file into a mapfile object.
** @param int fd     File descriptor of the cub file.
** @param t_mapfile* Outputs the resulting mapfile object.
** @return
** 	true  OK
** 	false Invalid cub file
*/

short	parsemap(int fd, t_mapfile *dst)
{
	char *line;

	while(0 < get_next_line(fd, line))
	{
		//...
		if (line)
			free(line);
	}
	return (1);
}
