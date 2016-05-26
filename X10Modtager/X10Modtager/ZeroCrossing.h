/*
Zero Cross forbindes til PE4 (Arduino ben 2) Ex Int 4
*/

#include <avr/interrupt.h>

#ifndef ZEROCROSSING_H_
#define ZEROCROSSING_H_

void zeroCrossInit();

void activateZeroCrossInterrupt();
void deactivateZeroCrossInterrupt();

ISR(INT4_vect);

#endif /* ZEROCROSSING_H_ */