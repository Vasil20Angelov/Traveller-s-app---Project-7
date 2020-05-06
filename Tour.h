#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
using namespace std;
class Tour
{
public:
	//static bool photoMem;
	Tour();
	Tour(const string& destination, Date aDate, Date dDate, short grade, const string& comment, int photos_num);
	Tour(const Tour& other);
	Tour& operator=(const Tour& other);
	~Tour();

	void LoadData(ifstream& in);
	void SavaData(ofstream& out) const;
	//void PhotosMemory(int photosNum);
	void AddPhotos(int index, const string photos);
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