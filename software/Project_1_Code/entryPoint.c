
#include "Headers/headers.h"
#include "Headers/Menu.h"

static int currentState;
static int prevState;

void changeState(int state)
{
	prevState = currentState;
	currentState = state;
}

int main()
{
	initVGA();
	initLevel(3);
	prevState= -1;
	currentState=Playing;
	drawStart(level);
	Menu *menu = malloc(sizeof(Menu));
	//initInterrupt();


	int counter=0;
	while(1)
	{
		//input to state machine
		counter++;
		if(counter>650000)
		{
			counter=0;
			if(getSwitchIndex()== 0)
				changeState(Paused);
			else if(getSwitchIndex()== 1)
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
				drawStart(level);
				initInterrupt();
			}else
			{
				stopInterrupt();
				if (currentState == MenuShow)
				{
					getMenu(menu,rootMenu);
				}else if (currentState == Paused)
				{
					getMenu(menu,pauseMenu);
				}
				clearScreen();
				drawStart(level);
				drawMenu(menu);
			}
			prevState = currentState;
		}
		//state machine
		if(currentState != Playing)
		{
			menuLoop(menu);
		}
	}
	return 0;
}


