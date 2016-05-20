#include "MainProgram.h"

const int unitID;
int inactivityBrightness;
int activityBrightness;


void mainProgram()
{
	mainInit();
	
	while (1)
	{
		
	}
}


void mainInit()
{
	pirInit();
	zeroCrossInit();
	dataReceiverInit();
	//lightInit();	
}