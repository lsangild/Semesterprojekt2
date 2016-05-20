#define F_CPU 16000000
#include <util/delay.h>
#include "ZeroCrossing.h"
#include "DataReceiver.h"


void zeroCrossInit()
{
	DDRD = (DDRD & 0b11111110);
	PORTD = (PORTD & 0b11111110);
	EICRA = (EICRA | 0b00000001);
	activateZeroCrossInterrupt();
	sei();
}


void activateZeroCrossInterrupt()
{
	EIMSK = (EIMSK | 0b00000001);
}


void deactivateZeroCrossInterrupt()
{
	EIMSK = (EIMSK & 0b11111110);
}
// 200 us

ISR(INT0_vect)
{
	newMessage();
	reti();
}