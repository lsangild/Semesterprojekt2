/*
Pirsensoren forbindes til PIND1 (Arduino ben 20)
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

ISR(INT1_vect);

#endif /* PIRSENSOR_H_ */