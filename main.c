/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/17 11:17:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "libft/libft.h"

#include "cub.h"

void	throw(int status, char *message)
{
	ft_putstr("Error\n");
	ft_putstr(message);
	exit(status);
}

int		main(int argc, char **args)
{
	int			fd;
	t_mapfile	map;

	if (argc < 2)
		throw(-1, "Not enough arguments.");
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		throw(errno, "Could not open file.");
	ft_bzero(&map, sizeof(t_mapfile));
	parsemap(fd, &map);
}
