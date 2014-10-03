/*
 * Level.c
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "../Headers/Level.h"

int score;

void initLevel(int lev)
{
	//level=malloc(sizeof(Level));

	level->balls = malloc(sizeof(Ball));
	startBall(level->balls,40,40,200,100);
	level->balls2 = malloc(sizeof(Ball));
	startBall(level->balls2,40,40,200,200);
	level->balls3 = malloc(sizeof(Ball));
	startBall(level->balls3,40,40,100,100);

	level->paddle = malloc(sizeof(Paddle));
	initPaddle(level->paddle,30);

	level->brickRow = malloc(sizeof(BrickRow));
	initBrickRow(level->brickRow,lev);




	score = 0;
}


void drawStart(Level *level)
{
	drawBall(level->balls);
	drawBall(level->balls2);
	drawBall(level->balls3);
	drawPaddle(level->paddle);
	drawScore(score);
	drawText("BRICK BREAKER",34,1,0);

	int i=0;
	for(i=0;i<bricksPerRow;i++)
	{
		level->brickRow->bricks[i]->prevHealth=-3;
		drawBrick(level->brickRow->bricks[i]);
	}
}

void updateScore(int value)
{
	score+=value;
	drawScore(score);
}
