
#ifndef _COMMUNICATION_OBJECT_H_
#define _COMMUNICATION_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <exception>
#include "PhoneNumber.h"

///////////////////////////////////////////////////////////////////////////////////////

class CommunicationObject
{
/* Member Variables */
protected :
	PhoneNumber		m_sender;
	int				m_timeYear, m_timeMonth, m_timeDay;
	int				m_timeHour, m_timeMinute, m_timeSecond;

/* Constructor & Destructor */
public :
	CommunicationObject();
	CommunicationObject(PhoneNumber phoneNumber);
	CommunicationObject(const CommunicationObject& object);
	CommunicationObject(PhoneNumber phoneNumber, int year, int month, int day, int hour, int minute, int second);
	~CommunicationObject();

/* Methods */
public :
	virtual int				SetSender(PhoneNumber senderNumber);
	virtual int				SetSender(std::string senderNumber);
	virtual PhoneNumber		GetSender(void) const;

	void					SetCurrentTime();

	bool					IsValidDate(void) const;
	int						SetTime(int year, int month, int day, int hour, int minute, int second);

	int						SetYear(int year);
	int						GetYear() const;

	int						SetMonth(int month);
	int						GetMonth() const;

	int						SetDay(int day);
	int						GetDay() const;

	int						SetHour(int hour);
	int						GetHour() const;

	int						SetMinute(int minute);
	int						GetMinute() const;

	int						SetSecond(int second);
	int						GetSecond() const;

/* operator overriding */

	// Compare objects by time
	bool					operator>(const CommunicationObject& operand);
	bool					operator>=(const CommunicationObject& operand);
	bool					operator<(const CommunicationObject& operand);
	bool					operator<=(const CommunicationObject& operand);

	friend std::ostream&	operator<<(std::ostream& out, const CommunicationObject&);
	friend std::istream&	operator>>(std::istream& in, CommunicationObject&);
};

///////////////////////////////////////////////////////////////////////////////////////

class CommunicationLoadFailException : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return "Wrong syntax for loading Communication Object";
	}
};

#endif	/* _COMMUNICATION_OBJECT_H_ */