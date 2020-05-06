#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
#include "Tour.h"
using namespace std;

class DestinationsList
{
public:

	DestinationsList();
	DestinationsList(const string& destination, const string& user, const string& comment, short grade);
	DestinationsList(const DestinationsList& other);
	DestinationsList& operator=(const DestinationsList& other);
	~DestinationsList();

	void LoadData(ifstream& in);
	void SaveData(ofstream& out) const;

	void addReview(const string user, const string comment, short grade);
	void ShowReviews() const;
	const string getDestination() const;

	friend ostream& operator<<(ostream& out, const DestinationsList& obj);

private:
	void copy(const DestinationsList& other);
	void clear();

	string destination;
	string* user;
	string* comment;
	short* grade;
	int reviews;
	double avr_grade;

};