/*
 * Menu.h
 *
 *  Created on: Sep 30, 2014
 *      Author: Karen
 */
#include "headers.h"
#include "Input.h"

#ifndef MENU_H_
#define MENU_H_

typedef struct Menu
{
	int selected;
	int max;
	int min;
	char *option[5][15];

} Menu;

extern void menuLoop(Menu *menu);
extern void getMenu(Menu *menu, int index);

#endif /* MENU_H_ */
