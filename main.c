/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/15 15:38:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#include "cub.h"

int	main(int argc, char **args)
{
	int			fd;
	t_mapfile	map;

	if(arcg < 2)
		exit(-1);
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		exit(errno);
	parsemap(fd, &map);
}
