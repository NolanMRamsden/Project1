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
	ball->prevX = ball->prev2X = x;
	ball->prevY = ball->prev2Y = y;
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
	if(ball->alive == 0)
			return;

	ball->x += ball->xVelo;
	ball->y += ball->yVelo;

	int x = ball->x/100;
	int y = ball->y/100;

	//screen bounds
	if (x <= leftScreenBound)
	{
		ball->x = leftScreenBound*100+100;
		bounceWall(ball);
	}
	else if (x >= rightScreenBound-ballDiameter)
	{
		ball->x = rightScreenBound*100-ballDiameter*100-100;
		bounceWall(ball);
	}
	if (y <= topScreenBound-1)
	{
		ball->y = topScreenBound*100+100;
		bounceRoof(ball);
	}else if (y >= bottomScreenBound-ballDiameter)
	{
		ball->y = bottomScreenBound*100-ballDiameter*100-100;
		bounceRoof(ball);
		updateScore(-1);
	}//end screen bounds

	//hit paddle
	if(ball->yVelo > 0)
		if (ball->y >= currentLevel->paddle->y-ballDiameter*100-100
		&&  ball->y <= currentLevel->paddle->y-ballDiameter*100 + currentLevel->paddle->height*100+100)
		{
			if(ball->x >= currentLevel->paddle->x - ballDiameter*100-100
			&& ball->x <= currentLevel->paddle->x + currentLevel->paddle->width*100 + 100)
			{
				//mapped the paddle to a pyramid, we can improve this logic later
				ball->xVelo += ((ball->x+ballDiameter*50)-(currentLevel->paddle->x+currentLevel->paddle->width*50))/paddleBounceScale;
				bounceRoof(ball);
			}
		}//end paddle logic

	//hit brick

	int i,j;
	int hasBounced=0;
	for(i=0;i<maxRows;i++)
	{
		if (y + ballDiameter >= currentLevel->bricks[i][0]->y
		&&  y <= currentLevel->bricks[i][0]->y + brickHeight ) //see if we can cut out a whole row of processing
		{
			for(j=0;j<bricksPerRow;j++)
			{
				Brick brick = *currentLevel->bricks[i][j];
				if(brick.health > 0)                          //dont bother if brick is dead
				{
					if(x + ballDiameter >= brick.x
					&& x <= brick.x + brickWidth )
					{
						if(hasBounced==0)  //buffer double bounces
						{
							//we use the previous value of the ball to tell which side it hit
							if(ball->prevY > brick.y + brickHeight)
							{
								bounceRoof(ball);
								ball->y = (brick.y+brickHeight)*100+100;
							} else if(ball->prevY < brick.y-ballDiameter)
							{
								bounceRoof(ball);
								ball->y = (brick.y-ballDiameter)*100-100;
							} else if(ball->prevX + ballDiameter < brick.x)
							{
								bounceWall(ball);
								ball->x = (brick.x-ballDiameter)*100-100;
							} else if(ball->prevX > brick.x+brickWidth)
							{
								bounceWall(ball);
								ball->x = (brick.x+brickWidth)*100+100;
							} else if (brick.isIndestructable)
							{
								ball->y = (brick.y+brickHeight)*100+100;
							}
						}
						hasBounced=1;
						updateScore(3);
						if (brick.isExplosive)
						{
							hit(currentLevel->bricks[i-1][j-1]);
							hit(currentLevel->bricks[i-1][j]);
							hit(currentLevel->bricks[i-1][j+1]);
							hit(currentLevel->bricks[i][j-1]);
							hit(currentLevel->bricks[i][j]);
							hit(currentLevel->bricks[i][j+1]);
							hit(currentLevel->bricks[i+1][j-1]);
							hit(currentLevel->bricks[i+1][j]);
							hit(currentLevel->bricks[i+1][j+1]);
						}
						else
						{
							hit(currentLevel->bricks[i][j]);
						}

					}
				}
			}
		}
	}//end brick logic
}

void bounceWall(Ball *ball)
{
	ball->xVelo = -ball->xVelo;
}

void bounceRoof(Ball *ball)
{
	ball->yVelo = -ball->yVelo;
}


