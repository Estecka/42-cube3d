/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:22:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_util.h"

/*
** Parse the map section of a cub file.
** The very first row is assumed to be already parsed.
** Checks that the file ends with the grid, empty lines are tolerated.
** @param int fd The file descriptor to read from.
** @param t_cubfile* file The object to fill.
** @param t_strb* builder The stringbuilder to use.
*/

static void		parsetiles(int fd, t_cubfile *file, t_strb *builder)
{
	char	*line;
	char	c;
	short	isvalidend;
	int		playercount;
	int		gnl;

	playercount = 0;
	isvalidend = 0;
	while (0 < (gnl = get_next_line(fd, &line)) && line[0])
	{
		isvalidend = validategridrow(line, file);
		playercount += parsegridrow(line, file, builder);
		free(line);
		line = NULL;
		file->maphgt++;
	}
	if (line)
		free(line);
	throwif(gnl < 0, errno, "[FATAL] GNL error: %d", errno);
	throwif(playercount != 1, -1, "Invalid player count: %d", playercount);
	throwif(!isvalidend, -1, "Invalid final row.");
	while (0 < (gnl = get_next_char(fd, &c)))
		throwif(!ft_isspace(c), -1, "Invalid end of file: %c", c);
	throwif(gnl < 0, errno, "[FATAL] get_next_char error: %d", errno);
}

/*
** Parses a *.cub file into a mapfile object.
** @param int fd     File descriptor of the cub file.
** @param t_cubfile* The mapfile object to fill.
*/

void			parsefile(int fd, t_cubfile *dst)
{
	char	*line;
	int		err;
	t_strb	*strbuilder;

	while (0 < (err = get_next_line(fd, &line)) && line[0] != '1')
	{
		if (line[0] != '\0')
			parsefield(line, dst);
		free(line);
		line = NULL;
	}
	if (err < 0)
		throw(errno, "Fatal: GNL error: %d", errno);
	if (err == 0 || dst->screenwdt == 0 || dst->screenhgt == 0
		|| dst->north == NULL || dst->south == NULL || dst->east == NULL
		|| dst->west == NULL || dst->sprite == NULL
		|| dst->floorcol.rgba.a == 0 || dst->ceilcol.rgba.a == 0)
		throw(-1, "Incomplete cub file.");
	strbuilder = parsegridwidth(line, dst);
	if (line)
		free(line);
	parsetiles(fd, dst, strbuilder);
	dst->tiles = strbflush(strbuilder);
}
