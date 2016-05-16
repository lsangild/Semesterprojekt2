#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "PirSensor.h"
#include "ZeroCrossing.h"


int main(void)
{
	DDRB = 0b11111111;
	DDRD = 0b00000000;
	
	zeroCrossInit();

	while(1)
	{
	
	}
}