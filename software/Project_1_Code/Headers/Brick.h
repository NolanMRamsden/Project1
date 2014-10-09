/*
 * Brick.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#include "Buff.h"
#include "headers.h"

#ifndef BRICK_H_
#define BRICK_H_

/*
 * bricks the balls will be hitting
 */
typedef struct Brick
{
	int x;
	int y;
	int prevHealth;
	int needUpdate;
	int health;
} Brick;


extern void initBrick(Brick *brick, int x, int y, int health);
extern void hit(Brick *brick);

#endif /* BRICK_H_ */
