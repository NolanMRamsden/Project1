/*
 * Level.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "headers.h"


#ifndef LEVEL_H_
#define LEVEL_H_

/*
 * contains all the information to be accessible,
 * the paddle ball and bricks are essentially all
 * that the game logic needs
 */
typedef struct Level
{
	Buff *buff;
	Ball *ball[maxBalls];
	Brick *bricks[maxRows][bricksPerRow];
	Paddle *paddle;
	int brickCount;
} Level;

/*
 * a map of where bricks should be placed and their health values
 */
typedef struct BrickMap
{
	int brickArray[maxRows][bricksPerRow];
} BrickMap;

Level *currentLevel;
Menu currentMenu;

extern void initLevel(BrickMap brickMap);
extern void initAllBricks(Level *level, int initArray[][bricksPerRow]);
extern void drawStart(Level *level);
extern void updateScore(int value);
extern void levelLookUp(BrickMap *brickmap, int level);
extern void loadInto(BrickMap *brickmap, int map[][bricksPerRow]);
#endif /* LEVEL_H_ */
