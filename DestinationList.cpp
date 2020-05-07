#include <iostream>
#include <fstream>
#include <string>
#include "DestinationList.h"
using namespace std;

DestinationsList::DestinationsList()
{
	destination = "";

	//grade = nullptr;

	//comment = nullptr;

	//user = nullptr;

	//avr_grade = 0.0;
	reviews = 0;

}

DestinationsList::DestinationsList(const string& destination, const string& user, const string& comment, short grade)
{
	this->destination = destination;

	this->user = new string[1]; // размера е 1, т.к. тук само създавам дестинацията
	this->user[0] = user;

	this->comment = new string [1];
	this->comment[0] = comment;

	this->grade = new short[1];
	this->grade[0] = grade;

	reviews = 1;
	avr_grade = (double)grade;
}

DestinationsList::DestinationsList(const DestinationsList& other)
{
	copy(other);
}

DestinationsList& DestinationsList::operator=(const DestinationsList& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

DestinationsList::~DestinationsList()
{
	clear();
}

void DestinationsList::LoadData(ifstream& in)
{
	size_t len;
	in.read((char*)&len, sizeof(size_t));
	destination.resize(len);
	in.read((char*)&destination[0], len);
	
	in.read((char*)&avr_grade, sizeof(double));
	in.read((char*)&reviews, sizeof(int));

	user = new string[reviews];
	comment = new string[reviews];
	grade = new short(reviews);

	for (int i = 0; i < reviews; i++)
	{
		size_t len;
		in.read((char*)&len, sizeof(size_t));
		user[i].resize(len);
		in.read((char*)&user[i][0], len);

		in.read((char*)&len, sizeof(size_t));
		comment[i].resize(len);
		in.read((char*)&comment[i][0], len);

		in.read((char*)&grade[i], sizeof(short));
	}
}

void DestinationsList::SaveData(ofstream& out) const
{
	size_t len = destination.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&destination[0], len);

	out.write((const char*)&avr_grade, sizeof(double));
	out.write((const char*)&reviews, sizeof(int));

	for (int i = 0; i < reviews; i++)
	{
		size_t len2 = user[i].size();
		out.write((const char*)&len2, sizeof(size_t));
		out.write((const char*)&user[i][0], len2);

		size_t len3 = comment[i].size();
		out.write((const char*)&len3, sizeof(size_t));
		out.write((const char*)&comment[i][0], len3);

		out.write((const char*)&grade[i], sizeof(short));
	}

}

void DestinationsList::addReview(const string user, const string comment, short grade)
{
	double sum = 0;

	if (reviews > 0)
	{
		string* temp = new string[reviews];
		for (int i = 0; i < reviews; i++)
		{
			temp[i] = this->user[i];
		}

		this->user = new string[reviews + 1];
		for (int i = 0; i < reviews; i++)
		{
			this->user[i] = temp[i];
		}
		this->user[reviews] = user;

		for (int i = 0; i < reviews; i++)
		{
			temp[i] = comment[i];
		}

		this->comment = new string[reviews + 1];
		for (int i = 0; i < reviews; i++)
		{
			this->comment[i] = temp[i];
		}
		this->comment[reviews] = comment;

		delete[] temp;

		short* tempG = new short[reviews];
		for (int i = 0; i < reviews; i++)
			tempG[i] = this->grade[i];

		this->grade = new short[reviews + 1];

		for (int i = 0; i < reviews; i++)
		{
			this->grade[i] = tempG[i];
			sum += this->grade[i];
		}
		this->grade[reviews] = grade;
		sum += this->grade[reviews];

		delete[] tempG;
	}
	else
	{
		this->user = new string[1];
		this->user[0] = user;

		this->comment = new string[1];
		this->comment[0] = comment;

		this->grade = new short[1];
		this->grade[0] = grade;

		sum = grade;
	}

	reviews++;
	avr_grade = sum / (double)reviews;

}

void DestinationsList::ShowReviews() const
{

	for (int i = 0; i < reviews; i++)
	{
		cout << "User: " << user[i] << ",  Grade: " << grade[i] << endl << comment[i] << endl;
	}
}

void DestinationsList::User_Tour(const string user) const
{
	for (int i = 0; i < reviews; i++)
	{
		if (user.compare(this->user[i]) == 0)
		{
			cout << "Destination: " << destination << ", Grade: " << grade[i] << endl;
		}
	}

}

const string DestinationsList::getDestination() const
{
	return destination;
}

void DestinationsList::copy(const DestinationsList& other)
{
	reviews = other.reviews;
	avr_grade = other.avr_grade;

	destination = other.destination;

	if (reviews > 0)
	{
		user = new string [reviews];
		for (int i = 0; i < reviews; i++)
		{
			user[i] = other.user[i];
		}

		comment = new string [reviews];
		for (int i = 0; i < reviews; i++)
		{
			comment[i] = other.comment[i];
		}

		grade = new short[reviews];
		for (int i = 0; i < reviews; i++)
		{
			grade[i] = other.grade[i];
		}
	}

}

void DestinationsList::clear()
{
	if (reviews > 0)
	{
		delete[] comment;
		delete[] user;
		delete[] grade;
	}
	comment = nullptr;
	user = nullptr;
	grade = nullptr;
}

ostream& operator<<(ostream& out, const DestinationsList& obj)
{
	return out << "Destination: " << obj.destination << ", Grade: " << obj.avr_grade << endl;
}
