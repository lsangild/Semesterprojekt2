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
	
	DDRB = 0b11111111;
	PORTB = 0b00000000;
	InitUART(9600, 8, 'N');
	activationTimerInit();

	pirInit();
	activatePirInterrupt();


	SendChar('\n');
	SendChar('S');
	SendChar('\n');
	
	while(1)
	{
		
	}
}