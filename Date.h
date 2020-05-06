#pragma once
struct Date
{
public:

	short day;
	short month;
	short year;
	
	bool DateValidation();
	bool DataComparison(const Date& other);
	void EnterDate();
	void ShowDate() const;
};
