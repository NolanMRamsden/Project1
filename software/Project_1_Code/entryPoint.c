
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

 	// printf("init profiles \n");
 	// Example code to write maps
	int brickArray[maxRows][bricksPerRow] =
			{
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
			};

	printIntArray(brickArray);

	// Writes the map to profile 1 map 1
	writeMap(brickArray, 1, 1);

	// Reads the map from profile 1 map 1
	readMap(brickArray, 1, 1);

	printIntArray(brickArray);

	int level=6;
	initVGA();

	//pre load the root menu
	getMenu(&currentMenu,rootMenu, 1);

	//allocate memory for level farm
	BrickMap *brickmap = malloc(sizeof(BrickMap));

	//set the game to playing
	prevState=currentState=Playing;


	//look up the level from level farm and load it into currentLevel
	levelLookUp(brickmap,level);
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
		if(counter>65000)
		{
			counter=0;
			if(getMenuPB())
			{
				while(getMenuPB() != 0);
				if(currentState == Playing)
					changeState(MenuShow);
			}
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
			{
				changeState(MenuShow);
				stopInterrupt();
				level++;
				levelLookUp(brickmap,level);
				initLevel(*brickmap);
			}
		}
	}
	return 0;
}


