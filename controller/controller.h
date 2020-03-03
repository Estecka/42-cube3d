/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:12:56 by abaur             #+#    #+#             */
/*   Updated: 2020/02/20 12:12:57 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "../worldbuilder/worldbuilder.h"

float	g_altitude;
float	g_angle;

int		keypressevent(int keycode, void *null);
int		keyreleaseevent(int keycode, void *null);

void	controllerloop();

#endif