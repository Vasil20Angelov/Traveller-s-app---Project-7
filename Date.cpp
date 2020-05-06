#include <iostream>
#include "Date.h"
using namespace std;

bool Date::DateValidation()
{
	if (day < 1)
	{
		cout << "Invalid date! The day cannot be a number lower than 1!" << endl;
		return false;
	}
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	{
		if (day > 31)
		{
			cout << "Invalid date! The selected month has 31 days!" << endl;
			return false;
		}
		return true;
	}
	case 2:
	{
		bool leapY = false;
		if (year % 4 == 0)
			leapY = true;
		if ((day > 28 && !leapY) || (day > 29 && leapY))
		{
			cout << "Invalid date! February has 28 days (29 if it is a leap year)!" << endl;
			return false;
		}
		return true;
	}
	default:
	{
		if (day > 30)
		{
			cout << "Invalid date! The selected month has 30 days!" << endl;
			return false;
		}
		return true;
	}
	}
}

bool Date::DataComparison(const Date& other) // /other/ is arrival date, while /this/ is departure date
{
	if (other.year < year)
		return true;
	if (other.year > year)
	{
		cout << "Invalid period. The date of departure cannot be before the date of arrival!" << endl;
		return false;
	}
	if (other.month < month)
		return true;
	if (other.month > month)
	{
		cout << "Invalid period. The date of departure cannot be before the date of arrival!" << endl;
		return false;
	}
	if (other.day > day)
	{
		cout << "Invalid period. The date of departure cannot be before the date of arrival!" << endl;
		return false;
	}

	return true;
}

void Date::EnterDate()
{
	bool isOk = true;
	do
	{
		isOk = true;
		cout << "Year: ";
		cin >> year;
		if (year < 1980 || year > 2020)
		{
			cout << "Invalid date! Enter an year between 1980 - 2020!" << endl;
			isOk = false;
		}

	} while (!isOk);

	do
	{
		isOk = true;
		cout << "Month: ";
		cin >> month;
		if (month < 1 || month > 12)
		{
			cout << "Invalid date! The month must be a number between 1 - 12!" << endl;
			isOk = false;
		}

	} while (!isOk);

	do
	{
		isOk = true;
		cout << "Day: ";
		cin >> day;
		if (!DateValidation())
		{
			isOk = false;
		}

	} while (!isOk);
}

void Date::ShowDate() const
{
	cout << year << "." << month << "." << day << endl;
}
