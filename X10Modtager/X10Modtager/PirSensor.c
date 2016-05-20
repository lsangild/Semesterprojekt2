#include "PirSensor.h"


void pirInit()
{
	DDRD = ( DDRD & 0b11111101 );
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


void pirIterruptInit()
{
	activatePirInterrupt();
	sei();							// Global interrupt enable.
}


void activatePirInterrupt()
{
	EIMSK = ( EIMSK | 0b00000010 );	// Lokal interrupt enable for INT0
	EICRA = ( EICRA | 0b00001100 ); // Interrupt on rising edge.
}


void deactivatePirInterrupt()
{
	EIMSK = ( EIMSK & 0b11111101 );
}


ISR(INT1_vect)
{
	

	reti();
}