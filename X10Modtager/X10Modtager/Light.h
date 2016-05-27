#ifndef LIGHT_H_
#define LIGHT_H_

#include "GlobalInclude.h"

void lightInit();
void setLightLevel(int);	// int 0 - 100
void lightOn();
void lightOff();
void lightInvert();

#endif /* LIGHT_H_ */