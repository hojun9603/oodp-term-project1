#include <iostream>
#include <fstream>
#include <vector>
#include "MyAddressBook.h"

MyAddressBook::MyAddressBook()
{
	fstream MyAddressBookSaveFile;

	cout << "Open the address book" << endl;
	m_groups[0] = "Null"; /*default value is 'Null'*/
}

MyAddressBook::~MyAddressBook()
{
	std::cout << "";
}

int MyAddressBook::AddAddress(MyAddress address)
{
	fstream MyAddressBookSaveFile;

	m_addresses.push_back(address);										/*	unnecesary?????	*/

	if (MyAddressBookSaveFile.is_open() == false)
		cout << "error : there is no file to open" << endl;

	else
	{
		MyAddressBookSaveFile.open("MyAddressBookSaveFile.txt", ios::out);
		MyAddressBookSaveFile << "[ADDRESS START]" << endl;
		MyAddressBookSaveFile << "NAME = " << address.GetName << endl <<
			"TELEPHONENUMBERS = " << address.GetTelephoneNumber << endl <<
			"EMAIL = " << address.GetEmail << endl <<
			"BIRTHDAY = " << address.GetBirthDayYear() << " / " << address.GetBirthDayMonth << " / " << address.GetBirthDayDay << endl <<
			" GROUP = " << address.GetGroup << endl;
		MyAddressBookSaveFile << "ADDRESS END" << endl;

		MyAddressBookSaveFile.close();

	}
	return 0;
}

int MyAddressBook::ExchangeAddress(size_t index1, size_t index2)
{
	MyAddress temp;
	temp = m_addresses[index1];
	m_addresses[index1] = m_addresses[index2];
	m_addresses[index2] = temp;

	return 0;
}

int MyAddressBook::DeleteAddress(size_t index)
{
	/*----------------------------------------------------*/
	fstream MyAddressBookSaveFile;
	std::vector<MyAddress>::iterator it = m_addresses.begin();
	
	if (MyAddressBookSaveFile.is_open() == false)
		cout << "error : there is no file to open" << endl;
	
	else
	{
		MyAddressBookSaveFile.open("MyAddressBookSaveFile.txt", ios::out);
		/*use iterator */
		
		MyAddressBookSaveFile.close();
	}






	
	
	
	/*----------------------------------------------------*/
	int i;
	MyAddress temp;

	for (i = index; i < m_addresses.size()-1; i++)	/*push back the index number to the end*/
	{
		temp = m_addresses[i];
		m_addresses[i] = m_addresses[i + 1];
		m_addresses[i + 1] = temp;
	}
	m_addresses.resize[m_addresses.size() - 1];			/*delete the last index number*/

	return 0;
}

MyAddress & MyAddressBook::GetAddress(size_t index)
{
	return m_addresses[index];
	// TODO: 여기에 반환 구문을 삽입합니다.
}

int MyAddressBook::SortAddressesByName()	/*bubble sort*/
{
	MyAddress temp, name1, name2;
	int i, j;

	for (i = 0; i < m_addresses.size() - 1; i++)
	{
		for(j=0; j< m_addresses.size() - 1 - i ; j++)
		{
			if (strcmp(m_addresses[j].GetName, m_addresses[j + 1].GetName) == 1)
			{
				temp = m_addresses[j];
				m_addresses[j] = m_addresses[j + 1];
				m_addresses[j + 1] = temp;
			}
		}
	}
	return 0;
}

int MyAddressBook::SortAddressesByGroup()
{
	int i,j;
	std::vector<MyAddress>	NewSortedAddresses;
	MyAddress temp;

	for (i = 0; i < m_groups.size() - 1; i++)				/*make new sorted addresses book*/
	{
		for (j = 0; j < m_addresses.size() - 1; j++)
		{
			if (m_groups[i] == m_addresses[j].GetGroup)
				NewSortedAddresses.push_back(m_addresses[j]);
		}
	}
	for (i = 0; i < m_addresses.size() - 1; i++)				/*copy new sorted addresses and paste them to m_addresses*/
	{
		m_addresses[i] = NewSortedAddresses[i];
	}
	return 0;
}
