/*
 * Brick.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Nolan
 */
#include "../Headers/Brick.h"



void initBrick(Brick *brick, int x, int y, int health)
{
	brick->needUpdate = 0;
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
	brick->needUpdate = 1;
	brick->health--;
	if(brick->health < 0)
		brick->health=0;
	if(brick->health == 0)
		if(currentLevel->buff->alive == 0)
			if(rand() % 100 < buffFrequency)
				spawnBuff(currentLevel->buff, brick->x+brickWidth/2,brick->y+brickHeight,rand()%numBuffs+1);

	currentLevel->brickCount--;
	drawBrick(brick);
}
