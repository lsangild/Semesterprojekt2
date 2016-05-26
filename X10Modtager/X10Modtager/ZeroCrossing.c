#define F_CPU 16000000
#include <util/delay.h>
#include "ZeroCrossing.h"
#include "DataReceiver.h"


void zeroCrossInit()
{
	DDRE = (DDRE & 0b11101111);
	PORTE = (PORTE & 0b11101111);
	EICRB = (EICRB | 0b00000001);
	activateZeroCrossInterrupt();
	sei();
}


void activateZeroCrossInterrupt()
{
	EIMSK = (EIMSK | 0b00010000);
}


void deactivateZeroCrossInterrupt()
{
	EIMSK = (EIMSK & 0b11101111);
}


ISR(INT4_vect)
{
	newMessage();
}