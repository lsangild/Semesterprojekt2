#include "ActivationTimer.h"
#include "uart.h"
#include "Light.h"

volatile int waitedTime = 0;

void activationTimerInit()
{
	TCCR3A = (TCCR3A & 0b11111100);		// Normal mode vælges
	TCCR3B = (TCCR3B & 0b11100111);		//

	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler sættes til 0

	TCNT3  = sec_time;					// Tælleregister sættes til 49911

	TIMSK3 = (TIMSK3 | 0b00000001);		// Interrupt enable

	sei();
}


void activationTimerStart()
{
	activationTimerReset();
	TCCR3B = (TCCR3B | 0b00000101);		// Preescaler sættes til 1024
	TCCR3B = (TCCR3B & 0b11111101);		//
}


void activationTimerStop()
{
	TCCR3B = (TCCR3B & 0b11111000);		// Preescaler sættes til 0
}


void activationTimerReset()
{
	waitedTime = 0;
}


void activationClokcReset()
{
	TCNT3 = sec_time;
}


ISR(TIMER3_OVF_vect)
{
	waitedTime++;

	if (waitedTime >= wait_time)
	{
		SendChar('Q');
		SendInteger(waitedTime);

		lightOff();
		waitedTime = 0;
		activationTimerStop();
	}
	else
	{
		lightOn();
		SendInteger(waitedTime);	// Debug
		SendChar(',');				//
	}

	activationClokcReset();			// Reset af tælleregister
}