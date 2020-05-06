#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "User.h"
#include "DestinationList.h"
#include "System.h"
using namespace std;
int main()
{
	System::i().run();
	
	return 0;
}