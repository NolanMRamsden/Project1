/*
 * Brick.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */

#ifndef BRICK_H_
#define BRICK_H_



typedef struct Brick
{
	int x;
	int y;
	int width;
	int height;
	int prevHealth;
	int health;
} Brick;

extern void initBrick(Brick *brick, int x, int y);
extern void hit(Brick *brick);

#endif /* BRICK_H_ */
