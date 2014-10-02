/*
 * Interrupt.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */

#include "../Headers/Interrupt.h"
static alt_alarm alarm;

alt_u32 interruptFunction(void* context)
{
	updatePosition(level->balls);
	drawBall(level->balls);
	updatePosition(level->balls2);
	drawBall(level->balls2);
	updatePosition(level->balls3);
	drawBall(level->balls3);
	moveHorizontal(level->paddle, getUserInput());
	drawPaddle(level->paddle);

	return alt_ticks_per_second()/screenRefreshRate;
}

void initInterrupt()
{
	alt_alarm_start (&alarm, alt_ticks_per_second()/screenRefreshRate, interruptFunction, NULL );
}

void stopInterrupt()
{
	alt_alarm_stop (&alarm);
}
