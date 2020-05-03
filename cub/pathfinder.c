/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:07:40 by abaur             #+#    #+#             */
/*   Updated: 2020/02/17 11:07:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_util.h"
#include <stdio.h>

/*
** Explore the map recursively from the given tile.
** @return bool
** 	true  The area is closed, or has already been explored.
** 	false The area leaks into the abyss.
*/

static short	explore(t_cubworld *this, int x, int y, char*const *list)
{
	if (x < 0 || y < 0 || x >= this->mapsize.x || y >= this->mapsize.y)
		return (0);
	if (list[x][y])
		return (1);
	list[x][y] = 1;
	if (this->tiles[x][y] == '\0')
		return (0);
	if (this->tiles[x][y] == '1')
		return (1);
	if (!explore(this, x + 1, y, list))
		return (0);
	if (!explore(this, x - 1, y, list))
		return (0);
	if (!explore(this, x, y + 1, list))
		return (0);
	if (!explore(this, x, y - 1, list))
		return (0);
	return (1);
}

/*
** Checks whether the player is able to escape the map.
** @param t_cubworld* this
** @param char[][] checklist	A empty pre-allocated grid the same size of the
**  map, used as a draft.
*/

void			escaperoom(t_cubworld *this)
{
	char*const *checklist;

	if (!(checklist =
		(char*const*)malloc2d(this->mapsize.x, this->mapsize.y, sizeof(char))))
		throw(errno, "[FATAL] Pathfinder allocation failed.");
	if (!explore(this, this->playerspawn.x, this->playerspawn.y, checklist))
		throw(-1, "The map is not closed.");
	free((void*)checklist);
}
