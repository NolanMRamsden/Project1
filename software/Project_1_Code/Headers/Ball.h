/*
 * Ball.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 */
#ifndef BALL_H_
#define BALL_H_

#include "./Definitions.h"

#define ballMoveScale  1

typedef struct Ball
{
	int x;
	int y;
	int prevX;
	int prevY;
	int xVelo;
	int yVelo;
	int alive;
	int colour;
} Ball;

extern void startBall(Ball *ball, int x, int y, int xVelo, int yVelo);
extern void updatePosition(Ball *ball);
extern void bounceWall(Ball *ball);
extern void bounceRoof(Ball *ball);

#endif /* BALL_H_ */
