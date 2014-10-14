/*
 * Drawing.c
 *
 *  Created on: Sep 25, 2014
 *      Author: William
 */

#include "../Headers/Drawing.h"

static alt_up_pixel_buffer_dma_dev* pixel_buffer;
static alt_up_char_buffer_dev *char_buffer;


void initVGA()
{
	pixel_buffer = malloc(sizeof(alt_up_pixel_buffer_dma_dev));
	char_buffer  = malloc(sizeof(alt_up_char_buffer_dev));
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

	unsigned int pixel_buffer_addr1 = PIXEL_BUFFER_BASE;
	unsigned int pixel_buffer_addr2 = PIXEL_BUFFER_BASE + (512 * 240 * 2);

	// Set the background buffer address – Although we don’t use the
	//background,
	// they only provide a function to change the background
	// buffer address, so
	// we must set that, and then swap it to the foreground.
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer, pixel_buffer_addr1);
	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	// Wait for the swap to complete
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer, pixel_buffer_addr2);

	// Initialize character buffer
	char_buffer = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);

	clearScreen();
}

void swapBuffers()
{
	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	// Wait for the swap to complete
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
}

void clearScreen()
{
	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, topScreenBound-1,rightScreenBound+1, topScreenBound-1, screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, topScreenBound-1, 0, bottomScreenBound+1,screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, rightScreenBound+1, bottomScreenBound+1,rightScreenBound+1, topScreenBound-1, screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, rightScreenBound+1, bottomScreenBound+1, 0,bottomScreenBound+1, screenOutline, 1);
	swapBuffers();
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, topScreenBound-1,rightScreenBound+1, topScreenBound-1, screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, topScreenBound-1, 0, bottomScreenBound+1,screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, rightScreenBound+1, bottomScreenBound+1,rightScreenBound+1, topScreenBound-1, screenOutline, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, rightScreenBound+1, bottomScreenBound+1, 0,bottomScreenBound+1, screenOutline, 1);

}

void clearCharacters()
{
	alt_up_char_buffer_clear(char_buffer);
}

void drawBall(Ball *ball)
{
	int colour = ball->colour;
	int x      = ball->x/100;
	int y      = ball->y/100;

	coverBall(ball->prev2X,ball->prev2Y,background);


	if(ball->alive == 0)
		return;

	coverBall(x,y,colour);
	ball->prev2X = ball->prevX;
	ball->prev2Y = ball->prevY;

	ball->prevX=x;
	ball->prevY=y;
}

void coverBall(int x, int y, int colour)
{
	if (colour == background)
	{
		//Following lines draw the ball in give color
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y,x+4, y, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+1,x+5, y+1, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+6, y+2, background,1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+6, y+3, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+6, y+4, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+5,x+5, y+5, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+6,x+4, y+6, background, 1);
	}
	else
	{
		//Steel Ball Pattern
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y,x+4, y, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+1,x+5, y+1, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+6, y+2, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+6, y+3, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+6, y+4, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+5,x+5, y+5, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+6,x+4, y+6, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, y,x+6, y+3, White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+4, y,x+6, y+2, White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+3, y+6, DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+2, y+6, DarkGrey, 1);
	}
}

void drawPaddle(Paddle *paddle)
{
	int colour = paddle->colour;
	int x      = paddle->x/100;
	int y      = paddle->y/100;
	int width  = paddle->prevWidth2;
	int gunMounted = paddle->gunMounted;
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, paddle->prev2X, paddle->prev2Y,paddle->prev2X+width-1, paddle->prev2Y, background, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, paddle->prev2X, paddle->prev2Y+1,paddle->prev2X+width-1, paddle->prev2Y+1, background, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, paddle->prev2X, paddle->prev2Y+2,paddle->prev2X+width-1, paddle->prev2Y+2, background, 1);

	if (paddle->gunMounted == 1)//erase gun
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, paddle->prev2X+width/2, paddle->prev2Y-3,paddle->prev2X+width/2, paddle->prev2Y-1, background, 1);
	}

	coverPaddle(x,y,paddle->width,colour,gunMounted);
	paddle->prev2X = paddle->prevX;
	paddle->prev2Y = paddle->prevY;
	paddle->prevX=x;
	paddle->prevY=y;
	paddle->prevWidth2 = paddle->prevWidth;
	paddle->prevWidth=paddle->width;
}

void coverPaddle(int x, int y, int width, int colour, int gunMounted)
{
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+1, y, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+1, y+1, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+1, y+2, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+width-2, y,x+width-1, y, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+width-2, y+1,x+width-1, y+1, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+width-2, y+2,x+width-1, y+2, Red, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y,x+width-3, y, White, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+1,x+width-3, y+1, LightGrey, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+2,x+width-3, y+2, DarkGrey, 1);

	if (gunMounted == 1) //draw Gun
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+width/2, y-3,x+width/2, y-1,Red , 1);

	}


}

void drawBrick (Brick *brick)
{
	coverBrick(brick->x,brick->y,0);
	if(brick->prevHealth == brick->health || brick->health==0)
		return;

	coverBrick(brick->x,brick->y,brick->health);

	brick->prevHealth = brick->health;
}

void coverBrick(int x, int y, int health)
{
	if (health == 6) {
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+18, y, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+18, y+1, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+18, y+2, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+18, y+3, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+18, y+4, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+18, y+5, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+18, y+6, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+18, y+7, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+1,x+5, y+1, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+13, y+1,x+17, y+1, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, y+2,x+3, y+6, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+15, y+2,x+15, y+6, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, y+1,x+7, y+6, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+11, y+1,x+11, y+6, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, y+1,x+11, y+6, Red, 1);







	}

	else if(health == 5)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+18, y, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+18, y+1, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+18, y+2, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+18, y+3, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+18, y+4, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+18, y+5, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+18, y+6, Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+18, y+7, Maroon, 1);
	}
	else if (health==3)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+5, y , LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, y,x+18, y, White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+13, y+1 , LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+14, y+1,x+18, y+1 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x, y+2 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+2,x+15, y+2, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+16, y+2,x+18, y+2 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x, y+3 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+3,x+16, y+3, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+17, y+3,x+18, y+3 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+1, y+4 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+4,x+17, y+4, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+4,x+18, y+4 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+2, y+5 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, y+5,x+17, y+5, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+5,x+18, y+5 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+4, y+6 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, y+6,x+18, y+6, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+11, y+7 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+12, y+7,x+18, y+7, LightGrey, 1);
	}
	else if (health==2)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+5, y , LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, y,x+18, y, White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+13, y+1 , LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+14, y+1,x+18, y+1 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x, y+2 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+2,x+15, y+2, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+16, y+2,x+18, y+2 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x, y+3 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+3,x+16, y+3, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+17, y+3,x+18, y+3 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+1, y+4 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+4,x+17, y+4, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+4,x+18, y+4 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+2, y+5 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, y+5,x+17, y+5, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+5,x+18, y+5 , White, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+4, y+6 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, y+6,x+18, y+6, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+11, y+7 , DarkGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+12, y+7,x+18, y+7, LightGrey, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+8, y,x+8, y+4, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+9, y+3,x+11, y+3, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+7, y+4,x+7, y+4, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+11, y+4,x+11, y+4, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, y+5,x+6, y+5, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+11, y+5,x+12, y+5, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, y+6,x+6, y+6, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+12, y+6,x+12, y+6, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+13, y+7,x+13, y+7, background, 1);
	}
	else if (health==1)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+5, y , Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+6, y,x+18, y, Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+13, y+1 , Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+14, y+1,x+18, y+1 , Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x, y+2 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+2,x+15, y+2, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+16, y+2,x+18, y+2 , Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x, y+3 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+3,x+16, y+3, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+17, y+3,x+18, y+3 , Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+1, y+4 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+4,x+17, y+4, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+4,x+18, y+4 , Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+2, y+5 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+3, y+5,x+17, y+5, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+18, y+5,x+18, y+5 , Red-25, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+4, y+6 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+5, y+6,x+18, y+6, Red, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+11, y+7 , Maroon, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+12, y+7,x+18, y+7, Red, 1);
	}else
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y,x+18, y, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+1,x+18, y+1, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+18, y+2, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+18, y+3, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+18, y+4, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+5,x+18, y+5, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+6,x+18, y+6, background, 1);
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+7,x+18, y+7, background, 1);
	}
}

void drawText(char *text, int x, int y, int selected)
{
	if(selected)
		alt_up_char_buffer_string(char_buffer,"-> ",x-3,y);
	else
		alt_up_char_buffer_string(char_buffer,"  ",x-3,y);

	alt_up_char_buffer_string(char_buffer,text,x,y);
}

void drawMenu(Menu menu)
{
	int i;
	int difference = (bottomScreenBound-menuOffset)-(topScreenBound+menuOffset);
	for( i = topScreenBound+menuOffset; i<topScreenBound+menuOffset+difference*(menu.max+1)/5; i++)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, leftScreenBound+menuOffset, i,rightScreenBound-menuOffset, i, menuBG, 0);
	}

	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, leftScreenBound+menuOffset+1, topScreenBound+menuOffset+1 ,rightScreenBound-menuOffset-1, topScreenBound+menuOffset+1 , menuHighlight, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, leftScreenBound+menuOffset+1, topScreenBound+menuOffset+difference*(menu.max+1)/5-1 ,rightScreenBound-menuOffset-1, topScreenBound+menuOffset+difference*(menu.max+1)/5-1 , menuHighlight, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, leftScreenBound+menuOffset+1, topScreenBound+menuOffset+1 ,leftScreenBound+menuOffset+1, topScreenBound+menuOffset+difference*(menu.max+1)/5-1 , menuHighlight, 0);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, rightScreenBound-menuOffset-1, topScreenBound+menuOffset+1 ,rightScreenBound-menuOffset-1, topScreenBound+menuOffset+difference*(menu.max+1)/5-1 , menuHighlight, 0);

	drawMenuText(menu);
}

void drawMenuText(Menu menu)
{
	clearCharacters();
	int i;
	for( i = 0 ; i<=menu.max;i++)
	{
		int selected=0;
		if(i==menu.selected)
			selected=1;
		drawText(menu.option[i],33,21+4*i,selected);
	}
}

void drawScore(int score)
{
	char *str = malloc(sizeof(char));
	sprintf(str,"%d  ",score);
	drawText(str,1,1,0);
}

void drawAmmo(int ammo)
{
	char *str = malloc(sizeof(char));
	sprintf(str,"Ammo: %d  ",ammo);
	drawText(str,73,1,0);
}

void drawBuff(Buff *buff)
{
	coverBuff(buff->prev2X,buff->prev2Y,-1);
	if(buff->alive == 1)
		coverBuff(buff->x/100,buff->y/100,buff->type);

	buff->needsErase--;
	buff->prev2X=buff->prevX;
	buff->prev2Y=buff->prevY;
	buff->prevX=buff->x/100;
	buff->prevY=buff->y/100;
}

void coverBuff(int x, int y, int type)
{
	int colour = background;
	if(type == -1)
	{
		colour=background;
	}else if (type == widthMinusBuff)
	{
		colour = Red;
	}else if (type == widthPlusBuff)
	{
		colour = Green;
	}else if (type == pointsBuff)
	{
		colour = Cyan;
	}else if (type == gunBuff)
	{
		colour = Magenta;
	}
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y,x+4, y, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+1,x+5, y+1, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+2,x+6, y+2, colour,1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+3,x+6, y+3, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+4,x+6, y+4, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+1, y+5,x+5, y+5, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x+2, y+6,x+4, y+6, colour, 1);
}
