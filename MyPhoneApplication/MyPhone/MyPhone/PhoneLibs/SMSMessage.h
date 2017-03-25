
#ifndef _SMS_MESSAGE_H_
#define _SMS_MESSAGE_H_

#pragma once

#include "CommunicationObject.h"

class SMSMessage : public CommunicationObject
{
/* Member variables */
protected :
	std::string			m_message;

/* Constructors & Destructor */
public :
	SMSMessage();
	SMSMessage(PhoneNumber phoneNumber);
	SMSMessage(PhoneNumber phoneNumber, std::string message);
	SMSMessage(const SMSMessage& object);
	SMSMessage(PhoneNumber phoneNumber, std::string message, int year, int month, int day, int hour, int minute, int second);
	~SMSMessage();

/* Methods */
public :
	int					SetMessage(std::string message);
	std::string			GetMessage(void) const;

	friend std::ostream&	operator<<(std::ostream& out, const SMSMessage&);
	friend std::istream&	operator>>(std::istream& in, SMSMessage&);
};

#endif	/* end of _SMS_MESSAGE_H_ */