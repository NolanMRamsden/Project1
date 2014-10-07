/*
 * Input.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#include "../Headers/Input.h"
#include "../Headers/Definitions.h"
#include "io.h"


const int scalars[4] = {10,5,-5,-10};

/*
 * return a scalar from -10 to 10 for paddle speed movement
 */
int getUserInput()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if( ((IORD_8DIRECT(pushbutton,0) >> i) & 1) == 0)
			return scalars[i];
	}
	return 0;
}
/*
 * returns the lowest index of a triggered switch
 */
int getSwitchIndex()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if( ((IORD_8DIRECT(switches,0) >> i) & 1) == 1)
			return i;
	}
	return -1;
}

void turnOnLED(int index)
{
	if (index > 8 || index < 0)
		return;
	IOWR_8DIRECT(leds,0,IORD_8DIRECT(leds,0) | (1 << index));
}

void turnOffLED(int index)
{
	if (index > 8 || index < 0)
		return;
	IOWR_8DIRECT(leds,0,IORD_8DIRECT(leds,0) & (256 & ~(1<<index)));
}
