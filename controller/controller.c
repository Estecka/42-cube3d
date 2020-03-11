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

#define MOVSPEED 1
#define ROTSPEED 1

#define KCMAX 258

float			g_altitude = 0.5f;
float			g_angle = 0.5f;

static short	g_keymask[KCMAX];

extern int		keypressevent(int keycode, void *null)
{
	(void)null;
	if (keycode == KCESC)
		exit(0);
	else if (keycode ==  KCSPACE)
		g_log = 1;
	if (keycode < KCMAX)
		g_keymask[keycode] = 1;
	return (0);
}

extern int		keyreleaseevent(int keycode, void *null)
{
	(void)null;
	if (keycode < KCMAX)
		g_keymask[keycode] = 0;
	return (0);
}

static float	deltatime(void)
{
	return (1/(float)30);
}

static float	controllerloop2(void)
{
	if (g_keymask[KCSPACE])
	{
		g_altitude = 0.25f;
		return (1/3.f);
	}
	else
	{
		g_altitude = 0.5f;
		if (g_keymask[KCLSHIFT])
			return (3);
		else
			return (1);
	}
}

/*
** It's important that movement has 1 extra dimension, so it can be transformed
**  as a vector instead of as a position.
*/

extern void		controllerloop(void)
{
	union u_v3	movement;
	float		sprint;

	movement.vec3 = (t_v3){ 0, 0, 0};
	sprint = controllerloop2();
	if (g_keymask[KCLEFT])
		g_player.rotation -= ROTSPEED * deltatime();
	else if (g_keymask[KCRIGHT])
		g_player.rotation += ROTSPEED * deltatime();
	if (g_keymask[KCUP])
		g_angle += ROTSPEED * deltatime();
	else if (g_keymask[KCDOWN])
		g_angle -= ROTSPEED * deltatime();
	if (g_keymask[KCW])
		movement.vec2.y -= MOVSPEED * sprint * deltatime();
	else if (g_keymask[KCS])
		movement.vec2.y += MOVSPEED * sprint * deltatime();
	if (g_keymask[KCA])
		movement.vec2.x -= MOVSPEED * sprint * deltatime();
	else if (g_keymask[KCD])
		movement.vec2.x += MOVSPEED * sprint * deltatime();
	movement = mx3v3(g_player.l2wmx, &movement.vec3);
	addvec2(&g_player.position, &g_player.position, &movement.vec2);
}
