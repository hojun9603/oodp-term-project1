#include <iostream>
#include <string>
#include "MyAddress.h"
#include "TelephoneNumber.h"

MyAddress::MyAddress(void)
{
	TelephoneNumber NewTelephoneNumber;

	m_name = "Null";
	m_number[0] = NewTelephoneNumber;
	m_email = "user@email.com";
	m_birthdayYear = 0;
	m_birthdayMonth = 0;
	m_birthdayDay = 0;
	m_group = "Null";
}

MyAddress::~MyAddress(void)
{
	std::cout << "Address is deleted" << endl;
}

int MyAddress::SetName(std::string name)
{
	m_name = name;
	return 0;
}

int MyAddress::AddNumber(TelephoneNumber number)
{
	/*append the new number to the m_name's list of phone number*/
	m_number.push_back(number);
	return 0;
}

int MyAddress::ModifyNumber(size_t index, TelephoneNumber number)
{
	m_number[index] = number;
	return 0;
}

int MyAddress::ExchangeNumber(size_t index1, size_t index2)
{
	TelephoneNumber temp;
	temp = m_number[index1];
	m_number[index1] = m_number[index2];
	m_number[index2] = temp;
	return 0;
}

int MyAddress::DeleteNumber(TelephoneNumber number)
{
	int i, j;
	TelephoneNumber temp;

	for (i=0;i<m_number.size();i++)
	{
		if (m_number[i].GetTelephoneNumber().compare(number.GetTelephoneNumber()) == 0)	/*when it finds phone number to delete, activate the if statement*/
		{
			for (j = i; j < m_number.size() - 1; j++)			/*pull the other rest phone numbers through swapping numbers*/
				temp = m_number[j];
				m_number[j] = m_number[j + 1];	
				m_number[j + 1] = temp;
			m_number.resize(m_number.size() - 1);
		}
		return 0;																	
	}
	return 1;													/*when there is no phone number to delete, return 1*/
}

int MyAddress::DeleteNumber(size_t index)
{
	int i;
	TelephoneNumber temp;

	if (0<= index <= m_number.size() - 1)
	{
		for (i = index; i < m_number.size() - 1; i++)			/*pull the other rest phone numbers through swapping numbers*/
		{
			temp = m_number[i];
			m_number[i] = m_number[i + 1];
			m_number[i + 1] = temp;
			m_number.resize(m_number.size() - 1);
		}
		return 0;
	}		
	return 1;													/*when there is no phone number to delete, return 1*/
}

int MyAddress::SetEmail(std::string email)
{
	m_email = email;
	return 0;
}

int MyAddress::SetBirthDay(int Year, int Month, int Day)
{
	m_birthdayYear = Year;
	m_birthdayMonth = Month;
	m_birthdayDay = Day;
	return 0;
}

int MyAddress::SetGroup(std::string group)
{
	m_group = group;
	return 0;
}

std::string MyAddress::GetName(void) const
{
	return m_name;
}

std::string MyAddress::GetTelephoneNumber(size_t index = 0) const
{	
	return m_number[index].GetTelephoneNumber();
}

std::string MyAddress::GetEmail(void) const
{
	return m_email;
}

int MyAddress::GetBirthDayYear(void) const
{
	return m_birthdayYear;
}

int MyAddress::GetBirthDayMonth(void) const
{
	return m_birthdayMonth;
}

int MyAddress::GetBirthDayDay(void) const
{
	return m_birthdayDay;
}

std::string MyAddress::GetGroup(void) const
{
	return m_group;
}
