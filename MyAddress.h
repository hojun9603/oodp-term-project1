
#pragma once

#include <string>
#include "TelephoneNumber.h"
#include <vector>

using namespace std;

class MyAddress
{
/* Member Variables */
protected :
	std::string					m_name;
	vector<TelephoneNumber>		m_number;
	std::string					m_email;

	int							m_birthdayYear;
	int							m_birthdayMonth;
	int							m_birthdayDay;

	std::string					m_group;

/* Constructor & Destructor */
public :
	MyAddress(void);
	~MyAddress(void);

/* Methods */
	int				SetName(std::string name);

	int				AddNumber(TelephoneNumber number);
	int				ModifyNumber(size_t index, TelephoneNumber number);
	int				ExchangeNumber(size_t index1, size_t index2);
	int				DeleteNumber(TelephoneNumber number);
	int				DeleteNumber(size_t index);

	int				SetEmail(std::string email);

	int				SetBirthDay(int Year, int Month, int Day);

	int				SetGroup(std::string group);

/* Getter */
	std::string		GetName(void) const;
	std::string		GetTelephoneNumber(size_t index = 0) const;
	std::string		GetEmail(void) const;
	int				GetBirthDayYear(void) const;
	int				GetBirthDayMonth(void) const;
	int				GetBirthDayDay(void) const;
	std::string		GetGroup(void) const;
};