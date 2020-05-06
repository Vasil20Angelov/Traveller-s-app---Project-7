#include <iostream>
#include "Date.h"
using namespace std;

bool Date::DateValidation()
{
	return false;
}

bool Date::DataComparison(const Date& other)
{
	return false;
}

void Date::ShowDate() const
{
	cout << year << "." << month << "." << day << endl;
}
