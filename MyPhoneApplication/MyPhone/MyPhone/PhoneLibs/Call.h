
#ifndef _CALL_H_
#define _CALL_H_

#pragma once

#include "CommunicationObject.h"

class Call : public CommunicationObject
{
/* Constructors & Destructor */
public :
	Call();
	Call(PhoneNumber sender, PhoneNumber receiver);
	Call(const Call& object);
	Call(PhoneNumber sender, PhoneNumber receiver, int year, int month, int day, int hour, int minute, int second);
	~Call();
};

#endif	/* end of _CALL_H_ */