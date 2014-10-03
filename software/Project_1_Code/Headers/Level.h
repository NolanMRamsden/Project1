/*
 * Level.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "headers.h"

#ifndef LEVEL_H_
#define LEVEL_H_

typedef struct Level
{
	Ball *balls;
	Ball *balls2;
	Ball *balls3;
	BrickRow *brickRow;
	Paddle *paddle;
} Level;

static Level *level;

extern void initLevel(int lev);
extern void drawStart(Level *level);
extern void updateScore(int value);

#endif /* LEVEL_H_ */
