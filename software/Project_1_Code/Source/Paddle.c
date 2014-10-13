/*
 * Paddle.c
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 */
#include "../Headers/Definitions.h"
#include "../Headers/Paddle.h"

void initPaddle(Paddle *paddle, int x)
{
	paddle->gunMounted = 0;
	paddle->gunAmmo = 0;
	paddle->x = x*100;
	paddle->y = paddleHeight*100;
	paddle->prevX = x*100;
	paddle->prevY = paddleHeight*100;
	paddle->width = paddleStartWidth;
	paddle->height = paddleThickness;
	paddle->colour = 0xFAFA;
}

void moveHorizontal(Paddle *paddle, int x)
{
	paddle->x += (x*paddleMoveScale);

	if ( paddle->x < leftScreenBound*100)
		paddle->x = leftScreenBound*100;
	else if ( paddle->x + paddle->width*100 > rightScreenBound*100 )
		paddle->x = rightScreenBound*100 - paddle->width*100;
}

