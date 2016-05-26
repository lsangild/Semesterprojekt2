#include "PirSensor.h"
#include "ActivationTimer.h"
#include "uart.h"

void pirInit()
{
	PORTE = (PORTE | 0b00000000);
	PINE = (PINE | 0b00000000);
	DDRE = (DDRE & 0b11011111);
	EICRB = (EICRB | 0b00001100);	// Interrupt on rising edge.
	deactivatePirInterrupt();
	sei();	

	activationTimerInit();
}


int pirScan()
{
	if ( ( PINE & 0b00100000 ) == 0b00000000 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void activatePirInterrupt()
{
	EIMSK = (EIMSK | 0b00100000);	// Lokal interrupt enable for INT1
}


void deactivatePirInterrupt()
{
	EIMSK = (EIMSK & 0b11011111);
}


ISR(INT5_vect)
{
	SendChar('\n');					//
	SendChar('a');					// Debug
	
	activationTimerStart();
}