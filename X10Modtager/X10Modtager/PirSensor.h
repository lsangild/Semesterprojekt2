/*

Pirsensoren forbindes til PIND0 (Arduino ben 21)

*/

#ifndef PIRSENSOR_H_
#define PIRSENSOR_H_

#include <avr/interrupt.h>

// Variables
int pirInterruptActive;

// Functions
void pirInit();

int pirScan();

void pirIterruptInit();
void activatePirInterrupt();
void deactivatePirInterrupt();

ISR(INT0_vect);

#endif /* PIRSENSOR_H_ */