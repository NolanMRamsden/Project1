/*
 * Level.c
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "../Headers/Level.h"
#include "../Headers/Brick.h"
#include <stdlib.h>


int score;

/*
 * initiliaze all coordinate and health aspects of the level
 * based on brickmap being fed
 */
void initLevel(BrickMap brickMap)
{
	int i=0,j=0;
	for(i=0;i<maxBalls;i++)
	{
		currentLevel->ball[i] = malloc(sizeof(Ball));
	}
	currentLevel->paddle = malloc(sizeof(Paddle));
	initAllBricks(currentLevel,brickMap.brickArray);

	int rowHit=0;
	for(i=maxRows-1;i>=0;i--)
	{
		for(j=0;j<bricksPerRow;j++)
			if(currentLevel->bricks[i][j]->health > 0)
			{
				if (rowHit == 0)
					rowHit=i+2;
			}
	}

	initPaddle(currentLevel->paddle,30);
	startBall(currentLevel->ball[0],40,topScreenBound+(brickHeight+brickSpacing)*rowHit+brickHeight*1.2,200,200);
	startBall(currentLevel->ball[1],60,topScreenBound+(brickHeight+brickSpacing)*rowHit+brickHeight*1.2,200,200);
	startBall(currentLevel->ball[2],80,topScreenBound+(brickHeight+brickSpacing)*rowHit+brickHeight*1.2,200,200);

	score = 0;
	currentLevel->brickCount=0;
	for(i=0;i<maxRows;i++)
	{
		for(j=0;j<bricksPerRow;j++)
			currentLevel->brickCount += brickMap.brickArray[i][j];
	}
}

/*
 * draw a static image of the level being passed (briks, paddle and ball)
 */
void drawStart(Level *level)
{
	int i=0;
	int j=0;
	for(j=0;j<maxRows;j++)
	{
		for(i=0;i<bricksPerRow;i++)
		{
			level->bricks[j][i]->prevHealth=-3;
			drawBrick(currentLevel->bricks[j][i]);
		}
	}

	for(i=0;i<maxBalls;i++)
	{
		if(level->ball[i]->alive)
			drawBall(level->ball[i]);
	}


	drawPaddle(level->paddle);
	drawScore(score);
	drawText("BRICK BREAKER",34,1,0);

}

void initAllBricks(Level *level, int initArray[][bricksPerRow])
{
	int i,j;
	for(i=0;i<maxRows;i++)
		for(j=0;j<bricksPerRow;j++)
		{
			level->bricks[i][j]=malloc(sizeof(Brick));
			initBrick(level->bricks[i][j], brickLeftStart+j*(brickWidth+brickSpacing), topScreenBound+brickSpacing+(brickHeight+brickSpacing)*(i), initArray[i][j]);
		}
}

void updateScore(int value)
{
	score+=value;
	drawScore(score);
}
/*
 * pre build level farm, note 0 will produce a random level
 */
void levelLookUp(BrickMap *brickMap, int level)
{
	if(level == 0)
	{
		int brickArray[maxRows][bricksPerRow];
		int i,j;
		for(i=0;i<maxRows;i++)
			for(j=0;j<bricksPerRow;j++)
				brickArray[i][j]=(int)rand()%4;

		loadInto(brickMap,brickArray);
	}
	else if(level == -1)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}
	else if(level == 1)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}else if(level == 2)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{1,1,3,1,3,1,3,1,3,1,3,1,3,1,1},
			{1,2,1,2,1,2,1,2,1,2,1,2,1,2,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}else if(level == 3)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,1,1,1,1,1,0,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}else if(level == 4)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,3,3,3,3,3,3,3,3,3,3,3,3,3,0},
			{0,3,2,2,2,2,2,2,2,2,2,2,2,3,0},
			{0,3,2,1,1,1,1,1,1,1,1,1,2,3,0},
			{0,3,2,1,0,0,0,0,0,0,0,1,2,3,0},
			{0,3,2,1,0,0,0,0,0,0,0,1,2,3,0},
			{0,3,2,1,1,1,1,1,1,1,1,1,2,3,0},
			{0,3,2,2,2,2,2,2,2,2,2,2,2,3,0},
			{0,3,3,3,3,3,3,3,3,3,3,3,3,3,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}else if(level == 5)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0},
			{0,3,0,3,0,2,0,1,0,2,0,3,0,3,0}
		};
		loadInto(brickMap,brickArray);
	}else if(level == 6)
	{
		int brickArray[maxRows][bricksPerRow] =
		{
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,3,3,3,3,3,0,3,3,3,3,3,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		loadInto(brickMap,brickArray);
	}
}

void loadInto(BrickMap *brickmap, int map[][bricksPerRow])
{
	int i,j;
	for(i=0;i<maxRows;i++)
		for(j=0;j<bricksPerRow;j++)
			brickmap->brickArray[i][j]= map[i][j];
}
