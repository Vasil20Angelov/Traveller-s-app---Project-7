#include <iostream>
#include "Date.h"
using namespace std;

void Date::ShowDate() const
{
	cout << year << "." << month << "." << day << endl;
}
