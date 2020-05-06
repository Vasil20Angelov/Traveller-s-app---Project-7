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

	bool AlreadyAdded(const string new_friend);
	void addFriend(const string new_friend);
	void ReadData(ifstream& in);
	void SaveData(ofstream& out) const;
	void ShowFriends() const;

private:

	string* friends;
	int friendsNum;
};

