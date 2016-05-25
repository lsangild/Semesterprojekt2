#include "PirSensor.h"
#include "ActivationTimer.h"
#include "uart.h"

void pirInit()
{
	PORTD = (PORTD | 0b00000000);
	PIND = (PIND | 0b00000000);
	DDRD = (DDRD & 0b11111101);
}


int pirScan()
{
	if ( ( PIND & 0b00000010 ) == 0b00000000 )
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
	EIMSK = ( EIMSK | 0b00000010 );	// Lokal interrupt enable for INT1
	EICRA = ( EICRA | 0b00001100 ); // Interrupt on rising edge.
	sei();						// Global interrupt enable.
}


void deactivatePirInterrupt()
{
	EIMSK = ( EIMSK & 0b11111101 );
}


ISR(INT1_vect)
{
	SendChar('a');

	activationTimerStart();
}