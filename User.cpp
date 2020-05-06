#include <iostream>
#include <string>
#include <fstream>
#include "User.h"

int User::ToursCount = 0;
int User::FriendsCount = 0;

User::User(const string& nickname, const string& password, const string& email)
{
	this->nickname = nickname;
	this->password = password;
	this->email = email;
}

User::User(const User& other)
{
	copy(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

User::~User()
{
	clear();
}

void User::Users_Data(ifstream& in)
{
	size_t len;
	in.read((char*)&len, sizeof(size_t));
	nickname.resize(len);
	in.read((char*)&nickname[0], len);
	
	size_t len2;
	in.read((char*)&len2, sizeof(size_t));
	password.resize(len2);
	in.read((char*)&password[0], len2);

	size_t len3;
	in.read((char*)&len3, sizeof(size_t));
	email.resize(len3);
	in.read((char*)&email[0], len3);

}

void User::Save_newUsers(ofstream& out) const
{
	size_t len = nickname.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&nickname[0], len);

	size_t len2 = password.size();
	out.write((const char*)&len2, sizeof(size_t));
	out.write((const char*)&password[0], len2);

	size_t len3 = email.size();
	out.write((const char*)&len3, sizeof(size_t));
	out.write((const char*)&email[0], len3);
}

void User::LoadAccInfo(ifstream& in)	
{
	friends.ReadData(in);

	in.read((char*)&ToursCount, sizeof(int));
	tours = new Tour[ToursCount];
	for (int i = 0; i < ToursCount; i++)
	{
		tours[i].LoadData(in);
	}

}

void User::SaveAccInfo(ofstream& out)
{
	friends.SaveData(out);

	out.write((const char*)&ToursCount, sizeof(int));
	for (int i = 0; i < ToursCount; i++)
	{
		tours[i].SavaData(out);
	}
}

void User::addnewtour(const string destination, Date aDate, Date dDate, short grade, const string comment, int photos_num)
{
	if (ToursCount > 0)
	{
		Tour* temp = new Tour[ToursCount];
		//temp = tours;

		for (int i = 0; i < ToursCount; i++)
			temp[i] = tours[i];
	
		tours = new Tour[ToursCount + 1];
		//tours = temp;

		for (int i = 0; i < ToursCount; i++)
			tours[i] = temp[i];
				
		tours[ToursCount] = Tour(destination, aDate, dDate, grade, comment, photos_num);
		delete[] temp;

	}
	else
	{
		tours = new Tour[ToursCount + 1];
		tours[ToursCount] = Tour(destination, aDate, dDate, grade, comment, photos_num);
	}

	ToursCount++;
}

void User::addPhotos(int index, const string photo)
{
	tours[ToursCount - 1].AddPhotos(index, photo);
}

void User::addNewFriends(const string friends_name)
{
	friends.addFriend(friends_name);
}

void User::ShowPersonalData() const
{
	cout << nickname << "'s Tours" << endl;

	if (ToursCount == 0)
		cout << "There haven't been added any tours in your account yet!" << endl;
	else
	{
		for (int i = 0; i < ToursCount; i++)
		{
			cout << i + 1 << ". ";
			tours[i].ShowTour();
		}
	}
}

void User::ShowFriendsList() const
{
	cout << "\nYour friends: " << endl;
	friends.ShowFriends();
}

bool User::CheckifAdded(const string friends_name)
{
	if (friends.AlreadyAdded(friends_name))
	{
		cout << "You have already added this user to your friends' list. He cannot be added again." << endl;
		return true;
	}
	return false;
}

const string User::getNickname() const
{
	return nickname;
}

const string User::getPassword() const
{
	return password;
}

const string User::getEmail() const
{
	return email;
}

void User::copy(const User& other)
{
	nickname = other.nickname;
	password = other.password;
	email = other.email;

	tours = other.tours;
	friends = other.friends;
}

void User::clear()
{
	if (ToursCount > 0)
		delete[] tours;
}
