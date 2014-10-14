/*
 * Menu.c
 *
 *  Created on: Sep 30, 2014
 *      Author: Karen
 */
#include "../Headers/Menu.h"
#include "../Headers/Profile.h"
#include <string.h>

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
	}
	if(getMenuPB())
	{
		while(getMenuPB() != 0);
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
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}

			getMenu(&currentMenu,profileMenu,1);
			drawMenuText(currentMenu);
			return;

		case 3:   //switch to settings menu
			getMenu(&currentMenu,settingsMenu,1);
			drawMenuText(currentMenu);
			return;

		case 4:   //switch to settings menu
			getMenu(&currentMenu,settingsMenu,1);
			drawMenuText(currentMenu);
			return;

		case 5: // Root of the profile management
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			if(profile_1 == NULL)
			{
				initProfiles();
			}
			getMenu(&currentMenu, loadprofileMenu, 1);
			drawMenuText(currentMenu);
			return;

		case 6: // Profile 1
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			if(strcmp((*profile_1).name, "new_profile") == 0)
			{
				printf("Creating a new profile \n");
				(*profile_1).name = "Profile 1";
				// Reload the selection menu. This profile will appear there now.
				getMenu(&currentMenu, editprofile1Menu, 1);
				drawMenuText(currentMenu);
				return;
			}

			getMenu(&currentMenu, editprofile1Menu, 1);
			drawMenuText(currentMenu);
			return;
			// Load the menu asking to either load the profile, or delete it
			break;

		case 7: // Profile 2
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			if(strcmp((*profile_2).name, "new_profile") == 0)
			{
				printf("Creating a new profile \n");
				(*profile_2).name = "Profile 2";
				// Reload the selection menu. This profile will appear there now.
				getMenu(&currentMenu, editprofile2Menu, 1);
				drawMenuText(currentMenu);
				return;
			}

			getMenu(&currentMenu, editprofile2Menu, 1);
			drawMenuText(currentMenu);
			return;
			// Load the menu asking to either load the profile, or delete it
			break;
		case 8: // Profile 3
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			if(strcmp((*profile_3).name, "new_profile") == 0)
			{
				printf("Creating a new profile \n");
				(*profile_3).name = "Profile 3";
				// Reload the selection menu. This profile will appear there now.
				getMenu(&currentMenu, editprofile3Menu, 1);
				drawMenuText(currentMenu);
				return;
			}
			getMenu(&currentMenu, editprofile3Menu, 1);
			drawMenuText(currentMenu);
			return;
			// Load the menu asking to either load the profile, or delete it
			break;

		case 9: // Setting the current profile
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			set_current_profile(profile_1);
			printf("Current profile: %s", (*current_profile).name);
			// Reload the game
			changeState(Playing);
			return;

			break;

		case 10:
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			printf("trying to delete profile 1! \n");
			// Delete the profile, reload all the profiles, and then reload the profile selection menu
			delete_profile(1);
			// reloadProfiles();

			getMenu(&currentMenu, loadprofileMenu, 1);
			drawMenuText(currentMenu);
			return;

			break;

		case 11: // Setting the current profile
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			set_current_profile(profile_2);
			printf("Current profile: %s", (*current_profile).name);
			// Reload the game
			changeState(Playing);
			return;
			break;

		case 12:
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			printf("trying to delete profile 2! \n");
			// Delete the profile, reload all the profiles, and then reload the profile selection menu
			delete_profile(2);
			// reloadProfiles();

			getMenu(&currentMenu, loadprofileMenu, 1);
			drawMenuText(currentMenu);
			return;


			break;

		case 13: // Setting the current profile
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			set_current_profile(profile_3);
			printf("Current profile: %s \n", (*current_profile).name);
			// Reload the game
			changeState(Playing);
			return;
			break;

		case 14:
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			printf("trying to delete profile 3! \n");
			// Delete the profile, reload all the profiles, and then reload the profile selection menu
			delete_profile(3);
			// reloadProfiles();

			getMenu(&currentMenu, loadprofileMenu, 1);
			drawMenuText(currentMenu);
			return;


			break;

		case 15:
			if(!sdcard_isPresent() || !sdcard_isFAT16())
			{
				printf("Please insert an SD Card \n");
				return;
			}
			// Saving the data of the current profile
			updateProfile(current_profile);

			changeState(Playing);
			return;
			break;
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
		sprintf(menu->option[2],"     Profiles");
		sprintf(menu->option[3],"     Settings");
		sprintf(menu->option[4],"     Save Game");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 1;  //resume
		menu->optionIndex[2] = 5;
		menu->optionIndex[3] = 3;
		menu->optionIndex[4] = 15;  //save game
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
		// sprintf(menu->option[4],"    Test Save");
		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 0;
		menu->optionIndex[2] = 0;
		menu->optionIndex[3] = 4;
		// menu->optionIndex[4] = 5;
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
		menu->optionIndex[1] = 15;
		menu->optionIndex[2] = 0;
		menu->optionIndex[3] = 0;
	}else if(index == loadprofileMenu)
	{
		// Load the names from the available profiles (loading scores for now)

		sprintf(menu->option[0], "    Profiles");
		sprintf(menu->option[1], "    %s    Score: %i", (*profile_1).name, (*profile_1).score);
		sprintf(menu->option[2], "    %s    Score: %i", (*profile_2).name, (*profile_2).score);
		sprintf(menu->option[3], "    %s    Score: %i", (*profile_3).name, (*profile_3).score);

		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 6;
		menu->optionIndex[2] = 7;
		menu->optionIndex[3] = 8;

	}else if(index == editprofile1Menu)
	{
		// Either Load or Edit the selected Profile

		sprintf(menu->option[0], "    %s", (*profile_1).name);
		sprintf(menu->option[1], "    Load Profile");
		sprintf(menu->option[2], "    Delete Profile");
		sprintf(menu->option[3], "    Maps");

		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 9;
		menu->optionIndex[2] = 10;

	}else if(index == editprofile2Menu)
	{
		// Either Load or Edit the selected Profile

		sprintf(menu->option[0], "    %s", (*profile_2).name);
		sprintf(menu->option[1], "    Load Profile");
		sprintf(menu->option[2], "    Delete Profile");
		sprintf(menu->option[3], "    Maps");

		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 11;
		menu->optionIndex[2] = 12;

	}else if(index == editprofile3Menu)
	{
		// Either Load or Edit the selected Profile

		sprintf(menu->option[0], "    %s", (*profile_3).name);
		sprintf(menu->option[1], "    Load Profile");
		sprintf(menu->option[2], "    Delete Profile");
		sprintf(menu->option[3], "    Maps");

		menu->min=1;
		menu->max=4;
		menu->selected=1;
		menu->optionIndex[1] = 13;
		menu->optionIndex[2] = 14;

	}
	else
	{
		sprintf(menu->option[0],"Bad Menu");
		menu->min=0;
		menu->max=0;
		menu->selected=-1;
	}
}

