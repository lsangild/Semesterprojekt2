#include "DataReceiver.h"
#include "uart.h"

const int unitID;
int inactivityBrightness;
int activityBrightness;

void dataReceiverInit()
{
	DDRD = (DDRD & 0b11111011);
}


void newMessage()
{
	insertNewBit();
	
	if (checkForMessage() == 1)
	{
		if (checkForLegitMessage() == 1)
		{
			struct X10Message message = readMessage();

			if (message.unit_ == unitID || message.unit_ == 31)
			{
				interpretMessage(message);
			}
		}
	}
}


void interpretMessage(struct X10Message m)
{
	if (m.mode_ == 0)
	{
		inactivityBrightness = m.brightness_;
	}
	else if (m.mode_ == 1)
	{
		activityBrightness = m.brightness_;
	}

	// her mangler en update light funktion.
}


void insertNewBit()		// Testet - Virker
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


int checkForMessage()		// Testet - Virker
{
	if ((firstMessagePart & 0b11110000) == 0b11100000)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int checkForLegitMessage()		// Testet - Virker
{
	if (checkForMessage() == 0)
	{
		return 0;
	}

	// 1
	int i;
	for (i = 0; i <= 1; i++)
	{
		if (getBitValue(firstMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	// 2
	for (i = 0; i <= 3; i++)
	{
		if (getBitValue(secondMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	// 3
	for (i = 0; i <= 3; i++)
	{
		if (getBitValue(thirdMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}
	
	// 4
	for (i = 1; i < 3; i++)
	{
		if (getBitValue(fourthMessagePart, i) == 0b11111111)
		{
			return 0;
		}
	}

	return 1;		// 1 = legit
}


struct X10Message readMessage()
{
	struct X10Message message;

	message.unit_ = getUnitID();
	message.mode_ = getMode();
	message.brightness_ = getBrightness();

	return message;
}


int getUnitID()		// Testet - Virker
{
	char unitID = 0b00000000;

	unitID = (unitID | (getBitValue(firstMessagePart, 1) << 4));
	unitID = (unitID | (getBitValue(firstMessagePart, 0) << 3));
	unitID = (unitID | (getBitValue(secondMessagePart, 3) << 2));
	unitID = (unitID | (getBitValue(secondMessagePart, 2) << 1));
	unitID = (unitID | (getBitValue(secondMessagePart, 1) << 0));

	return unitID;
}


int getMode()	// Testet - Virker
{
	return getBitValue(secondMessagePart, 0);
}


int getBrightness()		// Testet - Virker
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


char getBitValue(char byte, int bitNum)		// Testet - Virker
{
	char returnChar;

	if (bitNum < 0 && 3 < bitNum)
	{
		returnChar = 0b11111111;		// Muligvis stop funktionskald hvis forkert data
	}
	
	int bitShift = bitNum * 2;

	if ((byte & (0b00000011 << bitShift)) == (0b00000001 << bitShift))
	{
		returnChar = 0b00000000;
	}
	else if ((byte & (0b00000011 << bitShift)) == (0b00000010 << bitShift))
	{
		returnChar = 0b00000001;
	}
	else
	{
		returnChar = 0b11111111;		// Muligvis stop funktionskald hvis forkert data
	}

	return returnChar;
}