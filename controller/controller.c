/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:13:46 by abaur             #+#    #+#             */
/*   Updated: 2020/02/20 12:13:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "../worldbuilder/worldbuilder.h"
#include "../keycode.h"

#include <stdio.h>
#include "../ft_math/ft_math.h"

#define MOVSPEED 0.1
#define ROTSPEED 0.05

static short	g_keymask[128];

extern int		keypressevent(int keycode, void *null)
{
	(void)null;
	if (keycode == KCESC)
		exit(0);
	if (keycode < 128)
		g_keymask[keycode] = 1;
	return (0);
}

extern int		keyreleaseevent(int keycode, void *null)
{
	(void)null;
	if (keycode < 128)
		g_keymask[keycode] = 0;
	return (0);
}

/*
** It's important that movement has 1 extra dimension, so it can be transformed
**  as a vector instead of as a position.
*/

extern void		controllerloop()
{
	union u_v3 movement;

	movement.vec3 = (t_v3){ 0, 0, 0};
	if (g_keymask[KCLEFT])
		g_player.rotation += ROTSPEED;
	else if (g_keymask[KCRIGHT])
		g_player.rotation -= ROTSPEED;
	if (g_keymask[KCW])
		movement.vec2.y -= MOVSPEED;
	else if (g_keymask[KCS])
		movement.vec2.y += MOVSPEED;
	if (g_keymask[KCA])
		movement.vec2.x -= MOVSPEED;
	else if (g_keymask[KCD])
		movement.vec2.x += MOVSPEED;
	if (g_keymask[KCSPACE])
		g_log = 1;
	movement = mx3v3(g_player.l2wmx, &movement.vec3);
	addvec2(&g_player.position, &g_player.position, &movement.vec2);
}