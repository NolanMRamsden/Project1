/*
 * Interrupt.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */

#include "../Headers/Interrupt.h"

static alt_alarm alarm;
int countDown;

/*
 * game loop update and drawing
 */
alt_u32 interruptFunction(void* context)
{
	int i=0;
	for(i=0;i<maxBalls;i++)
	{
		if(currentLevel->ball[i]->alive)
		{
			updatePosition(currentLevel->ball[i]);
			drawBall(currentLevel->ball[i]);
		}
	}

	if(currentLevel->buff->alive)
	{
		updateBuff(currentLevel->buff);
		drawBuff(currentLevel->buff);
	}

	moveHorizontal(currentLevel->paddle, getUserInput());
	drawPaddle(currentLevel->paddle);

	return alt_ticks_per_second()/screenRefreshRate;
}

alt_u32 count(void *context)
{
	countDown=1;
	return alt_ticks_per_second();
}

/*
 * initiliazes the interrupt for game loop
 */
void initInterrupt()
{
	alt_alarm_start (&alarm, alt_ticks_per_second()/screenRefreshRate, interruptFunction, NULL );
}
/*
 * produces the countdown 3 2 1 GO! on the screen
 */
void runCountDown()
{
	countDown=0;
	alt_alarm_start (&alarm, alt_ticks_per_second(), count, NULL );
	drawText("3",38,40,0);
	while(countDown==0);
	countDown=0;
	drawText("2",38,40,0);
	while(countDown==0);
	countDown=0;
	drawText("1",38,40,0);
	while(countDown==0);
	countDown=0;
	drawText("GO!",37,40,0);
	while(countDown==0);
	countDown=0;
	drawText("   ",37,40,0);
	stopInterrupt();
}

void stopInterrupt()
{
	alt_alarm_stop (&alarm);
}
