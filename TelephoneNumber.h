
#pragma once

#include <string>

class TelephoneNumber
{
/* Member Variables */
protected :
	std::string		number;
	
/* Constructor & Destructor */
public :
	TelephoneNumber();
	~TelephoneNumber();

/* Methods */
public :
	int SetNumber(std::string number);
	int NormalizeNumber();

/* Getter */
	std::string GetTelephoneNumber(bool normalized = true) const;
};