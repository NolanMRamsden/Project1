/*
 * Level.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "../Headers/headers.h"

#ifndef LEVEL_H_
#define LEVEL_H_

typedef struct Level
{
	Ball *balls;
	Ball *balls2;
	Ball *balls3;
	Brick *bricks[10];
	Paddle *paddle;
} Level;

static Level *level;

extern void initLevel(int lev);

#endif /* LEVEL_H_ */
