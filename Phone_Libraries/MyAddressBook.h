
#pragma once

#include <string>
#include <vector>
#include "MyAddress.h"

class MyAddressBook
{
/* Member Variables */
protected :
	std::vector<MyAddress>		m_addresses;
	std::vector<std::string>	m_groups;

/* Constructor & Destructor */
public :
	MyAddressBook();
	~MyAddressBook();

/* Metods */
public :
	int			AddAddress(MyAddress address);
	int			ExchangeAddress(size_t index1, size_t index2);
	int			DeleteAddress(size_t index);

	MyAddress&	GetAddress(size_t index);

	int			SortAddressesByName();
	int			SortAddressesByGroup();

};