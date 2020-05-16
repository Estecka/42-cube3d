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

#define CLOCKS_TO_MS (1000/(float)CLOCKS_PER_SEC)

/*
* @var unsigned int watchcalls	The amount of stopwatches called during the current period.
* @var clock_t watchstart	The ellapsed time in clocks since the last call to `StartWatch`.
* @var clock_t watchclocks	The cumulative time in clocks measured by all stopwatches during the current period. 
*/

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

/*
* @var clock_t prevFrame	The time in clocks when the previous frame started.
* @var clock_t prevPeriod	The time in clocks when the previous period started.
* @var signed int framecount	The ellapsed time in frames since the current period started.
*/

/*
* @var clock_t currentTime	The current time in clocks. This marks the end of the previous frame and the beginning of the next one.
* @var clock_t inter	The duration of the current period in clocks.
* @var float interms	The duration of the current period in milliseconds.
* @var bool isPeriod	Whether the current period has fully ellapsed.
* @var float watchtime	The cumulative time in milliseconds, measured by all stopwatches during the current period.
* @var float workload	The portion of time in percentage, that `watchtime` represents.
*/

extern short FpsLoop()
{
	static clock_t prevFrame = 0; 
	static clock_t prevPeriod = 0;
	static int framecount = 0;

	framecount++;

	clock_t currentTime = clock();
	g_deltatime = (currentTime - prevFrame) / (float)CLOCKS_PER_SEC;

	clock_t inter = currentTime - prevPeriod;
	short isPeriod = inter > (PERIOD * CLOCKS_PER_SEC);
	if (isPeriod)
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

		prevPeriod = currentTime;
		framecount = 0;
	}
	prevFrame = currentTime;
	return isPeriod;
}
