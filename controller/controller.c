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

/*
** It's important that movement has 1 extra dimension, so it can be transformed
**  as a vector instead of as a position.
*/

extern void	onkeypress(int keycode)
{
	union u_v3 movement;

	movement.vec3 = (t_v3){ 0, 0, 0};
	if (keycode == KCLEFT)
		g_player.rotation += ROTSPEED;
	else if (keycode == KCRIGHT)
		g_player.rotation -= ROTSPEED;

	else if (keycode == KCW)
		movement.vec2.y -= MOVSPEED;
	else if (keycode == KCS)
		movement.vec2.y += MOVSPEED;
	else if (keycode == KCA)
		movement.vec2.x -= MOVSPEED;
	else if (keycode == KCD)
		movement.vec2.x += MOVSPEED;
	else if (keycode == KCSPACE)
		printf("%f %f\n%f\n", g_player.position.x, g_player.position.y, g_player.rotation * RAD2DEG);

	movement = mx3v3(g_player.l2wmx, &movement.vec3);
	addvec2(&g_player.position, &g_player.position, &movement.vec2);
}