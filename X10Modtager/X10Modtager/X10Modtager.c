#include "GlobalInclude.h"
#include "PirSensor.h"
#include "ZeroCrossing.h"
#include "X10Message.h"
#include "DataReceiver.h"
#include "uart.h"
#include "ActivationTimer.h"
#include "Light.h"

const int unitID = 1;

int inactivityBrightness = 0;
int activityBrightness = 100;

int main(void)
{
	InitUART(9600, 8, 'N');
	activationTimerInit();
	pirInit();
	activatePirInterrupt();

	lightInit();
	setLightLevel(100);

	while(1)
	{
		
	}
}

//// Sammenflettet ////
// Light
// PirSensor
// Aktivitets timer
// 

//// Mangler ////
// Zero Cross
// DataReciever
// AktivitetsSimulering