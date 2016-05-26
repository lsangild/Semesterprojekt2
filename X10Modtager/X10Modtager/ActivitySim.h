#ifndef ACTIVITYSIM_H_
#define ACTIVITYSIM_H_

#define SEC_TIME 49911		// 1 sek
#define MAX_SIM_TIME 3
#define MIN_SIM_TIME 1

#include <avr/interrupt.h>
#include "GlobalInclude.h"

void activitySimInit();
void activitySimStart();
void activitySimStop();
int generateNewSimTime();

void activityClockReset();

ISR(TIMER4_OVF_vect);

#endif /* ACTIVITYSIM_H_ */