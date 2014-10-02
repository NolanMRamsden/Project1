/*
 * Brick.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#include "../Headers/Brick.h"

const int brickHeight=10;
const int brickWidth=50;
const int startBrickHealth=1;

void initBrick(Brick *brick, int x, int y)
{
	brick->x = x;
	brick->y = y;
	brick->width  = brickWidth;
	brick->height = brickHeight;
	brick->health = startBrickHealth;
	brick->prevHealth  = startBrickHealth;
}

void hit(Brick *brick)
{
	brick->health--;
	if(brick->health < 0)
		brick->health=0;
}
