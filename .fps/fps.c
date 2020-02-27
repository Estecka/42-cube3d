/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:46:04 by abaur             #+#    #+#             */
/*   Updated: 2020/02/27 16:52:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>

#define PERIOD 1

extern void	FpsLoop()
{
	static clock_t lastTime;
	static int framecount = 0;

	framecount++;

	clock_t currentTime = clock();
	clock_t inter = currentTime - lastTime;
	if (inter > (PERIOD * CLOCKS_PER_SEC))
	{
		printf("Framerate: %f\n", framecount * (CLOCKS_PER_SEC / (float)inter));
		lastTime = currentTime;
		framecount = 0;
	}
	
}
