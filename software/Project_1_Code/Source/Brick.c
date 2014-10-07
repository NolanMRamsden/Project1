/*
 * Brick.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#include "../Headers/Brick.h"


void initBrick(Brick *brick, int x, int y, int health)
{
	brick->x = x;
	brick->y = y;
	brick->health = health;
	brick->prevHealth  = 0;
}

/*
 * reduce the heatlh of the brick, note buff spawn logic should probably go here,
 * as it has the coordinates of the brick being hit
 */
void hit(Brick *brick)
{
	brick->health--;
	if(brick->health < 0)
		brick->health=0;

	currentLevel->brickCount--;
	drawBrick(brick);
}
