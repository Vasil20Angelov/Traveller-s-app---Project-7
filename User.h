#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"
#include "Tour.h"
#include "FriendsList.h"
using namespace std;

class User
{
public:
	static int ToursCount;
	static int FriendsCount;

	User(const string& nickname = "", const  string& password = "", const string& email = "");
	User(const User& other);
	User& operator=(const User& other);
	~User();

	void Users_Data(ifstream& in); //������� �� ���� �����,�������� � ������
	void Save_newUsers(ofstream& out) const; // ������� ��� ���� ������ �����������
	void LoadAccInfo(ifstream& in); // ������� ������ ��������� �� ����� ���������
	void SaveAccInfo(ofstream& out); // ������� ����������� � ������� �� ����� ����������

	void addnewtour(const string destination, Date aDate, Date dDate, short grade, const string comment, int photos_num); // ������ ���� ��������� ��� �������
	void addPhotos(int index, const string photo); // ������ ������ �� ������ ���������
	void addNewFriends(const string friends_name); // ������ ���� ��������
	void ShowPersonalData() const;
	bool CheckifAdded(const string friends_name);

	const string getNickname() const;
	const string getPassword() const;
	const string getEmail() const;
	const int getFriendsCount() const;
	const string ShowFriendsList(int index) const;

private:
	void copy(const User& other);
	void clear();

	string nickname;
	string password;
	string email;
	FriendsList friends;
	Tour* tours;

};


