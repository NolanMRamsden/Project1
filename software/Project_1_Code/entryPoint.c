
#include "Headers/headers.h"

static int currentState;
static int prevState;

void changeState(int state)
{
	prevState = currentState;
	currentState = state;

}

int main()
{
	sdcard_Init();

	while(!sdcard_isPresent())
	{
		printf("No SD Card inserted \n");
	}
	while(!sdcard_isFAT16())
	{
		printf("SD Card must be FAT16 formatted! \n");
	}

	// score = get_score_from_sd_card(1);
 	initProfiles();
	initVGA();

	//pre load the root menu
	getMenu(&currentMenu,rootMenu, 1);

	//allocate memory for level farm
	BrickMap *brickmap = malloc(sizeof(BrickMap));

	//set the game to playing
	prevState=currentState=Playing;


	//look up the level from level farm and load it into currentLevel
	levelLookUp(brickmap,6);
	initLevel(*brickmap);
	drawStart(currentLevel);   //this is optional here
	swapBuffers();
	drawStart(currentLevel);

	runCountDown();              //count down from three
	initInterrupt();            //start the game (we dont need to right off the bat (probably shouldnt)

	int counter=0;   //so were not doing direct IO reads on EVERY iteration (we could timer this buttttt no)
	while(1)
	{
		//input to state machine
		counter++;
		if(counter>650000)
		{
			counter=0;
			if(getSwitchIndex()== 1)
				changeState(MenuShow);
			else
				changeState(Playing);
		}
		//flicker changes
		if(prevState != currentState)
		{
			if(currentState == Playing)
			{
				clearScreen();
				drawStart(currentLevel);   //this is optional here
				swapBuffers();
				drawStart(currentLevel);
				runCountDown();
				initInterrupt();
			}else
			{
				stopInterrupt();
				clearScreen();
				drawStart(currentLevel);   //this is optional here
				swapBuffers();
				drawStart(currentLevel);
				drawMenu(currentMenu);
			}
			prevState = currentState;
		}
		//state machine
		if(currentState != Playing)
		{
			menuLoop();
		}else //while were playing we will have to check for other things (all balls gone etc.)
		{
			if(currentLevel->brickCount==0)
				drawText("Completed",37,30,0);
		}
	}
	return 0;
}


