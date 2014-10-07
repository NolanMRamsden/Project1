/*
 * Menu.c
 *
 *  Created on: Sep 30, 2014
 *      Author: Karen
 */
#include "../Headers/Menu.h"

/*
 * abstract menu loop that executes tied commands when left key is pressed
 */
void menuLoop()
{
	int press = getUserInput();

	if(press == -5)
	{
		while(getUserInput() != 0);
		currentMenu.selected--;
		if(currentMenu.selected < currentMenu.min)
			currentMenu.selected = currentMenu.min;
		clearCharacters();
		drawMenuText(currentMenu);
	}
	else if(press == 5)
	{
		while(getUserInput() != 0);
		currentMenu.selected++;
		if(currentMenu.selected > currentMenu.max)
			currentMenu.selected = currentMenu.max;
		clearCharacters();
		drawMenuText(currentMenu);
	}else if(press == -10)
	{
		while(getUserInput() != 0);
		menuIndexLookUp(currentMenu.optionIndex[currentMenu.selected]);
	}
}
/*
 * the actual execution of tied commands
 */
void menuIndexLookUp(int index)
{
	switch (index)
	{
		case -2:   //exit to main
			changeState(Playing);
			return;

		case -1:  //previous menu
			currentMenu.currentIndex = currentMenu.prevIndex0;
			currentMenu.prevIndex0 = currentMenu.prevIndex1;
			currentMenu.prevIndex1 = currentMenu.prevIndex2;
			currentMenu.prevIndex2 = currentMenu.prevIndex3;
			getMenu(&currentMenu, currentMenu.currentIndex, 0);
			drawMenuText(currentMenu);
			return;

		case 1:   //resume playing
			changeState(Playing);
			return;

		case 2:
			getMenu(&currentMenu,profileMenu,1);
			drawMenuText(currentMenu);
			return;

		case 3:   //switch to settings menu
			getMenu(&currentMenu,settingsMenu,1);
			drawMenuText(currentMenu);
			return;

		case 4:   //switch to settings menu
			getMenu(&currentMenu,scoreMenu,1);
			drawMenuText(currentMenu);
			return;
	}
}

/*
 * menu farm look up (optional to push this menu onto the menu stack for returning
 */
void getMenu(Menu *menu, int index, int pushToStack)
{
	if(pushToStack == 1)
	{
		menu->prevIndex3 = menu->prevIndex2;
		menu->prevIndex2 = menu->prevIndex1;
		menu->prevIndex1 = menu->prevIndex0;
		menu->prevIndex0 = menu->currentIndex;
		menu->currentIndex = index;
	}

	//most menus will have a default up menu option (*can override this ie rootmenu)
	sprintf(menu->option[4],"     Return");
	menu->optionIndex[4] = -1;  //up menu

	if(index == rootMenu)
	{
		sprintf(menu->option[0],"    Main Menu");
		sprintf(menu->option[1],"     Resume");
		sprintf(menu->option[2],"     Profile");
		sprintf(menu->option[3],"     Settings");
		sprintf(menu->option[4],"      Exit");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 1;  //resume
		menu->optionIndex[2] = 2;
		menu->optionIndex[3] = 3;
		menu->optionIndex[4] = 0;  //exit
	}else if (index == pauseMenu)
	{
		sprintf(menu->option[0],"  Pause Menu");
		sprintf(menu->option[1],"    Resume");
		menu->min=1;
		menu->max=1;
		menu->selected=1;
		menu->optionIndex[1] = 1;  //resume
	}else if(index == settingsMenu)
	{
		sprintf(menu->option[0],"  Settings Menu");
		sprintf(menu->option[1],"     Volume");
		sprintf(menu->option[2],"   Game Speed");
		sprintf(menu->option[3],"     Scores");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 0;
		menu->optionIndex[2] = 0;
		menu->optionIndex[3] = 4;
	}
	else if(index == scoreMenu)
	{
		sprintf(menu->option[0],"   High Scores");
		sprintf(menu->option[1],"     NOLAN");
		sprintf(menu->option[2],"     JOSH");
		sprintf(menu->option[3],"    CHARLIE");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 0;
		menu->optionIndex[2] = 0;
		menu->optionIndex[3] = 0;
	}else if(index == profileMenu)
	{
		sprintf(menu->option[0],"    Profiles");
		sprintf(menu->option[1],"      Save");
		sprintf(menu->option[2],"      Load");
		sprintf(menu->option[3],"     Delete");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 0;
		menu->optionIndex[2] = 0;
		menu->optionIndex[3] = 0;
	}
	else
	{
		sprintf(menu->option[0],"Bad Menu");
		menu->min=0;
		menu->max=0;
		menu->selected=-1;
	}
}

