#define F_CPU 16000000
#include <util/delay.h>
#include "ZeroCrossing.h"


void zeroCrossInit()
{
	DDRD = (DDRD & 0b11111101);
	PORTD = (PORTD & 0b11111101);
	EICRA = (EICRA | 0b00000100);
	activateZeroCrossInterrupt();
	sei();
}


void activateZeroCrossInterrupt()
{
	EIMSK = (EIMSK | 0b00000010);
}


void deactivateZeroCrossInterrupt()
{
	EIMSK = (EIMSK & 0b11111101);
}


ISR(INT1_vect)
{
	if ((PIND & 0b00000100) == 0b00000100)
	{
		
	}

	reti();
}