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
	const string ShowFriends(int index) const;
	const int getFriendsNum() const;

private:

	string* friends;
	int friendsNum;
};

