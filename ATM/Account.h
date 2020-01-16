#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

class Account
{
public:
	string name;
	string idNumber;
	string password;
	int balance;

	void getData(string name, string idNum, string pw, int balance = 0) // °èÁÂ »ý¼º
	{
		this->name = name;
		this->idNumber = idNum;
		this->password = pw;
		this->balance = balance;
	}
};

#endif