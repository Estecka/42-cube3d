/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/16 13:23:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_util.h"
#include "cub.h"
#include "libft/libft.h"

/*
** Parse a single line to fill the given mapfile object.
** @param char* line     Assumed non null and non-empty.
** @param t_mapfile* dst The mapfile object to fill.
*/

static void	parseline(char *line, t_mapfile *dst)
{
	if (line[0] == '1')
		; //parse grid
	else if (ft_isspace(line[1]) && (line[0] == 'F' || line[0] == 'C'))
		; //parse color
	else if (ft_isspace(line[1]) && (line[0] == 'R'))
		; //parse resolution
	else if (ft_isspace(line[1]) && (line[0] == 'S'))
		; //parse texture
	else if (ft_isupper(line[0]) && ft_isupper(line[1]) && ft_isspace(line[2]))
		; //parse texture
	else
		throw(-1, "Unexpected character");
}

/*
** Parses a *.cub file into a mapfile object.
** @param int fd     File descriptor of the cub file.
** @param t_mapfile* The mapfile object to fill.
** @return
** 	true  OK
** 	false Invalid cub file
*/

short		parsemap(int fd, t_mapfile *dst)
{
	char *line;
	char err;

	while (0 < (err = get_next_line(fd, line)))
	{
		if (line[0] != '\0')
			parseline(line, dst);
		free(line);
	}
	if (err < 0)
		throw(errno, "GNL error");
	return (1);
}
