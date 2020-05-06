#include <iostream>
#include <fstream>
#include <string>
#include "FriendsList.h"

FriendsList::FriendsList()
{
	friendsNum = 0;
	friends = nullptr;
}

FriendsList::FriendsList(int friendsNum)
{
	this->friendsNum = friendsNum;
	if (friendsNum > 0)
		friends = new string[friendsNum];
	friends = nullptr;
}

FriendsList::~FriendsList()
{
	if (friendsNum > 0)
		delete[] friends;
	friends = nullptr;
}

bool FriendsList::AlreadyAdded(const string new_friend)
{
	for (int i = 0; i < friendsNum; i++)
	{
		if (new_friend.compare(friends[i]) == 0)
			return true;
	}

	return false;
}

void FriendsList::addFriend(const string new_friend)
{
	if (friendsNum > 0)
	{
		string* temp = new string[friendsNum];
		for (int i = 0; i < friendsNum; i++)
			temp[i] = friends[i];
		
		friends = new string[friendsNum + 1];
		for (int i = 0; i < friendsNum; i++)
			friends[i] = temp[i];

		friends[friendsNum] = new_friend;

		delete[] temp;
	}
	else
	{
		friends = new string[1];
		friends[0] = new_friend;
	}

	friendsNum++;
}

void FriendsList::ReadData(ifstream& in)
{
	in.read((char*)&friendsNum, sizeof(int));
	friends = new string[friendsNum];
	for (int i = 0; i < friendsNum; i++)
	{
		size_t len;
		in.read((char*)&len, sizeof(size_t));
		friends[i].resize(len);
		in.read((char*)&friends[i][0], len);
	}
}

void FriendsList::SaveData(ofstream& out) const
{
	out.write((const char*)&friendsNum, sizeof(int));
	for (int i = 0; i < friendsNum; i++)
	{
		size_t size = friends[i].size();
		out.write((const char*)&size, sizeof(size_t));
		out.write((const char*)&friends[i][0], size);
	}
}

void FriendsList::ShowFriends() const
{
	if (friendsNum == 0)
		cout << "You don't have any friends" << endl;
	else
	{
		for (int i = 0; i < friendsNum; i++)
			cout << friends[i] << endl;
	}
}


