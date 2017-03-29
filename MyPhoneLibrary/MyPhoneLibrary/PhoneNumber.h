
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _MY_PHONE_NUMBER_H_
#define _MY_PHONE_NUMBER_H_

#pragma once

/*
 * Team Project # 1
 * Created By Seung Won Kang, Ho Jun Lee
 */

///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

///////////////////////////////////////////////////////////////////////////////////////

#define PHONE_NUMBER_ALLOWED_STRING			"0123456789-"
#define PHONE_NUMBER_ALLOWED_STRING_SIZE	(sizeof(PHONE_NUMBER_ALLOWED_STRING) / sizeof(char))

///////////////////////////////////////////////////////////////////////////////////////

class PhoneNumber
{
/* shared data */
protected :
	static const std::string		AREA_CODE[];

/* Member variables */
protected :
	std::string		m_phoneNumber;

/* Constructors & Destructor */
public :
	PhoneNumber(void);
	PhoneNumber(std::string phoneNumber);
	PhoneNumber(const PhoneNumber&);
	~PhoneNumber();

/* Methods */
public :
	int				SetPhoneNumber(std::string number);
	std::string		GetPhoneNumber(void) const;
	int				Normalize(void);
	bool			IsEmpty(void) const;

/* Operator overriding */
	bool			operator==(const PhoneNumber&) const;
	bool			operator>(const PhoneNumber&) const;
	bool			operator<(const PhoneNumber&) const;
	PhoneNumber&	operator=(const PhoneNumber&);
	PhoneNumber&	operator=(const std::string&);

/* Methods for I/O */
	friend std::ostream& operator<<(std::ostream& out, const PhoneNumber&);
	friend std::istream& operator>>(std::istream& in, PhoneNumber&);
};

///////////////////////////////////////////////////////////////////////////////////////

class NotPhoneNumberException : public std::exception
{
protected :
	std::string		m_wrongString;

public :
	NotPhoneNumberException(std::string wrongString) noexcept;
	NotPhoneNumberException(NotPhoneNumberException& e) noexcept;

public :
	virtual const char* what() const noexcept
	{
		return "It is not phone number.";
	}
};

#endif

///////////////////////////////////////////////////////////////////////////////////////