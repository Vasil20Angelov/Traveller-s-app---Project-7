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
	cout << "Sign Up" << endl;
	bool IsOk = true;
	do {

		IsOk = true;
		cout << "Enter nickname: ";
		cin >> name;
		for (int i = 0; i < count; i++)
		{
			if (name.compare(this->users[i].getNickname()) == 0)
			{
				cout << "There is a user with that name already!" << endl;
				IsOk = false;
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

int System::signIn(int count)
{
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

bool System::PhotoValidation(string photo)
{
	int index = 0;
	if (photo[index] == '.')
		return false;

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
	return false;
}

void System::Addtour(User& cur_user, int& destNumber)
{
	string destination, comment, photo;
	int grade, photosNumber;
	Date aDate, dDate;

	cout << "Destination: " << endl;
	cin >> destination;

	cout << "\nEnter arrival date" << endl;
	cin >> aDate.year >> aDate.month >> aDate.day;

	cout << "\nEnter departure date" << endl;
	cin >> dDate.year >> dDate.month >> dDate.day;

	bool isOk = true;
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
	cin >> comment;

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

int System::run()
{
	User cur_user;
	string name, password, email, destination, comment, photo, fr, personal_acc;
	Date Adate, Ddate;
	int photonum, option, destNumber, count = 0;
	short grade;
	ofstream UsersData(database, ios::binary | ios::app);
	if (!UsersData)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return 0;
	}
	UsersData.close();
	ofstream Dest(dlist, ios::binary | ios::app);
	if (!Dest)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return 0;
	}
	Dest.close();
	ifstream DestRead(dlist, ios::binary);
	if (!DestRead)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return 0;
	}
	DestRead.seekg(0, ios::end);
	if (DestRead.tellg() == 0)
	{
		destNumber = 0;
	}
	else
	{
		DestRead.seekg(0, ios::beg);
		DestRead.read((char*)&destNumber, sizeof(int));
		destlist = new DestinationsList[destNumber];
		for (int i = 0; i < destNumber; i++)
		{
			destlist[i].LoadData(DestRead);
		}
	}
	DestRead.close();
	ifstream UsersDataR(database, ios::binary);
	if (!UsersData)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return 0;
	}
	UsersDataR.seekg(0, ios::end);
	if (UsersDataR.tellg() == 0)
	{
		UsersDataR.close();
		ofstream UsersData(database, ios::binary);
		if (!UsersData)
		{
			cout << "Error! Couldn't open the file!" << endl;
			return 0;
		}
		cur_user = signUp(count, UsersData);
		UsersData.close();

		personal_acc = cur_user.getNickname() + ".bin";
		ofstream pAcc(personal_acc, ios::binary);
		if (!pAcc)
		{
			cout << "Error! Couldn't open the file!" << endl;
			return 0;
		}
		//pAcc.write((const char*)&cur_user.FriendsCount, sizeof(int));
		//pAcc.write((const char*)&cur_user.ToursCount, sizeof(int));
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
			cout << "3. Exit" << endl;
			cin >> option;

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
						return 0;
					}
					cur_user.LoadAccInfo(pAccRead);
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
				ofstream pAcc(personal_acc, ios::binary);
				if (!pAcc)
				{
					cout << "Error! Couldn't open the file!" << endl;
					return 0;
				}
				pAcc.write((const char*)&cur_user.FriendsCount, sizeof(int));
				pAcc.write((const char*)&cur_user.ToursCount, sizeof(int));
				pAcc.close();
				break;
			}
			case 3:
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
		cout << "1. Add new tour" << endl;
		cout << "2. Check your tours" << endl;
		cout << "3. All destinations" << endl;
		cout << "4. Add a friend" << endl;
		cout << "5. Check your friends' list" << endl;
		cin >> option;
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

			break;
		}
		case 3:
		{

			break;
		}
		case 4:
		{

			break;
		}
		case 5:
		{

			break;
		}
		case 0:
		{
			cout << "Exiting the program" << endl;
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
