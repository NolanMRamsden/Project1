/*
 * Buff.c
 *
 *  Created on: Oct 7, 2014
 *      Author: Nolan
 */
#include "../Headers/Buff.h"

void spawnBuff(Buff *buff, int x, int y, int type)
{
	buff->type = type;
	buff->x = x*100;
	buff->y = y*100;
	buff->prevX = x;
	buff->prevY = y;
	buff->xVelo = 0;
	buff->yVelo = 200;
	buff->alive = 1;
}

void hitBottom(Buff *buff)
{
	buff->alive=0;
}
