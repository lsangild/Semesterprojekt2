#include "DataReceiver.h"
#include "PirSensor.h"
#include "ActivitySim.h"
#include "Light.h"


void dataReceiverInit()
{
	pirInit();
	activitySimInit();

	DDRD = (DDRD & 0b11111011);		// Sætter PD2 til indgagn
}


void newMessage()
{
	insertNewBit();		// Indsæt nye bit i bitrækken
	
	if (checkForLegitMessage() == 1)		// Check om der er kommet en ny besked
	{
		struct X10Message message = readMessage();		// Læs beekeden

		if (message.unit_ == UNIT_ID || message.unit_ == 0)		// Hvis beskeden er til denne enhed eller alle enheder
		{
			interpretMessage(message);		// Forstå besked og udfør kommandoer
		}
	}
}


void interpretMessage(struct X10Message m)
{
	setLightLevel(m.brightness_);		// Sæt den nye lysstyrke

	if (m.mode_ == 0 && pirInterruptCheckRunnig() != 1)			// PIR respons
	{
		activitySimStop();		// Stop Aktivitetssimuleringen
		pirInterruptStart();	// Start PIR-interruptet
	}
	else if (m.mode_ == 1 && activitySimCheckRunning() != 1)	// Aktivitessimulering
	{
		pirInterruptStop();		// Stop PIR-interruptet
		activitySimStart();		// Start Aktivitetssimuleringen
	}
}


void insertNewBit()		// Shifter alle bits i den indlæste bit én frem og indsætter ny bit
{
	firstMessagePart = firstMessagePart << 1;
	firstMessagePart = (firstMessagePart | ((secondMessagePart & 0b10000000) >> 7));

	secondMessagePart = secondMessagePart << 1;
	secondMessagePart = (secondMessagePart | ((thirdMessagePart & 0b10000000) >> 7));

	thirdMessagePart = thirdMessagePart << 1;
	thirdMessagePart = (thirdMessagePart | ((fourthMessagePart & 0b10000000) >> 7));

	fourthMessagePart = fourthMessagePart << 1;
	fourthMessagePart = (fourthMessagePart | (PIND & 0b00000100));
}


int checkForLegitMessage()
{
	if ((firstMessagePart & 0b11110000) != 0b11100000)	// Chekker for start besked
	{
		return 0;
	}
	
	int i;
	for (i = 0; i <= 1; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(firstMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}
	
	for (i = 0; i <= 3; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(secondMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	for (i = 0; i <= 3; i++)		// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(thirdMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}
	
	for (i = 1; i < 3; i++)			// Checker om der er paritet de rigtige steder
	{
		if (getBitValue(fourthMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	return 1;		// 1 = legit
}


struct X10Message readMessage()	// Læser X.10 besked
{
	struct X10Message message;

	message.unit_ = getUnitID();
	message.mode_ = getMode();
	message.brightness_ = getBrightness();

	return message;
}


int getUnitID()		// Henter enhedesnummer
{
	char unitID = 0b00000000;

	unitID = (unitID | (getBitValue(firstMessagePart, 1) << 4));
	unitID = (unitID | (getBitValue(firstMessagePart, 0) << 3));
	unitID = (unitID | (getBitValue(secondMessagePart, 3) << 2));
	unitID = (unitID | (getBitValue(secondMessagePart, 2) << 1));
	unitID = (unitID | (getBitValue(secondMessagePart, 1) << 0));

	return unitID;
}


int getMode()		// Henter mode
{
	return getBitValue(secondMessagePart, 0);
}


int getBrightness()		// Henter lysviveau
{
	char brightness = 0b00000000;

	brightness = (brightness | (getBitValue(thirdMessagePart, 3) << 6));
	brightness = (brightness | (getBitValue(thirdMessagePart, 2) << 5));
	brightness = (brightness | (getBitValue(thirdMessagePart, 1) << 4));
	brightness = (brightness | (getBitValue(thirdMessagePart, 0) << 3));

	brightness = (brightness | (getBitValue(fourthMessagePart, 3) << 2));
	brightness = (brightness | (getBitValue(fourthMessagePart, 2) << 1));
	brightness = (brightness | (getBitValue(fourthMessagePart, 1) << 0));

	if (brightness > 100)
	{
		brightness = 100;
	}

	return brightness;
}


char getBitValue(char byte, int bitNum)		// Henter bit nr. bitNum ud af X10 Besked
{
	if (0 >= bitNum && bitNum <= 3)		// Checker først om der bedes om legalt bit
	{
		return 0b11111111;
	}
	
	int bitShift = bitNum * 2;			

	if ((byte & (0b00000011 << bitShift)) == (0b00000001 << bitShift))
	{
		return 0b00000000;		// Det er et '0'
	}
	else if ((byte & (0b00000011 << bitShift)) == (0b00000010 << bitShift))
	{
		return 0b00000001;		// Det er et '1'
	}
	else
	{
		return 0b11111111;
	}
}