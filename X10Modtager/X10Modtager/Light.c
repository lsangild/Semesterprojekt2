#include "Light.h"

void lightInit()
{
	DDRB = (DDRB | 0b10000000);		// Sætter PB til udgang
	PORTB = (PORTB & 0b01111111);

	TCCR1A = (TCCR1A | 0b00000010);	//
	TCCR1B = (TCCR1B | 0b00000000);	// Timer-mode sættes til mode 2 (9 bit fasekorrekt)

	TCCR1B = (TCCR1B | 0b00000100);	// Preescaler sættes til 256
	
	TCCR1A = (TCCR1A | 0b00001100);	// Sætter C-system on compare when up-counting

	//setLightLevel(0);
}


void setLightLevel(int duty)
{
	OCR1C = (1 - (duty * 0.01)) * 512;	//	C-systemet bruges
	lightOn();
}


void lightOn()
{
	TCCR1B = (TCCR1B | 0b00000100);	// Preescaler sættes til 256 for at tænde
}


void lightOff()
{
	TCCR1B = (TCCR1B & 0b11111000);	// Preescaler sættes til 0 for at slukke
	PORTB = (PORTB & 0b01111111);
}