/*
Zero Cross forbindes til PIND0 (Arduino ben 21)
*/

#include <avr/interrupt.h>

#ifndef ZEROCROSSING_H_
#define ZEROCROSSING_H_

int crossings;

void zeroCrossInit();

void activateZeroCrossInterrupt();
void deactivateZeroCrossInterrupt();

ISR(INT0_vect);

#endif /* ZEROCROSSING_H_ */