#include <iostream>
#include <string>
#include "TelephoneNumber.h"

using namespace std;

TelephoneNumber::TelephoneNumber()
{
	this->number = "Input the phone number";
}

TelephoneNumber::~TelephoneNumber()
{
	cout << "Phone number is deleted" << endl;
}

int TelephoneNumber::SetNumber(std::string number)
{
	this->number = number;
	return 0;
}

int TelephoneNumber::NormalizeNumber()
{
	if (number.size() > 5)
		number.insert(number.size() - 5, "-");	/*000000-0000*/
	else
		return 1;								/*return without any change*/
	/*classify the reign numbers*/
	if (number[0] == '0' && number[1] == '2')	/*Seoul => 02-0000-0000*/
		number.insert(2, "-");
	else
		number.insert(3, "-");					/*Gyounggi or internet => 031-500-0000	or	070-0000-0000*/
													
	return 0;
}

std::string TelephoneNumber::GetTelephoneNumber(bool normalized = true) const
{	
	return this->number;
}
