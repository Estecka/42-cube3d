/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:44:35 by abaur             #+#    #+#             */
/*   Updated: 2020/02/27 16:45:58 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
#define FPS_H

#ifndef PERIOD
/*
* The amount of time in seconds between each log to stdout.
*/
#define PERIOD 1
#endif

/*
* The amount of time in seconds, between the beginning of the current frame and the previous one.
*/
float   g_deltatime;


/*
* Measures the execution time and framerate of the code.
* This function must be called exactly once per frame in order to work as expected.
* It logs an averaged result every PERIOD second(s) to stdout, and returns true when doing so.
* If `StopWatch` and `StartWatch` have been used, their results will also be logged there.
* 
* @return bool
* 	true	Results were logged. (At least one period has passed since previous true.)
* 	false	Results were not logged. (Less than a period has passed since previous true.)
*/
short	FpsLoop();


/*
* Marks the end of a specific portion of code whose execution time must be measured.
* The result in both percents and milliseconds are logged by `FpsLoop`.
* 
* Each call to StopWatch must *always* be matched with exactly one call to StartWatch at the beginning of the code portion.
*/
void	StopWatch();

/*
* Marks the beginning of a specific portion of code whose execution time must be measured.
* The result in both percents and milliseconds are logged by `FpsLoop`.
* 
* Each call to StartWatch must *always* be matched with exactly one call to StopWatch at the end of the code portion.
*/
void 	StartWatch();

#endif
