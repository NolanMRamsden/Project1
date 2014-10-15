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
	brick->isIndestructable=0;
	brick->isExplosive = 0;
	if(health==5)
		brick->isIndestructable=1;
	if (health==6)
		brick->isExplosive = 1;
}

/*
 * reduce the heatlh of the brick, note buff spawn logic should probably go here,
 * as it has the coordinates of the brick being hit
 */
void hit(Brick *brick)
{
	if(brick->isIndestructable == 1)
	{
		brick->needUpdate=1;
		return;
	}
	if(brick->health == 0)
		return;
	if (brick->isExplosive ==1)
	{
		brick->health =0;
	}else
	{
		brick->health--;
	}
	brick->needUpdate = 1;
	if(brick->health < 0)
		brick->health=0;
	if(brick->health == 0)
		if(currentLevel->buff->alive == 0)
			if(rand() % 100 < buffFrequency)
				spawnBuff(currentLevel->buff, brick->x+brickWidth/2,brick->y+brickHeight,rand()%numBuffs+1);

	currentLevel->brickCount--;
	drawBrick(brick);
}
