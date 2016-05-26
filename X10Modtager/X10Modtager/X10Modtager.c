// Koder til styring af X.10 Modtager til Semester Projekt 2.
// xx/xx - 2016
// 
//
// Zero Cross Detector	PE4	Arduino ben 2	Ext Int 4
// Båndpasfilter		PD2	Arduino ben 19	
// PIR-sensor			PE5	Arduino ben 3	Ext Int 5
// Lys					PB7	Arduino ben 13	Timer 1	C-System	Mode 2 (9-bit fasekorrekt PWM)	Prescaler: 256
// ActivationTimer (1s)	--	--				Timer 3				Mode 0 (Normal)					Prescaler: 1024
// Aktiviters Simulering--	--				Timer 4				Mode 
//


#include "GlobalInclude.h"
#include "PirSensor.h"
#include "ZeroCrossing.h"
#include "uart.h"

#include "ActivitySim.h"
#include "Light.h"

const int unitID = 1;

int inactivityBrightness = 0;
int activityBrightness = 100;

int main(void)
{
	InitUART(9600, 8, 'N');		// Debug
	lightInit();
	activitySimInit();
	activitySimStart();

	setLightLevel(100);
	int i;
	for (i = 0; i < 50; i++)
	{
	_delay_ms(200);
	}
	activitySimStop();


	for (i = 0; i < 50; i++)
	{
		_delay_ms(200);
	}
	activitySimStart();
	s
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