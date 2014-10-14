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
#define rightScreenBound  317
#define topScreenBound    15
#define bottomScreenBound 238
#define screenRefreshRate 120

//colours
#define background        0x0000
#define screenOutline     0xFFFF
#define topBanner         0xFFFF

//game state constants
#define Playing        0
#define Paused         1
#define MenuShow       2
#define pauseMenu      10
#define rootMenu       11
#define settingsMenu   12
#define profileMenu    13
#define scoreMenu      14
#define loadprofileMenu 15
#define editprofile1Menu 16
#define editprofile2Menu 17
#define editprofile3Menu 18

//Menu stuff
#define menuOffset     50
#define menuBG         0x7BEF
#define menuHighlight  0xC618

//paddle shit
#define paddleMoveScale   100
#define paddleHeight      220
#define paddleStartWidth  60
#define paddleThickness   5
#define paddleBounceScale 70
#define paddleMaxWidth    100
#define paddleMinWidth    20
#define maxAmmo           10

//ball stuff
#define ballDiameter      7
#define maxBalls          3

//brick stuff
#define bricksPerRow      15
#define brickHeight       8
#define brickWidth        19
#define brickSpacing      2
#define brickLeftStart    4
#define maxRows           10

//buff stuff
#define pointsBuff        1
#define widthPlusBuff     2
#define widthMinusBuff    3
#define gunBuff           4
#define numBuffs          4
#define buffFrequency     100

//colours
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */

#endif /* DEFINITIONS_H_ */
