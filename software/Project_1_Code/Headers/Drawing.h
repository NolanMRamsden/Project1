/*
 * Drawing.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */
#include "headers.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

#ifndef DRAWING_H_
#define DRAWING_H_

extern void initVGA();
extern void clearScreen();
extern void drawBall(Ball *ball);
extern void coverBall(int x, int y, int colour);
extern void drawPaddle(Paddle *paddle);
extern void coverPaddle(int x, int y, int width, int colour);
extern void drawText(char *text, int x, int y, int selected);
#endif /* DRAWING_H_ */
