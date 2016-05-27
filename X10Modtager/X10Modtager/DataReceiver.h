#ifndef DATARECEIVER_H_
#define DATARECEIVER_H_

#include "GlobalInclude.h"
#include "X10Message.h"

// Variabler				// Besked modtaget deles op i 4 char variabler
char firstMessagePart;		// og shiftes én frem ved hvert zero cross
char secondMessagePart;		//
char thirdMessagePart;		// 
char fourthMessagePart;		//

// Funktioner
void dataReceiverInit();

void newMessage();
void interpretMessage(struct X10Message);

void insertNewBit();
int checkForLegitMessage();

struct X10Message readMessage();

int getUnitID();
int getMode();
int getBrightness();

char getBitValue(char, int);	// Henter paritiseret bitværdi ved bit nr. 3-0 i char. Returnere -1 ved fejl.

#endif /* DATARECEIVER_H_ */