/*
 * Buff.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Nolan
 */
#ifndef BUFF_H_
#define BUFF_H_

#include "headers.h"

typedef struct Buff
{
	int alive;
	int needsErase;
	int type;
	int x;
	int y;
	int prevX;
	int prevY;
	int prev2X;
	int prev2Y;
	int xVelo;
	int yVelo;
} Buff;

extern void spawnBuff(Buff *buff, int x, int y, int type);
extern void moveBuff(Buff *buff);

#endif /* BUFF_H_ */
