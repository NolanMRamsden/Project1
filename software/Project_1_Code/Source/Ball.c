/*
 * Ball.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 */
#include "../Headers/headers.h"

void startBall(Ball *ball, int x, int y, int xVelo, int yVelo)
{
	ball->x = x*100;
	ball->y = y*100;
	ball->prevX = x*100;
	ball->prevY = y*100;
	ball->xVelo = xVelo;
	ball->yVelo = yVelo;
	ball->alive = 1;
	ball->colour = 0xFFFF;
}
void nullBall(Ball *ball)
{
	ball->alive = 0;
}

void updatePosition(Ball *ball)
{
	ball->x += ball->xVelo;
	ball->y += ball->yVelo;

	int x = ball->x/100;
	int y = ball->y/100;

	//screen bounds
	if (x <= leftScreenBound)
	{
		ball->x = leftScreenBound*100;
		bounceWall(ball);
	}
	else if (x >= rightScreenBound-ballDiameter)
	{
		ball->x = rightScreenBound*100-ballDiameter*100;
		bounceWall(ball);
	}
	if (y <= topScreenBound)
	{
		ball->y = topScreenBound*100;
		bounceRoof(ball);
	}else if (y >= bottomScreenBound-ballDiameter)
	{
		ball->y = bottomScreenBound*100-ballDiameter*100;
		bounceRoof(ball);
	}

	//hit paddle
	if (ball->y >= level->paddle->y-ballDiameter*100-100
	&&  ball->y <= level->paddle->y-ballDiameter*100 + level->paddle->height*100+100)
	{
		if(ball->x >= level->paddle->x
		&& ball->x <= level->paddle->x + level->paddle->width*100
		)//&& ball->yVelo > 0)
		{
			bounceRoof(ball);
		}
	}


}

void bounceWall(Ball *ball)
{
	ball->xVelo = -ball->xVelo;
}

void bounceRoof(Ball *ball)
{
	ball->yVelo = -ball->yVelo;
}


