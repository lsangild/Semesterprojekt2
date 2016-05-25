/*
Pirsensoren forbindes til PE5 (Arduino ben 3) EXT Int 5
*/

#ifndef PIRSENSOR_H_
#define PIRSENSOR_H_

#include <avr/interrupt.h>

// Variables
int pirInterruptActive;

// Functions
void pirInit();

int pirScan();

void activatePirInterrupt();
void deactivatePirInterrupt();

ISR(INT5_vect);

#endif /* PIRSENSOR_H_ */