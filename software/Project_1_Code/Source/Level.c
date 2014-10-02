/*
 * Level.c
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "../Headers/Level.h"

void initLevel(int lev)
{
	level->balls = malloc(sizeof(Ball));
	startBall(level->balls,20,20,300,100);
	level->balls2 = malloc(sizeof(Ball));
	startBall(level->balls2,20,20,250,125);
	level->balls3 = malloc(sizeof(Ball));
	startBall(level->balls3,20,20,400,400);
	level->paddle = malloc(sizeof(Paddle));
	initPaddle(level->paddle,30);
}
