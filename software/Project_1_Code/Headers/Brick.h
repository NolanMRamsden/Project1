/*
 * Brick.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */

#include "Definitions.h"

#ifndef BRICK_H_
#define BRICK_H_

typedef struct Brick
{
	int x;
	int y;
	int prevHealth;
	int health;
} Brick;

typedef struct BrickRow
{
	Brick *bricks[bricksPerRow];
} BrickRow;

extern void initBrick(Brick *brick, int x, int y, int health);
extern void initBrickRow(BrickRow *brickRow, int startHealth);
extern void hit(Brick *brick);

#endif /* BRICK_H_ */
