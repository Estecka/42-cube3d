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
#include "fps.h"

#define PERIOD 1
#define CLOCKS_TO_MS (1000/(float)CLOCKS_PER_SEC)

static unsigned int watchcalls = 0;
static clock_t watchstart = 0;
static clock_t watchclocks = 0;

extern void StartWatch()
{
	watchstart = clock();
}

extern void	StopWatch()
{
	watchclocks += clock() - watchstart;
	watchcalls++;
}

extern void	FpsLoop()
{
	static clock_t prevTime = 0; 
	static clock_t lastPeriod = 0;
	static int framecount = 0;

	framecount++;

	clock_t currentTime = clock();
	g_deltatime = (currentTime - prevTime) / (float)CLOCKS_PER_SEC;

	clock_t inter = currentTime - lastPeriod;
	if (inter > (PERIOD * CLOCKS_PER_SEC))
	{
		float interms = inter * CLOCKS_TO_MS;

		printf("Framerate: %.1f", framecount * (CLOCKS_PER_SEC/(float)inter));
		printf(" (%.3f ms)\n", interms/framecount);

		if (watchcalls) {
			float watchtime = watchclocks * CLOCKS_TO_MS;
			float workload = 100 * watchtime / interms;
			printf("Stopwatch: %.3fms (%.1f%%).\n", watchtime/framecount, workload);
			printf("\n");
			watchclocks = 0;
			watchcalls  = 0;
		}

		lastPeriod = currentTime;
		framecount = 0;
	}
	prevTime = currentTime;
}
