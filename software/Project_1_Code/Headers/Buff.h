/*
 * Buff.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Nolan
 */
#include "headers.h"

#ifndef BUFF_H_
#define BUFF_H_

typedef struct Buff
{
	int alive;
	int type;
	int x;
	int y;
	int prevX;
	int prevY;
	int xVelo;
	int yVelo;
} Buff;

extern void spawnBuff(Buff *buff, int x, int y, int type);
extern void moveBuff(Buff *buff);
extern void hitBottom(Buff *buff);

#endif /* BUFF_H_ */
