#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "User.h"
#include "Tour.h"
#include "FriendsList.h"
#include "DestinationList.h"
class System
{
public:
	static System& i();

	User signUp(int& count, ofstream& out);
	int signIn(const int count); // ����� ������� �� ������� � ����� ����� �� �����
	bool NameValidation(const string name);
	bool PhotoValidation(const string photo); // ��������� ���� � ����� �������� ������������ �� ��������
	bool addFriend(User& cur_user, const int count);
	void Addtour(User& cur_user, int& destNumber);
	void FriendsAndDestinations(const User& cur_user, const int destNumber);
	int run();

private:
	System();
	User* users;
	DestinationsList* destlist;
};

