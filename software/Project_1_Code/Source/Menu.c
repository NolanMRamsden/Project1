/*
 * Menu.c
 *
 *  Created on: Sep 30, 2014
 *      Author: Karen
 */
#include "../Headers/Menu.h"

void menuLoop(Menu *menu)
{
	int press = getUserInput();

	if(press == -5)
	{
		while(getUserInput() != 0);
		menu->selected--;
		if(menu->selected < menu->min)
			menu->selected = menu->min;
	}
	else if(press == 5)
	{
		while(getUserInput() != 0);
		menu->selected++;
		if(menu->selected > menu->max)
			menu->selected = menu->max;
	}

	if(press != 0)
		drawMenu(menu);
}

void getMenu(Menu *menu, int index)
{
	if(index == rootMenu)
	{
		sprintf(menu->option[0],"    Main Menu");
		sprintf(menu->option[1],"     Resume");
		sprintf(menu->option[2],"      Load");
		sprintf(menu->option[3],"      Save");
		sprintf(menu->option[4],"     test5");
		menu->min=0;
		menu->max=4;
		menu->selected=1;
	}else if (index == pauseMenu)
	{
		sprintf(menu->option[1],"    Resume");
		sprintf(menu->option[0],"    Paused");
		menu->min=1;
		menu->max=1;
		menu->selected=1;
	}else
	{
		sprintf(menu->option[0],"Bad Menu");
		menu->min=0;
		menu->max=0;
		menu->selected=-1;
	}
}

