/*
 * Paddle.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#include "../Headers/Definitions.h"

/*
 * the players paddle
 */
typedef struct Paddle
{
	float x;
	float y;
	int prevX;
	int prevY;
	int prev2X;
	int prev2Y;
	int gunAmmo;
	int gunMounted;
	int prevWidth2;
	int prevWidth;
	int width;
	int height;
	int colour;

} Paddle;

extern void initPaddle(Paddle *paddle, int x);
extern void moveHorizontal(Paddle *paddle, int x);


#endif /* PADDLE_H_ */
