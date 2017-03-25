
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _MY_ADDRESS_H_
#define _MY_ADDRESS_H_

///////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "PhoneNumber.h"


///////////////////////////////////////////////////////////////////////////////////////

class MyAddress
{
/* Member Variables */
protected :
	std::vector<PhoneNumber>		m_phoneNumbers;
	std::string						m_name;
	std::string						m_homeAddress, m_officeAddress;
	std::string						m_involvedGroup;
	std::string						m_email;
	std::string						m_url;
	size_t							m_birthdayYear, m_birthdayMonth, m_birthdayDay;


/* Constructor & Destructor */
public :
	MyAddress(void);
	~MyAddress(void);

/* Methods */
public :
	int				AddPhoneNumber(PhoneNumber phoneNumber);
	int				ModifyPhoneNumber(size_t index, std::string phoneNumber);
	int				ModifyPhoneNumber(size_t index, PhoneNumber phoneNumber);
	int				ModifyPhoneNumber(std::string from, std::string to);
	int				ModifyPhoneNumber(PhoneNumber from, PhoneNumber to);
	int				DeletePhoneNumber(size_t index);
	int				DeletePhoneNumber(PhoneNumber phoneNumber);
	PhoneNumber		GetPhoneNumber(size_t index) const;
	size_t			GetPhoneNumbersSize(void) const;

	int				SetStringData(std::string title, std::string value);
	std::string		GetStringData(std::string title) const;

#define MY_ADDRESS_DATA_NAME				"NAME"
#define MY_ADDRESS_DATA_PHONE_NUMBERS		"PHONE_NUMBERS"
#define MY_ADDRESS_DATA_HOME_ADDRESS		"HOME_ADDRESS"
#define MY_ADDRESS_DATA_OFFICE_ADDRESS		"OFFICE_ADDRESS"
#define MY_ADDRESS_DATA_GROUP_NAME			"GROUP_NAME"
#define MY_ADDRESS_DATA_EMAIL				"EMAIL"
#define MY_ADDRESS_DATA_URL					"URL"
#define MY_ADDRESS_DATA_BIRTHDAY			"BIRTHDAY"

	int				SetName(std::string name);
	std::string		GetName(void) const;

	int				SetHomeAddress(std::string homeAddress);
	int				SetOfficeAddress(std::string officeAddress);
	std::string		GetHomeAddress(void) const;
	std::string		GetOfficeAddress(void) const;

	int				SetInvolvedGroup(std::string groupName);
	std::string		GetInvolvedGroup(void) const;

	int				SetEmail(std::string email);
	std::string		GetEmail(void) const;

	int				SetURL(std::string url);
	std::string		GetURL(void) const;

	int				SetBirthday(size_t year, size_t month, size_t day);
	size_t			GetBirthdayYear(void) const;
	size_t			GetBirthdayMonth(void) const;
	size_t			GetBirthdayDay(void) const;

#define	MY_ADDR_BIRTHDAY_NOT_SET	0
// if birthday is not set, return 0 in the method GetBirthdayYear(),
// GetBirthdayMonth(), GetBirthdayDay()

/* operator overriding */
	bool operator>(const MyAddress&);
	bool operator>=(const MyAddress&);
	bool operator<(const MyAddress&);
	bool operator<=(const MyAddress&);
	bool operator==(const MyAddress&);

/* Methods for I/O */
	friend std::ostream& operator<<(std::ostream& out, const MyAddress&);
	friend std::istream& operator>>(std::istream& in, MyAddress&);
};

///////////////////////////////////////////////////////////////////////////////////////

class AddressLoadFailException : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return "Wrong syntax for loading address";
	}
};


#endif

///////////////////////////////////////////////////////////////////////////////////////
