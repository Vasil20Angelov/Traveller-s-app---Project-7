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
	int signIn(int count); // Връща индекса на акаунта в който искам да вляза
	bool NameValidation(const string name);
	bool PhotoValidation(string photo); // Проверява дали е вярно въведено разширението на снимката
	bool addFriend(User& cur_user, const int count);
	void Addtour(User& cur_user, int& destNumber);
	int run();

private:
	System();
	User* users;
	DestinationsList* destlist;
};

