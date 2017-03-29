
#include "Call.h" 

Call::Call()
{

}

Call::Call(PhoneNumber sender, PhoneNumber receiver)
	: CommunicationObject(sender, receiver)
{

}

Call::Call(const Call& object)
	: CommunicationObject(object)
{

}

Call::Call(PhoneNumber sender, PhoneNumber receiver, int year, int month, int day, int hour, int minute, int second)
	: CommunicationObject(sender, receiver, year, month, day, hour, minute, second)
{

}

Call::~Call()
{

}