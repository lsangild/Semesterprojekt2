// Timer til at deaktivere lys efter 15 min tændt tid Timer 3.
// Top = 65536
// TCCR3 = 49911
// Pre = 1024

#define sec_time 49911		// 1 sek
#define wait_time 900		// 900 sek = 15 min

#include "GlobalInclude.h"
#include <avr/interrupt.h>

#ifndef ACTIVATIONTIMER_H_
#define ACTIVATIONTIMER_H_

void activationTimerInit();
void activationTimerStart();
void activationTimerStop();
void activationTimerReset();
void activationClokcReset();

ISR(TIMER3_COMPA_vect);

#endif /* ACTIVATIONTIMER_H_ */