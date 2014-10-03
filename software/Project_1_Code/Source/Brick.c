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

void initBrickRow(BrickRow *brickRow, int startHealth)
{
	int brickNum=0;
	for( brickNum=0 ; brickNum < bricksPerRow ; brickNum++)
	{
		brickRow->bricks[brickNum]=malloc(sizeof(Brick));
		initBrick(brickRow->bricks[brickNum], brickLeftStart+brickNum*(brickWidth+brickSpacing), topScreenBound+brickSpacing, startHealth);
	}
}

void hit(Brick *brick)
{
	brick->health--;
	if(brick->health < 0)
		brick->health=0;
	drawBrick(brick);
}
