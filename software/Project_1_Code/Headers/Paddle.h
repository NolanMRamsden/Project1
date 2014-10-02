/*
 * Paddle.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 */
#include "../Headers/Definitions.h"

#ifndef PADDLE_H_
#define PADDLE_H_

typedef struct Paddle
{
	float x;
	float y;
	int prevX;
	int prevY;
	int width;
	int height;
	int colour;

} Paddle;

extern void initPaddle(Paddle *paddle, int x);
extern void moveHorizontal(Paddle *paddle, int x);


#endif /* PADDLE_H_ */
