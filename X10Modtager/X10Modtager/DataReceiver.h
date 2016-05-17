/*
Båndpasfilteret forbindes til PIND2 (Arduino ben 19)
*/ 


#ifndef DATARECEIVER_H_
#define DATARECEIVER_H_

#include "GlobalInclude.h"
#include "X10Message.h"

// Variabler				// Besked modtaget deles op i 4 char variabler
char firstMessagePart;		// Første 
char secondMessagePart;		//
char thirdMessagePart;		// 
char fourthMessagePart;		//

// Funktioner
void dataReceiverInit();

void newMessage();

void interpretMessage(struct X10Message);

void insertNewBit();
int checkForMessage();
int checkForLegitMessage();

struct X10Message readMessage();

int getUnitID();
int getMode();
int getBrightness();

char getBitValue(char, int);	// Henter paritiseret bitværdi ved bit nr. 3-0 i char. Returnere -1 ved fejl.

#endif /* DATARECEIVER_H_ */