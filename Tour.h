#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
using namespace std;
class Tour
{
public:

	Tour();
	Tour(const string& destination, Date aDate, Date dDate, short grade, const string& comment, int photos_num);
	Tour(const Tour& other);
	Tour& operator=(const Tour& other);
	~Tour();

	void LoadData(ifstream& in);
	void SavaData(ofstream& out) const;
	void AddPhotos(int index, const string photos);
	void ShowTour() const;
	const string getdest() const;

private:
	void copy(const Tour& other);
	void clear();

	string destination;
	Date aDate;
	Date dDate;
	short grade;
	int photos_num;

	string comment;
	string* photos;

};
