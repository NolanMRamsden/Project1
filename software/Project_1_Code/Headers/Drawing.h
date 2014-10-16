/*
 * Drawing.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#ifndef DRAWING_H_
#define DRAWING_H_

#include "headers.h"
#include "Menu.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

extern void initVGA();
extern void clearScreen();
extern void swapBuffers();
extern void clearCharacters();
extern void drawBall(Ball *ball);
extern void coverBall(int x, int y, int colour);
extern void drawPaddle(Paddle *paddle);
extern void coverPaddle(int x, int y, int width, int colour, int gunMounted);
extern void drawBrick(Brick *brick);
extern void coverBrick(int x, int y, int health);
extern void drawText(char *text, int x, int y, int selected);
extern void drawMenu(Menu menu);
extern void drawMenuText(Menu menu);
extern void drawScore(int score);
extern void drawInt(int value, int x, int y);
extern void drawAmmo(int ammo);
extern void drawBuff(Buff *buff);
extern void coverBuff(int x, int y, int type, int erase);

#endif /* DRAWING_H_ */
