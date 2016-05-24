#include "GlobalInclude.h"
#include "PirSensor.h"
#include "ZeroCrossing.h"
#include "X10Message.h"
#include "DataReceiver.h"
#include "uart.h"
#include "ActivationTimer.h"

const int unitID = 1;

int inactivityBrightness = 0;
int activityBrightness = 100;

int main(void)
{
	InitUART(9600, 8, 'N');

	activationTimerInit();

	while(1)
	{
			
	}
}