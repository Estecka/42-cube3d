/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clampresolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/02/12 17:27:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cub/cub.h"
#include "minilibx/mlx.h"

void	clampresolution(t_cubworld *world)
{
	int xmax;
	int ymax;

	mlx_get_screen_size(g_mlx, &xmax, &ymax);
	if (xmax < world->resolution.x)
		world->resolution.x = xmax;
	if (ymax < world->resolution.y)
		world->resolution.y = ymax;
}
