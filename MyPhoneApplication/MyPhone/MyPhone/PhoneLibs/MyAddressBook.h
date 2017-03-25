
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _MY_ADDRESS_BOOK_H_
#define _MY_ADDRESS_BOOK_H_

///////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <exception>
#include <vector>
#include "MyAddress.h"
#include "Call.h"
#include "SMSMessage.h"

///////////////////////////////////////////////////////////////////////////////////////

class MyAddressBook
{
/* Member Variables */
protected :
	std::vector<MyAddress>					m_myAddresses;
	std::vector<std::string>				m_myGroups;
	std::vector<SMSMessage>					m_myMessages;
	std::vector<Call>						m_myCalls;
	std::map<PhoneNumber, std::string>		m_namesByNumbers;

/* Constructor & Destructor */
public :
	MyAddressBook();
	~MyAddressBook();

/* Methods */
	int				AddAddress(const MyAddress& address);
	int				DeleteAddress(size_t index);
	MyAddress*		GetAddress(size_t index);
	int				UpdateAddress(size_t index);
	int				UpdateAddress(size_t index, MyAddress& address);
	int				SearchAddress(std::string name);
	int				SearchAddress(const PhoneNumber& phoneNumber);
	size_t			GetAddressCount(void) const;

	bool			CheckValidAddress(MyAddress address);

	int				UpdateNumber(const PhoneNumber& number, std::string name);
	int				RemoveNumber(const PhoneNumber& number);

	int				AddGroup(std::string groupName);
	int				DeleteGroup(std::string groupName);
	std::string*	GetGroup(size_t index);

	int				AddCall(Call& call);
	int				DeleteCall(size_t index);
	Call*			GetCall(size_t index);
	size_t			GetCallCount(void) const;

	int				AddMessage(SMSMessage& message);
	int				DeleteMessage(size_t index);
	SMSMessage*		GetMessage(size_t index);
	int				SearchFirstMessage(const PhoneNumber& number);
	size_t			GetMessageCount(void) const;

	int				SortAddressByName();
	int				SortAddressByGroup();

	int				SetStringData(std::string title, std::string value);
	std::string		GetStringData(std::string title);

	int				SaveAddressFile(std::string fileName);
	int				LoadAddressFile(std::string fileName);

#define	MY_ADDRBOOK_DATA_GROUP		"GROUPS"

	int				SaveCallsFile(std::string fileName);
	int				LoadCallsFile(std::string fileName);

	int				SaveMessageFile(std::string fileName);
	int				LoadMessageFile(std::string fileName);
};

///////////////////////////////////////////////////////////////////////////////////////

class PhoneFileLoadFailException : public std::exception
{
public :
	virtual const char* what() const noexcept
	{
		return "Wrong syntax for loading.";
	}
};


#endif

///////////////////////////////////////////////////////////////////////////////////////