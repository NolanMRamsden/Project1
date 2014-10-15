/*
 * Buff.c
 *
 *  Created on: Oct 7, 2014
 *      Author: Nolan
 */
#include "../Headers/Buff.h"

void spawnBuff(Buff *buff, int x, int y, int type)
{
	buff->type = type;
	buff->x = x*100;
	buff->y = y*100;
	buff->prevX = x;
	buff->prevY = y;
	buff->xVelo = 0;
	buff->yVelo = 50 + rand()%100;
	buff->alive = 1;
}

void moveBuff(Buff *buff)
{
	if(buff->alive == 0)
		return;

	buff->x += buff->xVelo;
	buff->y += buff->yVelo;

	//redraw bricks buff is touching
	int i;
	int xbrick = (int)((buff->x/100-leftScreenBound)/(brickWidth+brickSpacing));
	if(xbrick >= 0 && xbrick < bricksPerRow)
		for(i=0;i<maxRows;i++)
			currentLevel->bricks[i][xbrick]->needUpdate=1;

	if (buff->y+ ballDiameter*100+100 > bottomScreenBound*100)
	{
		buff->alive=0;
		buff->needsErase=2;
	}

	if (buff->y >= currentLevel->paddle->y-ballDiameter*100-100
	&&  buff->y <= currentLevel->paddle->y-ballDiameter*100 + currentLevel->paddle->height*100+100)
	{
		if(buff->x >= currentLevel->paddle->x - ballDiameter*100-100
		&& buff->x <= currentLevel->paddle->x + currentLevel->paddle->width*100 + 100)
		{
			// Increment the buffs statistic
			if(buff->type != widthMinusBuff)
			{
				incrementBuffsCaught(1);
			}
			switch (buff->type)
			{
				case pointsBuff:
					updateScore(100);
					break;
				case widthPlusBuff:
					currentLevel->paddle->width+= 20;
					if(currentLevel->paddle->width > paddleMaxWidth)
						currentLevel->paddle->width = paddleMaxWidth;
					break;
				case widthMinusBuff:
					currentLevel->paddle->width-= 20;
					if(currentLevel->paddle->width < paddleMinWidth)
						currentLevel->paddle->width = paddleMinWidth;
					break;
				case gunBuff:
					currentLevel->paddle->gunMounted=1;
					currentLevel->paddle->gunAmmo+=1;
					if(currentLevel->paddle->gunAmmo > maxAmmo)
						currentLevel->paddle->gunAmmo=maxAmmo;
					break;
			}
			buff->alive=0;
			buff->needsErase=2;
		}
	}//end paddle logic
}
