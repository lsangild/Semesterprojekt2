/*
LED forbindes til PB7 (Arduino ben 13) og bruger timer 1C.
9 bit
Prescaler 256
*/

#ifndef LIGHT_H_
#define LIGHT_H_

#include "GlobalInclude.h"

void lightInit();
void setLightLevel(int);	// int 0 - 100
void lightOn();
void lightOff();

#endif /* LIGHT_H_ */