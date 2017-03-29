

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "MyAddressBook.h"

#define SWAP(Type, a, b)	{ Type tmp = a; a = b; b = tmp; }

extern std::string Trim(const std::string str);

MyAddressBook::MyAddressBook()
{
}

MyAddressBook::~MyAddressBook()
{
}

int MyAddressBook::AddAddress(const MyAddress& address)
{
	size_t i;

	// check this address is addable
	if (!CheckValidAddress(address)) return 1;

	// if finishing checking, insert address
	m_myAddresses.push_back(address);

	// if one element added, insert the right position to be sorted
	for (i = m_myAddresses.size() - 1; i >= 1; --i)
	{
		if (m_myAddresses[i - 1] > m_myAddresses[i])
		{
			SWAP(MyAddress, m_myAddresses[i - 1], m_myAddresses[i])
		}

		else break;
	}

	for (i = 0; i < address.GetPhoneNumbersSize(); ++i)
		UpdateNumber(address.GetPhoneNumber(i), address.GetName());

	UpdateAddress(i);

	return 0;
}

int MyAddressBook::DeleteAddress(size_t index)
{
	size_t i;
	if (index >= m_myAddresses.size()) return 1;

	for (i = 0; i < m_myAddresses[index].GetPhoneNumbersSize(); ++i)
		RemoveNumber(m_myAddresses[index].GetPhoneNumber(i));

	m_myAddresses.erase(m_myAddresses.begin() + index);
	return 0;
}

MyAddress* MyAddressBook::GetAddress(size_t index)
{
	if (index >= m_myAddresses.size()) return nullptr;
	else return &(m_myAddresses[index]);
}

int MyAddressBook::UpdateAddress(size_t index)
{
	if (index >= m_myAddresses.size()) return 1;

	size_t i;
	for (i = 0; i < m_myAddresses[index].GetPhoneNumbersSize(); ++i)
	{
		UpdateNumber(m_myAddresses[index].GetPhoneNumber(i), m_myAddresses[index].GetName());
	}

	return 0;
}

int	MyAddressBook::UpdateAddress(size_t index, MyAddress& address)
{
	if (index >= m_myAddresses.size()) return 1;
	if (m_myAddresses[index].GetName() == address.GetName())
	{
		m_myAddresses[index] = address;
		return UpdateAddress(index);
	}

	else
	{
		m_myAddresses[index] = address;
		
		while (index > 0 && m_myAddresses[index] < m_myAddresses[index - 1])
		{
			SWAP(MyAddress, m_myAddresses[index - 1], m_myAddresses[index])
				index--;
		}

		while (index < m_myAddresses.size() - 1 && m_myAddresses[index] > m_myAddresses[index + 1])
		{
			SWAP(MyAddress, m_myAddresses[index + 1], m_myAddresses[index])
		}
	}

	return 0;
}

int MyAddressBook::SearchAddress(std::string name)
{
	std::vector<MyAddress>::iterator it;

	it = std::lower_bound(m_myAddresses.begin(), m_myAddresses.end(), name,
		[](const MyAddress& addr1, const std::string& operand) -> bool
	{
		if (strcmp(addr1.GetName().data(), operand.data()) < 0) return true;
		else return false;
	});

	// if not found, return -1, or if found, return the first element index
	if (it == m_myAddresses.end()) return -1;
	else if(it->GetName() == name) return (it - m_myAddresses.begin());
	else return -1;
}

int MyAddressBook::SearchAddress(const PhoneNumber& phoneNumber)
{
	std::map<PhoneNumber, std::string>::iterator it;
	it = m_namesByNumbers.find(phoneNumber);

	if (it == m_namesByNumbers.end()) return -1;
	return SearchAddress(it->second);
}

size_t MyAddressBook::GetAddressCount(void) const
{
	return m_myAddresses.size();
}

bool MyAddressBook::CheckValidAddress(MyAddress address)
{
	size_t i;
	std::string groupChecker;
	std::map<PhoneNumber, std::string>::iterator numberChecker;
	groupChecker = address.GetInvolvedGroup();
	if (groupChecker != "" && find(m_myGroups.begin(), m_myGroups.end(), groupChecker) == m_myGroups.end())
		return false;

	for (i = 0; i < address.GetPhoneNumbersSize(); ++i)
	{
		numberChecker = m_namesByNumbers.find(address.GetPhoneNumber(i));
		if (numberChecker != m_namesByNumbers.end()) return false;
	}

	if (address.GetName() == "" || !address.GetPhoneNumbersSize()) return false;

	return true;
}

int MyAddressBook::UpdateNumber(const PhoneNumber& number, std::string name)
{
	m_namesByNumbers[number] = name;
	return 0;
}

int MyAddressBook::RemoveNumber(const PhoneNumber& number)
{
	m_namesByNumbers.erase(number);
	return 0;
}

int MyAddressBook::AddGroup(std::string groupName)
{
	std::vector<std::string>::iterator it;
	int i;
	std::string swapTemp;

	// if name already exists, return failed
	it = find(m_myGroups.begin(), m_myGroups.end(), groupName);
	if (it != m_myGroups.end()) return 1;

	// insertion
	m_myGroups.push_back(groupName);
	for (i = m_myGroups.size() - 1; i >= 1; --i)
	{
		if (m_myGroups[i - 1] > m_myGroups[i])
			SWAP(std::string, m_myGroups[i - 1], m_myGroups[i])

		else break;
	}

	return 0;
}

int MyAddressBook::DeleteGroup(std::string groupName)
{
	std::vector<std::string>::iterator it;

	it = find(m_myGroups.begin(), m_myGroups.end(), groupName);
	if (it == m_myGroups.end()) return 1;

	m_myGroups.erase(it);
	return 0;
}

std::string* MyAddressBook::GetGroup(size_t index)
{
	if (index >= m_myGroups.size()) return nullptr;
	return &(m_myGroups[index]);
}

int MyAddressBook::AddCall(Call& call)
{
	int index = m_myCalls.size();
	m_myCalls.push_back(call);

	while (index >= 1 && m_myCalls[index] > m_myCalls[index - 1])
	{
		SWAP(Call, m_myCalls[index], m_myCalls[index - 1]);
		index--;
	}

	return 0;
}

int MyAddressBook::DeleteCall(size_t index)
{
	if (index >= m_myCalls.size()) return 1;
	m_myCalls.erase(m_myCalls.begin() + index);
	return 0;
}

Call* MyAddressBook::GetCall(size_t index)
{
	if (index >= m_myCalls.size()) return nullptr;
	else return &(m_myCalls[index]);
}

size_t MyAddressBook::GetCallCount(void) const
{
	return m_myCalls.size();
}

int MyAddressBook::AddMessage(SMSMessage& message)
{
	int index = m_myMessages.size();
	m_myMessages.push_back(message);

	if (index < 1) return 0;
	while (index >= 1 && m_myMessages[index] < m_myMessages[index - 1])
	{
		SWAP(SMSMessage, m_myMessages[index], m_myMessages[index - 1]);
		index--;
	}

	return 0;
}

int MyAddressBook::DeleteMessage(size_t index)
{
	if (index >= m_myMessages.size()) return 1;
	m_myMessages.erase(m_myMessages.begin() + index);
	return 0;
}

SMSMessage* MyAddressBook::GetMessage(size_t index)
{
	if (index >= m_myMessages.size()) return nullptr;
	else return &(m_myMessages[index]);
}

int MyAddressBook::SearchFirstMessage(const PhoneNumber& number)
{
	SMSMessage tmp;
	tmp.SetSender(number);
	tmp.SetTime(1, 1, 1, 0, 0, 0);
	
 	std::vector<SMSMessage>::iterator index = std::lower_bound(m_myMessages.begin(), m_myMessages.end(), tmp);
	if (index == m_myMessages.end()) return -1;
	if (index->GetSender() == number || index->GetReceiver() == number) return (index - m_myMessages.begin());
	else return -1;
}

size_t MyAddressBook::GetMessageCount(void) const
{
	return m_myMessages.size();
}

int MyAddressBook::SortAddressByName()
{
	std::sort(m_myAddresses.begin(), m_myAddresses.end(), [](const MyAddress& address, const MyAddress& operand) -> bool
	{
		return address.GetName() > operand.GetName();
	});

	return 0;
}

int MyAddressBook::SortAddressByGroup()
{
	std::sort(m_myAddresses.begin(), m_myAddresses.end(), [](const MyAddress& address, const MyAddress& operand) -> bool
	{
		if (address.GetInvolvedGroup() != address.GetInvolvedGroup())
			return address.GetInvolvedGroup() > operand.GetInvolvedGroup();
		else return address.GetName() > operand.GetName();
	});

	return 0;
}

int  MyAddressBook::SetStringData(std::string title, std::string value)
{
	if(title == MY_ADDRBOOK_DATA_GROUP)
	{
		std::string groupName;
		std::stringstream valueInput(value);
		
		do
		{
			valueInput >> groupName;
			m_myGroups.push_back(groupName);
		} while (!valueInput.eof());
	}

	else return 1;

	return 0;
}

std::string  MyAddressBook::GetStringData(std::string title)
{
	if (title == MY_ADDRBOOK_DATA_GROUP)
	{
		std::stringstream sOut;
		for (auto it = m_myGroups.begin(); it != m_myGroups.end(); ++it)
		{
			if (it != m_myGroups.begin()) sOut << " ";
			sOut << *it;
		}

		return sOut.str();
	}

	return "";
}

int	MyAddressBook::SaveAddressFile(std::string fileName)
{
	std::fstream MyAddressBookSaveFile;

	std::vector<MyAddress>::iterator addressIndex = m_myAddresses.begin();
	int i = 0;

	MyAddressBookSaveFile.open(fileName, std::ios::out);


	if (MyAddressBookSaveFile.is_open() == false)							// error : no file, no save. return 1
	{
		std::cout << "error : there is no file to open" << std::endl;
		return 1;
	}

	else																	// open file and copy the values to save 
	{

		for (addressIndex = m_myAddresses.begin(); addressIndex < m_myAddresses.end(); addressIndex++)
		{
			MyAddressBookSaveFile << "[ADDRESS START]" << std::endl;

			MyAddressBookSaveFile <<
				"NAME			  = " << addressIndex->GetName() << std::endl <<
				"TELEPHONENUMBERS = " << addressIndex->GetPhoneNumber(0).GetPhoneNumber() << " " << addressIndex->GetPhoneNumber(1).GetPhoneNumber() << " " << addressIndex->GetPhoneNumber(2).GetPhoneNumber() << std::endl <<
				"HOME			  = " << addressIndex->GetHomeAddress() << std::endl <<
				"OFFICE           = " << addressIndex->GetOfficeAddress() << std::endl <<
				"EMAIL		      = " << addressIndex->GetEmail() << std::endl <<
				"URL			  = " << addressIndex->GetURL() << std::endl;
			//"BIRTHDAY = "		  << address.GetBirthdayYear() << " / " << address.GetBirthdayMonth << " / " << address.GetBirthdayDay << endl <<

			MyAddressBookSaveFile << "[ADDRESS END]" << std::endl;
		}
		MyAddressBookSaveFile.close();

	}
	return 0;

}

int	MyAddressBook::LoadAddressFile(std::string fileName)
{
	std::string loadedString;
	std::ifstream inputFile;
	std::string title, value;
	size_t index;
	int failedCount = 0;

	// if FAILED to open the file
	inputFile.open(fileName);
	if (!inputFile.is_open()) return -1;

	do
	{
		if (inputFile.eof()) goto FAIL_LOAD_ADDRESS_FILE;
		std::getline(inputFile, loadedString);

		loadedString = Trim(loadedString);
		if (loadedString == "") continue;

		index = loadedString.find('=');
		if (index == std::string::npos) goto FAIL_LOAD_ADDRESS_FILE;

		title = loadedString.substr(0, index);
		value = loadedString.substr(index + 1);

		SetStringData(title, value);
		break;
		
	} while (1);

	while(1)
	{
		MyAddress address;
		
		try
		{
			inputFile >> address;
		}
		catch (AddressLoadFailException e)
		{
			failedCount++;
			continue;
		}

		if(inputFile.eof()) break;
		if (!CheckValidAddress(address))
		{
			++failedCount;
			continue;
		}
		m_myAddresses.push_back(address);
		UpdateAddress(m_myAddresses.size() - 1);
	}

	std::sort(m_myAddresses.begin(), m_myAddresses.end());

	// return the number of addresses failed to load
	return failedCount;

FAIL_LOAD_ADDRESS_FILE :
	PhoneFileLoadFailException e;
	throw e;
	return -1;
}

int MyAddressBook::SaveCallsFile(std::string fileName)
{
	std::ofstream outputFile;

	outputFile.open(fileName);
	if (!outputFile.is_open()) return -1;

	for (auto it = m_myCalls.begin(); it != m_myCalls.end(); ++it)
	{
		outputFile << *it << std::endl;
	}

	outputFile.close();
	return 0;
}

int MyAddressBook::LoadCallsFile(std::string fileName)
{
	std::ifstream inputFile;


	inputFile.open(fileName);
	if (!inputFile.is_open()) return -1;

	while (1)
	{
		Call call;
		inputFile >> call;
		if (inputFile.eof()) break;
		m_myCalls.push_back(call);
	}

	std::sort(m_myCalls.begin(), m_myCalls.end(), [](Call& call1, Call& call2) -> bool {
		return (call1 > call2);
	});
	return 0;
}

int MyAddressBook::SaveMessageFile(std::string fileName)
{
	std::ofstream outputFile;

	outputFile.open(fileName);
	if (!outputFile.is_open()) return -1;

	for (auto it = m_myMessages.begin(); it != m_myMessages.end(); ++it)
	{
		outputFile << *it << std::endl;
	}

	outputFile.close();
	return 0;
}

int MyAddressBook::LoadMessageFile(std::string fileName)
{
	std::ifstream inputFile;

	inputFile.open(fileName);
	if (!inputFile.is_open()) return -1;

	while (1)
	{
		SMSMessage message;
		inputFile >> message;
		if (inputFile.eof()) break;
		m_myMessages.push_back(message);
		
	}

	std::sort(m_myMessages.begin(), m_myMessages.end());
	return 0;
}