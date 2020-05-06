#pragma once
struct Date
{
public:

	short day;
	short month;
	short year;
	
	bool DateValidation();
	void ShowDate() const;
};
