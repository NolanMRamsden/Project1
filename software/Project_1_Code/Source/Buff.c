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
	buff->yVelo = 200;
	buff->alive = 1;
}

void moveBuff(Buff *buff)
{
	if(buff->alive == 0)
		return;

	buff->x += buff->xVelo;
	buff->y += buff->yVelo;

	if (buff->y > bottomScreenBound)
		//hitBottom(buff);

	if (buff->y >= currentLevel->paddle->y-ballDiameter*100-100
	&&  buff->y <= currentLevel->paddle->y-ballDiameter*100 + currentLevel->paddle->height*100+100)
	{
		if(buff->x >= currentLevel->paddle->x - ballDiameter*100-100
		&& buff->x <= currentLevel->paddle->x + currentLevel->paddle->width*100 + 100)
		{
			switch (buff->type)
			{
				case pointsBuff:
					updateScore(100);
			}
		}
	}//end paddle logic
}

void hitBottom(Buff *buff)
{
	buff->alive=0;
}
