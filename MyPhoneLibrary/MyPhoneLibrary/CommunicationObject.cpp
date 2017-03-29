
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <time.h>
#include "CommunicationObject.h"

CommunicationObject::CommunicationObject()
	: m_sender(), m_timeYear(0), m_timeMonth(0), m_timeDay(0), m_timeHour(0), m_timeMinute(0), m_timeSecond(0)
{

}

CommunicationObject::CommunicationObject(PhoneNumber sender, PhoneNumber receiver)
	: m_sender(sender), m_receiver(receiver)
{
	SetCurrentTime();
}

CommunicationObject::CommunicationObject(const CommunicationObject& object)
{
	m_sender = object.m_sender;
	m_receiver = object.m_receiver;
	m_timeYear = object.m_timeYear; m_timeMonth = object.m_timeMonth; m_timeDay = object.m_timeDay;
	m_timeHour = object.m_timeHour; m_timeMinute = object.m_timeMinute; m_timeSecond = object.m_timeSecond;
}

CommunicationObject::CommunicationObject(PhoneNumber sender, PhoneNumber receiver, int year, int month, int day, int hour, int minute, int second)
	: m_sender(sender), m_receiver(receiver)
{
	SetTime(year, month, day, hour, minute, second);
}

CommunicationObject::~CommunicationObject()
{
}

int CommunicationObject::SetSender(PhoneNumber senderNumber)
{
	if (senderNumber.IsEmpty()) return 1;
	m_sender = senderNumber;
	return 0;
}

int CommunicationObject::SetSender(std::string senderNumber)
{
	PhoneNumber number(senderNumber);
	return SetSender(number);
}

PhoneNumber CommunicationObject::GetSender(void) const
{
	return m_sender;
}

int CommunicationObject::SetReceiver(PhoneNumber receiverNumber)
{
	if (receiverNumber.IsEmpty()) return 1;
	m_receiver = receiverNumber;
	return 0;
}

int CommunicationObject::SetReceiver(std::string receiverNumber)
{
	PhoneNumber number(receiverNumber);
	return SetReceiver(receiverNumber);
}

PhoneNumber CommunicationObject::GetReceiver(void) const
{
	return m_receiver;
}

void CommunicationObject::SetCurrentTime()
{
	time_t currentTime;
	struct tm* tmTime;

	time(&currentTime);
	
#pragma warning(push)
#pragma warning(disable:4996)
	tmTime = localtime(&currentTime);
#pragma warning(pop)

	SetYear(tmTime->tm_year + 1900);
	SetMonth(tmTime->tm_mon + 1);
	SetDay(tmTime->tm_mday);
	SetHour(tmTime->tm_hour);
	SetMinute(tmTime->tm_min);
	SetSecond(tmTime->tm_sec);
}

bool CommunicationObject::IsValidDate(void) const
{
	const static int DAY_LIMIT[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int dayLimit;

	if (m_timeMonth < 1 || m_timeMonth > 12 || m_timeHour < 0 || m_timeHour >= 60
		|| m_timeMinute < 0 || m_timeMinute >= 60 || m_timeSecond < 0 || m_timeSecond >= 60) return false;

	dayLimit = DAY_LIMIT[m_timeMonth - 1];

	// calculate leap year
	if (m_timeMonth == 2 && ((!(m_timeYear % 4) && (m_timeYear % 100)) || !(m_timeYear % 400))) ++dayLimit;
	if (m_timeDay < 1 || m_timeDay > dayLimit) return false;

	return true;
}

int	CommunicationObject::SetTime(int year, int month, int day, int hour, int minute, int second)
{
	if (SetYear(year)) return 1;
	if (SetMonth(month)) return 1;
	if (SetDay(day)) return 1;
	if (SetHour(hour)) return 1;
	if (SetMinute(minute)) return 1;
	if (SetSecond(second)) return 1;
	return 0;
}

int CommunicationObject::SetYear(int year)
{
	m_timeYear = year;
	return 0;
}

int CommunicationObject::GetYear() const
{
	return m_timeYear;
}

int CommunicationObject::SetMonth(int month)
{
	if (month < 1 || month > 12) return 1;
	m_timeMonth = month;
	return 0;
}

int CommunicationObject::GetMonth() const
{
	return m_timeMonth;
}

int CommunicationObject::SetDay(int day)
{
	int tmp = m_timeDay;
	m_timeDay = day;
	if (IsValidDate()) return 0;
	else
	{
		m_timeDay = tmp;
		return 1;
	}
}

int CommunicationObject::GetDay() const
{
	return m_timeDay;
}

int	CommunicationObject::SetHour(int hour)
{
	if (hour < 0 || hour >= 24) return 1;
	m_timeHour = hour;
	return 0;
}

int	CommunicationObject::GetHour() const
{
	return m_timeHour;
}

int CommunicationObject::SetMinute(int minute)
{
	if (minute < 0 || minute >= 60) return 1;
	m_timeMinute = minute;
	return 0;
}

int CommunicationObject::GetMinute() const
{
	return m_timeMinute;
}

int CommunicationObject::SetSecond(int second)
{
	if (second < 0 || second >= 60) return 1;
	m_timeSecond = second;
	return 0;
}

int CommunicationObject::GetSecond() const
{
	return m_timeSecond;
}

bool CommunicationObject::operator>(const CommunicationObject& operand)
{
	if (m_timeYear != operand.GetYear())			return m_timeYear > operand.GetYear();
	else if (m_timeMonth != operand.GetMonth())		return m_timeMonth > operand.GetMonth();
	else if (m_timeDay != operand.GetDay())			return m_timeDay > operand.GetDay();
	else if (m_timeHour != operand.GetHour())		return m_timeHour > operand.GetHour();
	else if (m_timeMinute != operand.GetMinute())	return m_timeMinute > operand.GetMinute();
	else return m_timeSecond > operand.GetSecond();
	// if time is all the same
	return false;
}

bool CommunicationObject::operator>=(const CommunicationObject& operand)
{
	if (m_timeYear != operand.GetYear())			return m_timeYear >= operand.GetYear();
	else if (m_timeMonth != operand.GetMonth())		return m_timeMonth >= operand.GetMonth();
	else if (m_timeDay != operand.GetDay())			return m_timeDay >= operand.GetDay();
	else if (m_timeHour != operand.GetHour())		return m_timeHour >= operand.GetHour();
	else if (m_timeMinute != operand.GetMinute())	return m_timeMinute >= operand.GetMinute();
	else return m_timeSecond >= operand.GetSecond();
	// if time is all the same
	return true;
}

bool CommunicationObject::operator<(const CommunicationObject& operand)
{
	if (m_timeYear != operand.GetYear())			return m_timeYear < operand.GetYear();
	else if (m_timeMonth != operand.GetMonth())		return m_timeMonth < operand.GetMonth();
	else if (m_timeDay != operand.GetDay())			return m_timeDay < operand.GetDay();
	else if (m_timeHour != operand.GetHour())		return m_timeHour < operand.GetHour();
	else if (m_timeMinute != operand.GetMinute())	return m_timeMinute < operand.GetMinute();
	else return m_timeSecond < operand.GetSecond();
	// if time is all the same
	return false;
}

bool CommunicationObject::operator<=(const CommunicationObject& operand)
{
	if (m_timeYear != operand.GetYear())			return m_timeYear <= operand.GetYear();
	else if (m_timeMonth != operand.GetMonth())		return m_timeMonth <= operand.GetMonth();
	else if (m_timeDay != operand.GetDay())			return m_timeDay <= operand.GetDay();
	else if (m_timeHour != operand.GetHour())		return m_timeHour <= operand.GetHour();
	else if (m_timeMinute != operand.GetMinute())	return m_timeMinute <= operand.GetMinute();
	else return m_timeSecond <= operand.GetSecond();
	// if time is all the same
	return true;
}

std::ostream& operator<<(std::ostream& out, const CommunicationObject& object)
{
	if (object.m_sender.IsEmpty() && !object.m_receiver.IsEmpty())
		out << "To " + object.m_receiver.GetPhoneNumber() << " ";
	else if (!object.m_sender.IsEmpty() && object.m_receiver.IsEmpty())
		out << "From " + object.m_sender.GetPhoneNumber() << " ";
	else out << "FromTo " << object.m_sender << " " << object.m_receiver << " ";

	if (object.IsValidDate())
	{
		out << object.GetYear() << "." << object.GetMonth() << "." << object.GetDay() << " "
			<< object.GetHour() << ":" << object.GetMinute() << ":" << object.GetSecond() << std::endl;
	}

	else
	{
		out << "0.0.0 0:0:0";
	}

	return out;
}

std::istream& operator>>(std::istream& in, CommunicationObject& object)
{
	std::string tmp;
	int year, month, day, hour, minute, second;

	in >> tmp;

	if (tmp == "From") in >> object.m_sender;
	else if (tmp == "To") in >> object.m_receiver;
	else in >> object.m_sender >> object.m_receiver;

	in >> tmp;
	std::replace_if(tmp.begin(), tmp.end(), std::bind2nd(std::equal_to<char>(), '.'), ' ');
	std::stringstream s1(tmp);
	s1 >> year >> month >> day;

	in >> tmp;
	std::replace_if(tmp.begin(), tmp.end(), std::bind2nd(std::equal_to<char>(), ':'), ' ');
	std::stringstream s2(tmp);
	s2 >> hour >> minute >> second;

	object.SetTime(year, month, day, hour, minute, second);

	return in;
}