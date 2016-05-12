#include "PirSensor.h"

void pirInit()
{
	DDRD = ( DDRD & 0b11111110 );
}


int pirScan()
{
	if ( ( PIND & 0b00000001 ) == 0b00000000 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void pirIterruptInit()
{
	activatePirInterrupt();
	sei();							// Global interrupt enable.
}


void activatePirInterrupt()
{
	EIMSK = ( EIMSK | 0b00000001 );	// Lokal interrupt enable for INT0
	EICRA = ( EICRA | 0b00000011 ); // Interrupt on rising edge.
}


void deactivatePirInterrupt()
{
	EIMSK = ( EIMSK & 0b11111110 );
}


ISR(INT0_vect)
{
	
	reti();
}