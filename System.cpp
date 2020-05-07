#include <iostream>
#include <fstream>
#include <string>
#include "System.h"
#include "Date.h"
using namespace std;

const string database = "User.bin";
const string dlist = "Destinations.bin";

System::System()
{
}

System& System::i()
{
	static System sys;
	return sys;
}

User System::signUp(int& count, ofstream& out)
{
	string name, password, email;
	cout << "Signing Up" << endl;
	bool IsOk = true;
	do {

		IsOk = true;
		cout << "Enter nickname: ";
		cin >> name;
		if (!NameValidation(name))
			IsOk = false;
		else
		{
			for (int i = 0; i < count; i++)
			{
				if (name.compare(this->users[i].getNickname()) == 0)
				{
					cout << "There is a user with that name already!" << endl;
					IsOk = false;
				}
			}
		}

	} while (!IsOk);
	cout << "Enter password: ";
	cin >> password;

	do {

		IsOk = true;
		cout << "Enter email: ";
		cin >> email;
		for (int i = 0; i < count; i++)
		{
			if (email.compare(this->users[i].getEmail()) == 0)
			{
				cout << "There is a user with that email already!" << endl;
				IsOk = false;
			}
		}

	} while (!IsOk);

	if (count > 0)
	{
		User* temp = new User[count];
		for (int i = 0; i < count; i++)
			temp[i] = users[i];
	
		users = new User[count + 1];
		for (int i = 0; i < count; i++)
			users[i] = temp[i];
		users[count] = User(name, password, email);

		delete[] temp;
	}
	else
	{
		users = new User[1];
		users[0] = User(name, password, email);
	}
	count++;

	out.write((const char*)&count, sizeof(int));
	for (int i = 0; i < count; i++)
		users[i].Save_newUsers(out);
	out.close();

	return users[count - 1];
}

int System::signIn(const int count)
{
	cout << "Signing in" << endl;
	string name, password;
	cout << "Enter nickname: ";
	cin >> name;
	cout << "Enter password: ";
	cin >> password;

	for (int i = 0; i < count; i++)
	{
		if (name.compare(users[i].getNickname()) == 0 && password.compare(users[i].getPassword()) == 0)
		{
			return i;
		}
	}

	cout << "User hasn't been found" << endl;
	return -1;
}

bool System::NameValidation(const string name)
{
	int index = 0;
	while (name[index] != '\0')
	{
		if (name[index] < 'A' || name[index] > 'Z')
		{
			if (name[index] < 'a' || name[index] > 'z')
			{
				if (name[index] < '0' || name[index] > '9')
				{
					cout << "Invalid nickname! It can contain only letters a-Z or numbers 0-9." << endl;
					return false;
				}
			}
		}
		index++;
	}

	return true;
}

bool System::PhotoValidation(const string photo)
{
	int index = 0;
	if (photo[index] == '.')
	{
		cout << "The photos must be in format name.jpeg or name.png!" << endl;
		return false;
	}
		

	while (photo[index]!='\0')
	{
		if (photo[index] == '.')
		{
			if (photo[index + 1] == 'j' && photo[index + 2] == 'p' && photo[index + 3] == 'e' && photo[index + 4] == 'g' && photo[index + 5] == '\0')
				return true;
			if (photo[index + 1] == 'p' && photo[index + 2] == 'n' && photo[index + 3] == 'g' && photo[index + 4] == '\0')
				return true;
			cout << "The extension must be .jpeg or .png" << endl;
			return false;
		}
		if (photo[index] != '_' && (photo[index] < 'a' || photo[index]>'z') && (photo[index] < 'A' || photo[index]>'Z'))
		{
			cout << "Invalid photo's name! Only letters and '_' are allowed!" << endl;
			return false;
		}
		index++;

	}
	
	cout << "The photo must be in format name.jpeg or name.png" << endl;
	return false;
}

bool System::addFriend(User& cur_user, const int count)
{
	string nickname;
	cout << "Enter user's nickname to add him in your friends' list" << endl;
	cout << "Nickname: ";
	cin >> nickname;
	if (nickname.compare(cur_user.getNickname()) == 0)
	{
		cout << "You cannot add yourself as a friend!" << endl;
		return false;
	}

	for (int i = 0; i < count; i++)
	{
		if (nickname.compare(users[i].getNickname()) == 0)
		{
			if (cur_user.CheckifAdded(nickname))
				return false;

			cur_user.addNewFriends(users[i].getNickname());
			return true;
		}
	}

	cout << "No user with that nickname has been found in the system!" << endl;
	return false;
	
}

void System::Addtour(User& cur_user, int& destNumber)
{
	string destination, comment;
	string photo;
	int grade, photosNumber;
	Date aDate, dDate;
	
	cout << "\nDestination: " << endl;
	cin.ignore();
	getline(cin, destination);

	cout << "\nEnter arrival date" << endl;
	aDate.EnterDate();

	cout << "\nEnter departure date" << endl;
	bool isOk = true;
	do
	{
		isOk = true;
		dDate.EnterDate();
		if (!dDate.DataComparison(aDate))
			isOk = false;
	} while (!isOk);
	
	do
	{
		isOk = true;
		cout << "\nGrade: ";
		cin >> grade;
		if (grade < 1 || grade>5)
		{
			cout << "Invalid grade! Enter a number between 1-5" << endl;
			isOk = false;
		}

	} while (!isOk);

	cout << "\nYour comment for the destination (up to 100 symbols): " << endl;
	cin.ignore();
	getline(cin, comment);
	
	cout << "\nHow many pictures you want to add: ";
	cin >> photosNumber;
	if (photosNumber < 0)
	{
		cout << "You won't add any photos" << endl;
		photosNumber = 0;
	}
	cur_user.addnewtour(destination, aDate, dDate, grade, comment, photosNumber);

	for (int i = 0; i < photosNumber; i++)
	{
		do {
			isOk = true;
			cout << "\nUpload photo " << i + 1 << endl;
			cin >> photo;
			if (!PhotoValidation(photo))
				isOk = false;

		} while (!isOk);
		cur_user.addPhotos(i, photo);
	}

	
	if (destNumber == 0)
	{
		destNumber++;
		destlist = new DestinationsList[1];
		destlist[0] = DestinationsList(destination, cur_user.getNickname(), comment, grade);
	}
	else
	{
		bool newDest = true;
		for (int i = 0; i < destNumber; i++)
		{
			if (destination.compare(destlist[i].getDestination()) == 0)
			{
				destlist[i].addReview(cur_user.getNickname(), comment, grade);
				newDest = false;
				break;
			}
		}
		if (newDest)
		{
			DestinationsList* temp = new DestinationsList[destNumber];
			for (int i = 0; i < destNumber; i++)
			{
				temp[i] = destlist[i];
			}

			destlist = new DestinationsList[destNumber + 1];
			for (int i = 0; i < destNumber; i++)
			{
				destlist[i] = temp[i];
			}
			destlist[destNumber] = DestinationsList(destination, cur_user.getNickname(), comment, grade);

			destNumber++;
			delete[] temp;
		}
	}

}

void System::FriendsAndDestinations(const User& cur_user, const int destNumber)
{
	cout << "Friends' list and their tours" << endl;
	string friends_name;
	int friendsCount = cur_user.getFriendsCount();
	if (friendsCount == 0)
		cout << "You don't have friends" << endl;	
	else
	{
		for (int i = 0; i < friendsCount; i++)
		{
			friends_name = cur_user.ShowFriendsList(i);
			cout << i + 1 << ". " << friends_name << endl;
			cout << "Visited destinations by the user: " << endl;
			for (int j = 0; j < destNumber; j++)
			{
				destlist[j].User_Tour(friends_name);
			}
		}
	}
}

int System::run()
{
	User cur_user;
	string name, password, email, destination, comment, photo, personal_acc;
	Date Adate, Ddate;
	int photonum, option, destNumber, count = 0;
	short grade;

	ofstream UsersData(database, ios::binary | ios::app);
	if (!UsersData)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return -1;
	}
	UsersData.close();
	ofstream Dest(dlist, ios::binary | ios::app);
	if (!Dest)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return -1;
	}
	Dest.close();
	ifstream DestRead(dlist, ios::binary);
	if (!DestRead)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return -1;
	}
	DestRead.seekg(0, ios::end);
	if (DestRead.tellg() == 0)
		destNumber = 0;
	else
	{
		DestRead.seekg(0, ios::beg);
		DestRead.read((char*)&destNumber, sizeof(int));
		destlist = new DestinationsList[destNumber];
		for (int i = 0; i < destNumber; i++)
			destlist[i].LoadData(DestRead);
	}
	DestRead.close();

	ifstream UsersDataR(database, ios::binary);
	if (!UsersData)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return -1;
	}
	UsersDataR.seekg(0, ios::end);
	if (UsersDataR.tellg() == 0)
	{
		UsersDataR.close();
		ofstream UsersData(database, ios::binary);
		if (!UsersData)
		{
			cout << "Error! Couldn't open the file!" << endl;
			return -1;
		}
		cur_user = signUp(count, UsersData);
		UsersData.close();

		personal_acc = cur_user.getNickname() + ".bin";
		ofstream pAcc(personal_acc, ios::binary);
		if (!pAcc)
		{
			cout << "Error! Couldn't open the file!" << endl;
			return -1;
		}

		pAcc.close();
	}
	else
	{
		UsersDataR.seekg(0, ios::beg);
		UsersDataR.read((char*)&count, sizeof(int));
		users = new User[count];
		for (int i = 0; i < count; i++)
		{
			users[i].Users_Data(UsersDataR);
		}
		UsersDataR.close();

		bool Done = true;
		do
		{
			Done = true;
			cout << "1. Sign in" << endl;
			cout << "2. Sign up" << endl;
			cout << "0. Exit" << endl;
			cout << ">> ";
			cin >> option;
			cout << endl;
			switch (option)
			{
			case 1:
			{
				int index = signIn(count);
				if (index != -1)
				{
					cur_user = users[index];
					personal_acc = cur_user.getNickname() + ".bin";
					ifstream pAccRead(personal_acc, ios::binary);
					if (!pAccRead)
					{
						cout << "Error! Couldn't open the file!" << endl;
						return -1;
					}
					cur_user.LoadAccInfo(pAccRead);
					pAccRead.close();

					cout << "Successfully loaded account information!" << endl;
				}
				else
					Done = false;

				break;
			}
			case 2:
			{
				ofstream UsersData(database, ios::binary);
				if (!UsersData)
				{
					cout << "Error! Couldn't open the file!" << endl;
					return 0;
				}
				cur_user = signUp(count, UsersData);
				personal_acc = cur_user.getNickname() + ".bin";
				ofstream pAcc(personal_acc, ios::binary);
				if (!pAcc)
				{
					cout << "Error! Couldn't open the file!" << endl;
					return 0;
				}
				pAcc.close();

				cout << "Successfully created an account!" << endl;
				break;
			}
			case 0:
			{
				cout << "Exiting the program..." << endl;
				return 0;
			}
			default:
			{
				cout << "Invalid command!" << endl;
				Done = false;
				break;
			}
			}
		} while (!Done);

	}

	do
	{
		cout << "\nMain menu" << endl;
		cout << "1. Add new tour" << endl;
		cout << "2. Check your tours" << endl;
		cout << "3. All destinations" << endl;
		cout << "4. Add a new friend" << endl;
		cout << "5. Check your friends' list" << endl;
		cout << "0. Exit" << endl;
		cout << ">> ";
		cin >> option;
		cout << endl;
		switch (option)
		{
		case 1:
		{
			Addtour(cur_user, destNumber);

			ofstream pAcc(personal_acc, ios::binary);
			if (!pAcc)
			{
				cout << "Error! Cannot save the new destination!" << endl;
				return -1;
			}
			cur_user.SaveAccInfo(pAcc);
			pAcc.close();

			ofstream savedest(dlist, ios::binary);
			if (!savedest)
			{
				cout << "Error! Cannot save the new destination!" << endl;
				return -1;
			}
			savedest.write((const char*)&destNumber, sizeof(int));
			for (int i = 0; i < destNumber; i++)
			{
				destlist[i].SaveData(savedest);
			}
			savedest.close();

			cout << "You have successfully added a new tour in your account" << endl;
			break;
		}
		case 2:
		{
			cur_user.ShowPersonalData();
			break;
		}
		case 3:
		{
			cout << "\nAll destinations:" << endl;
			for (int i = 0; i < destNumber; i++)
			{
				cout << i + 1 << ". " << destlist[i];
				destlist[i].ShowReviews();
				cout << endl;
			}
			break;
		}
		case 4:
		{
			if (addFriend(cur_user, count))
			{
				ofstream pAcc(personal_acc, ios::binary);
				if (!pAcc)
				{
					cout << "Error! Couldn't open the file!" << endl;
					return -1;
				}
				cur_user.SaveAccInfo(pAcc);
				cout << "You have successfully added a user to your friend's list!" << endl;
				pAcc.close();
			}
			break;
		}
		case 5:
		{
			FriendsAndDestinations(cur_user, destNumber);
			break;
		}
		case 0:
		{
			cout << "Exiting the program..." << endl;
			break;			
		}
		default:
		{
			cout << "Invalid command!" << endl;
			break;
		}
		}

	} while (option != 0);

	return 0;
}
