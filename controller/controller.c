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
#define ROTSPEED 0.1

extern void	onkeypress(int keycode)
{
	union u_v4 movement;

	movement.vec4 = (t_v4){ 0, 0, 0, 0};
	if (keycode == KCLEFT)
		g_player.rotation.y -= ROTSPEED;
	else if (keycode == KCRIGHT)
		g_player.rotation.y += ROTSPEED;

	else if (keycode == KCW)
		movement.vec3.z -= MOVSPEED;
	else if (keycode == KCS)
		movement.vec3.z += MOVSPEED;
	else if (keycode == KCA)
		movement.vec3.x -= MOVSPEED;
	else if (keycode == KCD)
		movement.vec3.x += MOVSPEED;
	else if (keycode == KCSPACE)
		printf("%f %f %f \n%f\n", g_player.position.x, g_player.position.y, g_player.position.z, g_player.rotation.y * RAD2DEG);

	movement = mx4v4(g_player.l2wmx, &movement.vec4);
	addvec3(&g_player.position, &g_player.position, &movement.vec3);
}