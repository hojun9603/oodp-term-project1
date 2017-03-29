
#include <sstream>
#include "MyAddress.h"

// functions for using internally

std::string Trim(const std::string str)
{
	size_t firstWord, lastWord;

	firstWord = str.find_first_not_of(" \a\b\f\n\r\t\v");
	lastWord = str.find_last_not_of(" \a\b\f\n\r\t\v");

	if (firstWord == std::string::npos) return "";
	return std::string(str, firstWord, lastWord - firstWord + 1);
}

// definition of constructor and destructor

int MyAddress::AddressIDGenerator = 1;

MyAddress::MyAddress(void) :
	m_addressID(AddressIDGenerator++),
	m_name(""),
	m_homeAddress(""), m_officeAddress(""),
	m_involvedGroup(""),
	m_email(""),
	m_url(""),
	m_birthdayYear(0), m_birthdayMonth(0), m_birthdayDay(0)
{

}

MyAddress::~MyAddress(void)
{

}

int MyAddress::AddPhoneNumber(PhoneNumber phoneNumber)
{
	std::vector<PhoneNumber>::iterator it;

	// find the number has already existed in the list
	it = find(m_phoneNumbers.begin(), m_phoneNumbers.end(), phoneNumber);

	// if not exists, add the number to the list
	if (it == m_phoneNumbers.end())
	{
		m_phoneNumbers.push_back(phoneNumber);
		// return sucess
		return 0;
	}

	// if same number exists in the list, return failed
	return 1;
}

int MyAddress::ModifyPhoneNumber(size_t index, std::string phoneNumber)
{
	return ModifyPhoneNumber(index, PhoneNumber(phoneNumber));
}

int MyAddress::ModifyPhoneNumber(size_t index, PhoneNumber phoneNumber)
{
	// if index is not valid, return failed
	if (index >= m_phoneNumbers.size()) return 1;
	
	// modify and return success
	m_phoneNumbers[index] = phoneNumber;
	return 0;
}

int MyAddress::ModifyPhoneNumber(std::string from, std::string to)
{
	return ModifyPhoneNumber(PhoneNumber(from), PhoneNumber(to));
}

int MyAddress::ModifyPhoneNumber(PhoneNumber from, PhoneNumber to)
{
	std::vector<PhoneNumber>::iterator it;

	// find number
	it = find(m_phoneNumbers.begin(), m_phoneNumbers.end(), from);

	// if not found, return failed
	if (it == m_phoneNumbers.end()) return 1;

	// if found, modify the number and return success
	*it = to;
	return 0;
}

int MyAddress::DeletePhoneNumber(size_t index)
{
	std::vector<PhoneNumber>::iterator it;

	// if index is not valid, return failed
	if (index >= m_phoneNumbers.size()) return 1;

	it = m_phoneNumbers.begin() + index;

	// erase the data indexed and return success
	m_phoneNumbers.erase(it, it + 1);
	return 0;
}

int MyAddress::DeletePhoneNumber(PhoneNumber phoneNumber)
{
	std::vector<PhoneNumber>::iterator it;

	// find the number
	it = find(m_phoneNumbers.begin(), m_phoneNumbers.end(), phoneNumber);

	// if the number does not exist, return failed
	if (it == m_phoneNumbers.end()) return 1;

	// erase the number
	m_phoneNumbers.erase(it, it + 1);
	return 0;
}

PhoneNumber MyAddress::GetPhoneNumber(size_t index) const
{
	// if invalid index, return PhoneNumber instance that has a empty number
	if (index >= m_phoneNumbers.size()) return PhoneNumber("");
	// return the phone number indexed.
	return m_phoneNumbers[index];
}

size_t MyAddress::GetPhoneNumbersSize(void) const
{
	return m_phoneNumbers.size();
}

int MyAddress::SetStringData(std::string title, std::string value)
{
	if (title == MY_ADDRESS_DATA_NAME) return SetName(value);
	if (title == MY_ADDRESS_DATA_HOME_ADDRESS) return SetHomeAddress(value);
	else if (title == MY_ADDRESS_DATA_OFFICE_ADDRESS) return SetOfficeAddress(value);
	else if (title == MY_ADDRESS_DATA_GROUP_NAME) return SetInvolvedGroup(value);
	else if (title == MY_ADDRESS_DATA_EMAIL) return SetEmail(value);
	else if (title == MY_ADDRESS_DATA_URL) return SetURL(value);
	else if (title == MY_ADDRESS_DATA_BIRTHDAY)
	{
		std::stringstream valueInput(value);
		int year, month, day;
		valueInput >> year >> month >> day;
		return SetBirthday(year, month, day);
	}
	else if (title == MY_ADDRESS_DATA_PHONE_NUMBERS)
	{
		std::stringstream valueInput(value);
		PhoneNumber phoneNumber;

		m_phoneNumbers.clear();

		do
		{
			try {
				valueInput >> phoneNumber;
				m_phoneNumbers.push_back(phoneNumber);
			}
			catch (NotPhoneNumberException e)
			{
				return 1;
			}
			
		} while (!valueInput.eof());

		return 0;
	}

	return 1;
}

std::string MyAddress::GetStringData(std::string title) const
{
	if (title == MY_ADDRESS_DATA_NAME) return GetName();
	if (title == MY_ADDRESS_DATA_HOME_ADDRESS) return GetHomeAddress();
	else if (title == MY_ADDRESS_DATA_OFFICE_ADDRESS) return GetOfficeAddress();
	else if (title == MY_ADDRESS_DATA_GROUP_NAME) return GetInvolvedGroup();
	else if (title == MY_ADDRESS_DATA_EMAIL) return GetEmail();
	else if (title == MY_ADDRESS_DATA_URL) return GetURL();
	else if (title == MY_ADDRESS_DATA_BIRTHDAY)
	{
		std::stringstream sOut;
		int year = GetBirthdayYear(), month = GetBirthdayMonth(), day = GetBirthdayDay();
		if (!year || !month || !day) return "";
		sOut << year << " " << month << " " << day;
		return sOut.str();
	}
	else if (title == MY_ADDRESS_DATA_PHONE_NUMBERS)
	{
		std::string sOut = "";
		std::vector<PhoneNumber>::const_iterator it;

		for (it = m_phoneNumbers.begin(); it != m_phoneNumbers.end(); ++it)
			sOut += " " + it->GetPhoneNumber();

		return sOut;
	}

	return "";
}

int MyAddress::SetName(std::string name)
{
	m_name = name;
	return 0;
}

std::string MyAddress::GetName() const
{
	return m_name;
}

int MyAddress::SetHomeAddress(std::string homeAddress)
{
	m_homeAddress = homeAddress;
	return 0;
}

int MyAddress::SetOfficeAddress(std::string officeAddress)
{
	m_officeAddress = officeAddress;
	return 0;
}

std::string MyAddress::GetHomeAddress(void) const
{
	return m_homeAddress;
}

std::string MyAddress::GetOfficeAddress(void) const
{
	return m_officeAddress;
}

int MyAddress::SetInvolvedGroup(std::string groupName)
{
	m_involvedGroup = groupName;
	return 0;
}

std::string MyAddress::GetInvolvedGroup(void) const
{
	return m_involvedGroup;
}

int MyAddress::SetEmail(std::string email)
{
	std::string::iterator it;
	size_t countAt = 0;

	// check the number of @
	it = email.begin();

	do
	{
		it = find(it, email.end(), '@');
		if (it != email.end())
		{
			++it;
			++countAt;
		}
		else break;
	} while (1);
	// if the number of @ is not 1, return failed
	if (countAt != 1) return 1;

	// set the email and return success
	m_email = email;
	return 0;
}

std::string MyAddress::GetEmail(void) const
{
	return m_email;
}

int MyAddress::SetURL(std::string url)
{
	m_url = url;
	return 0;
}

std::string MyAddress::GetURL(void) const
{
	return m_url;
}

int MyAddress::SetBirthday(size_t year, size_t month, size_t day)
{
	const static size_t DAYS_IN_MONTH[12] =
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	size_t DayCount;

	// if month is not valid, return failed
	if (month < 0 || month > 12) return 1;

	// get the number of day in the month
	DayCount = DAYS_IN_MONTH[month - 1];

	// calculate whether it is leap year
	if (month == 2)
	{
		if (!(year % 4) && (year % 100) || !(year % 400)) ++DayCount;
	}

	// if day is not valid, return failed
	if (day < 1 || day > DayCount) return 1;

	m_birthdayYear = year;
	m_birthdayMonth = month;
	m_birthdayDay = day;

	// return success
	return 0;
}

size_t MyAddress::GetBirthdayYear(void) const
{
	return m_birthdayYear;
}

size_t MyAddress::GetBirthdayMonth(void) const
{
	return m_birthdayMonth;
}

size_t MyAddress::GetBirthdayDay(void) const
{
	return m_birthdayDay;
}

int MyAddress::GetAddressID(void) const
{
	return m_addressID;
}

bool MyAddress::operator>(const MyAddress& operand)
{
	if (m_name.compare(operand.GetName()) > 0) return true;
	return false;
}

bool MyAddress::operator>=(const MyAddress& operand)
{
	if (m_name.compare(operand.GetName()) >= 0) return true;
	return false;
}

bool MyAddress::operator<(const MyAddress& operand)
{
	if (m_name.compare(operand.GetName()) < 0) return true;
	return false;
}

bool MyAddress::operator<=(const MyAddress& operand)
{
	if (m_name.compare(operand.GetName()) <= 0) return true;
	return false;
}

bool MyAddress::operator==(const MyAddress& operand)
{
	return m_name == operand.GetName();
}

std::ostream& operator<<(std::ostream& out, const MyAddress& address)
{
	static const std::string SAVE_LIST[] = {
		MY_ADDRESS_DATA_NAME,
		MY_ADDRESS_DATA_PHONE_NUMBERS,
		MY_ADDRESS_DATA_HOME_ADDRESS,
		MY_ADDRESS_DATA_OFFICE_ADDRESS,
		MY_ADDRESS_DATA_GROUP_NAME,
		MY_ADDRESS_DATA_EMAIL,
		MY_ADDRESS_DATA_URL,
		MY_ADDRESS_DATA_BIRTHDAY
	};

	std::vector<PhoneNumber>::const_iterator it;
	std::string sOut;
	int i;
	
	out << "[ADDRESS START]" << std::endl;

	for (i = 0; i < sizeof(SAVE_LIST) / sizeof(std::string); ++i)
	{
		sOut = address.GetStringData(SAVE_LIST[i]);
		if (sOut != "")
			out << SAVE_LIST[i] << "=" << sOut << std::endl;
	}

	out << "[ADDRESS_END]" << std::endl;

	return out;
}

std::istream& operator>>(std::istream& in, MyAddress& address)
{
	std::string loadedString;
	std::string title, value;
	size_t index;
	
	do
	{
		if (in.eof()) return in;
		std::getline(in, loadedString);
		loadedString = Trim(loadedString);
	} while (loadedString == "");

	// syntax checking
	if (loadedString != "[ADDRESS START]") goto LOAD_EXCEPTION;

	do
	{
		// get line
		std::getline(in, loadedString);

		// if meet EOF, generate exception
		if (in.eof()) goto LOAD_EXCEPTION;
		
		// if it is end of data,
		loadedString = Trim(loadedString);
		if (loadedString == "") continue;
		if (loadedString == "[ADDRESS_END]") break;

		// syntax checking
		index = loadedString.find('=');
		if (index == std::string::npos) goto LOAD_EXCEPTION;

		// load string data from file
		title = loadedString.substr(0, index);
		value = loadedString.substr(index + 1);
		if (address.SetStringData(title, value)) goto LOAD_EXCEPTION;

	} while (1);

	return in;

LOAD_EXCEPTION :
	while (1)
	{
		std::getline(in, loadedString);
		if (in.eof() || Trim(loadedString) == "[ADDRESS_END]") break;
	}
	AddressLoadFailException e;
	throw e;
	return in;
}



























