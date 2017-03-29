
#include "PhoneNumber.h"

// definition of static variable
const std::string PhoneNumber::AREA_CODE[] = {
	"02", "051", "053", "032", "062", "042", "052",
	"044", "031", "033", "043", "041", "063", "061",
	"054", "055", "064",
	"010", "011", "012", "013", "014", "015", "016", "017", "018", "019"
};

#define NUMBER_OF_AREA_CODE		27

// definition of constructors and destructor

PhoneNumber::PhoneNumber(void) : m_phoneNumber("") {}

PhoneNumber::PhoneNumber(std::string phoneNumber)
{
	SetPhoneNumber(phoneNumber);
}

PhoneNumber::PhoneNumber(const PhoneNumber& phoneNumber) : m_phoneNumber(phoneNumber.GetPhoneNumber()) {}
PhoneNumber::~PhoneNumber() {}

int PhoneNumber::SetPhoneNumber(std::string number)
{
	std::string::iterator it;
	int i;
	bool bAllowedChar;

	// check that the number string has disallowed characters
	for (it = number.begin(); it != number.end(); ++it)
	{
		bAllowedChar = false;
		for (i = 0; i < PHONE_NUMBER_ALLOWED_STRING_SIZE; ++i)
		{
			if (PHONE_NUMBER_ALLOWED_STRING[i] == *it)
			{
				bAllowedChar = true;
				break;
			}
		}

		// if the character is disallowed character, throw exception
		if (!bAllowedChar)
		{
			NotPhoneNumberException e(number);
			throw e;
			return 1;
		}
	}

	m_phoneNumber = number;
	Normalize();

	// return success
	return 0;
}

std::string PhoneNumber::GetPhoneNumber(void) const
{
	return m_phoneNumber;
}

int PhoneNumber::Normalize(void)
{
	std::string normalizedString;
	size_t index = 0, i, remainedSize;

	// remove all "-" first
	m_phoneNumber.erase(std::remove(m_phoneNumber.begin(), m_phoneNumber.end(), '-'), m_phoneNumber.end());

	// search first code(area code or cell phone number)
	for (i = 0; i < NUMBER_OF_AREA_CODE; ++i)
	{
 		if (!m_phoneNumber.find(PhoneNumber::AREA_CODE[i]))
		{
			index = PhoneNumber::AREA_CODE[i].size();
			if (index == m_phoneNumber.size()) return 0;
			normalizedString = m_phoneNumber.substr(0, index) + "-";
			break;
		}
	}

	// if no AREA_CODE, there is no '-'
	if (i == NUMBER_OF_AREA_CODE) return 0;

	remainedSize = m_phoneNumber.size() - index;

	if (remainedSize <= 3)		// xx-xxx or xxx-xxx
	{
		normalizedString += m_phoneNumber.substr(index);
	}

	else if (remainedSize > 3 && remainedSize <= 7)		// xx-xxx-xxxx
	{
		normalizedString += m_phoneNumber.substr(index, 3) + "-" + m_phoneNumber.substr(index + 3);
	}

	else	// xx-xxxx-xxxx. It is only length 8
	{
		normalizedString += m_phoneNumber.substr(index, 4) + "-" + m_phoneNumber.substr(index + 4);
	}

	m_phoneNumber = normalizedString;
	// return success
	return 0;
}

bool PhoneNumber::IsEmpty(void) const
{
	if (m_phoneNumber.size()) return false;
	return true;
}

bool PhoneNumber::operator==(const PhoneNumber& phoneNumber) const
{
	// if the number is the equal with the operand, return true
	// and if not, return false
	if (m_phoneNumber == phoneNumber.GetPhoneNumber()) return true;
	return false;
}

PhoneNumber& PhoneNumber::operator=(const PhoneNumber& phoneNumber)
{
	// substitute the number
	m_phoneNumber = phoneNumber.GetPhoneNumber();
	return *this;
}

PhoneNumber& PhoneNumber::operator=(const std::string& phoneNumber)
{
	// substitute the number
	SetPhoneNumber(phoneNumber);
	return *this;
}

bool PhoneNumber::operator>(const PhoneNumber& operand) const
{
	return m_phoneNumber > operand.GetPhoneNumber();
}

bool PhoneNumber::operator<(const PhoneNumber& operand) const
{
	return m_phoneNumber < operand.GetPhoneNumber();
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& phoneNumber)
{
	out << phoneNumber.GetPhoneNumber();
	return out;
}

std::istream& operator>>(std::istream& in, PhoneNumber& phoneNumber)
{
	std::string numberTemp;
	in >> numberTemp;
	phoneNumber.SetPhoneNumber(numberTemp);
	return in;
}

NotPhoneNumberException::NotPhoneNumberException(std::string wrongString) noexcept
	: m_wrongString(wrongString)
{}

NotPhoneNumberException::NotPhoneNumberException(NotPhoneNumberException& e) noexcept
	: m_wrongString(e.m_wrongString)
{}