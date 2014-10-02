/*
 * Definitions.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Nolan
 *
 *      Defines memory location for IO
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define switches   (volatile char*)   0x00004030
#define leds       (volatile char*)   0x00004020
#define pushbutton (volatile char*)   0x00004000
#define NULL       ((void*)0)

//screen bounds
#define leftScreenBound   1
#define rightScreenBound  318
#define topScreenBound    1
#define bottomScreenBound 238
#define screenRefreshRate 120

//colours
#define background        0x0000
#define screenOutline     0x0201

//logic values
#define ballDiameter      7
#define paddleThickness   5

//game state constants
#define Playing 0
#define Paused  1
#define Menu    2

//paddle shit
#define paddleMoveScale   100
#define paddleHeight      220
#define paddleStartWidth  60


#endif /* DEFINITIONS_H_ */
