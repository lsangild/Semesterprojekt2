/*
Zero Cross forbindes til PIND1 (Arduino ben 20)
*/

#include <avr/interrupt.h>

#ifndef ZEROCROSSING_H_
#define ZEROCROSSING_H_

int crossings;

void zeroCrossInit();

void activateZeroCrossInterrupt();
void deactivateZeroCrossInterrupt();

ISR(INT1_vect);

#endif /* ZEROCROSSING_H_ */