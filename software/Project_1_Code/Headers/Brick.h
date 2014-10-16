/*
 * Brick.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#ifndef BRICK_H_
#define BRICK_H_

#include "Buff.h"
#include "headers.h"

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
	int isIndestructable;
	int isExplosive;
} Brick;


extern void initBrick(Brick *brick, int x, int y, int health);
extern void hit(Brick *brick);

#endif /* BRICK_H_ */
