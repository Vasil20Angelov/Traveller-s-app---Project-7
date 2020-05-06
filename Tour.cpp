#include <iostream>
#include <string>
#include <fstream>
#include "Tour.h"

//bool Tour::photoMem = false;
Tour::Tour()
{
	destination = "";
	comment = "";
	photos = nullptr;

	aDate.day = 0;
	aDate.month = 0;
	aDate.year = 0;

	dDate.day = 0;
	dDate.month = 0;
	dDate.year = 0;

	grade = 0;
	photos_num = 0;

}

Tour::Tour(const string& destination, Date aDate, Date dDate, short grade, const string& comment, int photos_num)
{
	this->destination = destination;

	this->aDate = aDate;
	this->dDate = dDate;
	this->grade = grade;

	this->comment = comment;

	this->photos_num = photos_num;
	this->photos = new string [photos_num];
	for (int i = 0; i < photos_num; i++)
		this->photos[i] = "";
}

Tour::Tour(const Tour& other)
{
	copy(other);
}

Tour& Tour::operator=(const Tour& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Tour::~Tour()
{
	clear();
}

void Tour::LoadData(ifstream& in)
{
	size_t len;
	in.read((char*)&len, sizeof(size_t));
	destination.resize(len);
	in.read((char*)&destination[0], len);

	in.read((char*)&aDate, sizeof(Date));
	in.read((char*)&dDate, sizeof(Date));
	in.read((char*)&grade, sizeof(short));

	in.read((char*)&len, sizeof(size_t));
	comment.resize(len);
	in.read((char*)&comment[0], len);

	in.read((char*)&photos_num, sizeof(int));
	photos = new string[photos_num];
	for (int i = 0; i < photos_num; i++)
	{
		in.read((char*)&len, sizeof(size_t));
		photos[i].resize(len);
		in.read((char*)&photos[i][0], len);
	}
}

void Tour::SavaData(ofstream& out) const
{
	size_t len = destination.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&destination[0], len);

	out.write((const char*)&aDate, sizeof(Date));
	out.write((const char*)&dDate, sizeof(Date));
	out.write((const char*)&grade, sizeof(short));

	len = comment.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&comment[0], len);

	out.write((const char*)&photos_num, sizeof(int));
	for (int i = 0; i < photos_num; i++)
	{
		size_t len = photos[i].size();
		out.write((const char*)&len, sizeof(size_t));
		out.write((const char*)&photos[i][0], len);
	}

}

void Tour::AddPhotos(int index, const string photo)
{
	photos[index] = photo;
	
}

const string Tour::getdest() const
{
	return destination;
}

void Tour::copy(const Tour& other)
{
	destination = other.destination;
	comment = other.comment;

	aDate = other.aDate;
	dDate = other.dDate;
	grade = other.grade;

	photos_num = other.photos_num;
	if (photos_num > 0)
		photos = new string[photos_num];
	else
		photos = nullptr;

}

void Tour::clear()
{
	delete[] photos;
	photos = nullptr;
}