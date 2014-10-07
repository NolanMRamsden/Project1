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
	int prevIndex3;
	int prevIndex2;
	int prevIndex1;
	int prevIndex0;
	int currentIndex;
	int selected;
	int max;
	int min;
	char *option[5][15];
	int *optionIndex[5];

} Menu;

extern void menuLoop();
extern void menuIndexLookUp(int index);
extern void getMenu(Menu *menu, int index, int pushToStack);

#endif /* MENU_H_ */
