
#include "SMSMessage.h"

extern std::string Trim(const std::string str);

SMSMessage::SMSMessage()
	: m_message("")
{

}

SMSMessage::SMSMessage(PhoneNumber sender, PhoneNumber receiver)
	: CommunicationObject(sender, receiver), m_message("")
{

}

SMSMessage::SMSMessage(PhoneNumber sender, PhoneNumber receiver, std::string message)
	: CommunicationObject(sender, receiver)
{
	SetMessage(message);
}

SMSMessage::SMSMessage(const SMSMessage& object)
	: CommunicationObject(object)
{
	SetMessage(object.GetMessage());
}

SMSMessage::SMSMessage(PhoneNumber sender, PhoneNumber receiver, std::string message, int year, int month, int day, int hour, int minute, int second)
	: CommunicationObject(sender, receiver, year, month, day, hour, minute, second)
{
	SetMessage(message); 
}

SMSMessage::~SMSMessage()
{
}

int SMSMessage::SetMessage(std::string message)
{
	m_message = message;
	return 0;
}

std::string SMSMessage::GetMessage(void) const
{
	return m_message;
}

std::ostream& operator<<(std::ostream& out, const SMSMessage& object)
{
	out << (CommunicationObject&)object;
	out << "[SMS MESSAGE START]" << std::endl;
	out << object.m_message << std::endl;
	out << "[SMS MESSAGE END]" << std::endl;

	return out;
}

std::istream& operator>>(std::istream& in, SMSMessage& object)
{
	std::string tmp;
	in >> (CommunicationObject&)object;
	
	do
	{
		std::getline(in, tmp);
		tmp = Trim(tmp);
		if (in.eof()) return in;
	} while (tmp == "");

	if (tmp != "[SMS MESSAGE START]") goto MESSAGE_GET_EXCEPTION;

	do
	{
		if (in.eof()) goto MESSAGE_GET_EXCEPTION;
		std::getline(in, tmp);

		if (Trim(tmp) == "[SMS MESSAGE END]") break;
		object.SetMessage(object.GetMessage() + tmp);
	} while (1);

	return in;

MESSAGE_GET_EXCEPTION :
	CommunicationLoadFailException e;
	throw e;
	return in;
}

bool SMSMessage::operator>(const SMSMessage& operand)
{
	PhoneNumber pivot1, pivot2;
	pivot1 = m_sender; if (pivot1.IsEmpty()) pivot1 = m_receiver;
	pivot2 = operand.m_sender; if (pivot2.IsEmpty()) pivot2 = operand.m_receiver;
	if (pivot1.GetPhoneNumber() != pivot2.GetPhoneNumber())
	{
		if (pivot1.GetPhoneNumber().compare(pivot2.GetPhoneNumber()) > 0)
			return true;
		else return false;
	}

	else
	{
		return CommunicationObject::operator>(operand);
	}
}

bool SMSMessage::operator>=(const SMSMessage& operand)
{
	PhoneNumber pivot1, pivot2;
	pivot1 = m_sender; if (pivot1.IsEmpty()) pivot1 = m_receiver;
	pivot2 = operand.m_sender; if (pivot2.IsEmpty()) pivot2 = operand.m_receiver;
	if (pivot1.GetPhoneNumber() != pivot2.GetPhoneNumber())
	{
		if (pivot1.GetPhoneNumber().compare(pivot2.GetPhoneNumber()) >= 0)
			return true;
		else return false;
	}

	else
	{
		return CommunicationObject::operator>=(operand);
	}
}

bool SMSMessage::operator<(const SMSMessage& operand)
{
	PhoneNumber pivot1, pivot2;
	pivot1 = m_sender; if (pivot1.IsEmpty()) pivot1 = m_receiver;
	pivot2 = operand.m_sender; if (pivot2.IsEmpty()) pivot2 = operand.m_receiver;
	if (pivot1.GetPhoneNumber() != pivot2.GetPhoneNumber())
	{
		if (pivot1.GetPhoneNumber().compare(pivot2.GetPhoneNumber()) < 0)
			return true;
		else return false;
	}

	else
	{
		return CommunicationObject::operator<(operand);
	}
}

bool SMSMessage::operator<=(const SMSMessage& operand)
{
	PhoneNumber pivot1, pivot2;
	pivot1 = m_sender; if (pivot1.IsEmpty()) pivot1 = m_receiver;
	pivot2 = operand.m_sender; if (pivot2.IsEmpty()) pivot2 = operand.m_receiver;
	if (pivot1.GetPhoneNumber() != pivot2.GetPhoneNumber())
	{
		if (pivot1.GetPhoneNumber().compare(pivot2.GetPhoneNumber()) <= 0)
			return true;
		else return false;
	}

	else
	{
		return CommunicationObject::operator<=(operand);
	}
}