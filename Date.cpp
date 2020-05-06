#include <iostream>
#include "Date.h"
using namespace std;

bool Date::DateValidation()
{
	return false;
}

void Date::ShowDate() const
{
	cout << year << "." << month << "." << day << endl;
}
