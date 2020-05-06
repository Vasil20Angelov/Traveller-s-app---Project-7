#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class FriendsList
{
public:
	FriendsList();
	FriendsList(int friendsNum);
	~FriendsList();

	void addFriend(const string new_friend);
	void ReadData(ifstream& in);
	void SaveData(ofstream& out) const;

private:

	string* friends;
	int friendsNum;
};

