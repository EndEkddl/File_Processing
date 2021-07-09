// member.h
#ifndef MEMBER_H
#define MEMBER_H
#include <iostream>
#include <string>
#include "../useIOBuffer.h"
using namespace std;

class Member
{
private:
	string ID;
	string Password;
	string Name;
	string E_mail;
	string Address;
	char Birthday[11];
	char Class;

public:
	//operations
	Member();
	Member(const string newID);
	Member(const Member &s);

	Member & operator = (const Member &s);
	bool operator == (const Member &s);
	bool operator != (const Member &s);

	friend istream& operator >> (istream &is, Member &s);
	friend ostream& operator << (ostream &os, Member &s);

	void setID(const string newID) { ID = newID; };
	void setPW(const string newPW) { Password = newPW; };
	void setName(const string newName) { Name = newName; };
	void setEmail(const string newEmail) { E_mail = newEmail; };
	void setAddr(const string newAddr) { Address = newAddr; };
	void setBirthday(const char* newBirthday) { memcpy(Birthday, newBirthday, 11); };
	void setGrade(const char newGrade) { Class = newGrade; };

	string getID() { return ID; };
	string getPW() { return Password; };
	string getName() { return Name; };
	string getEmail() { return E_mail; };
	string getAddr() { return Address; };
	char* getBirthday() { return Birthday; };
	char getGrade() { return Class; };

	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
};

istream & operator >> (istream &is, Member &s);
ostream & operator << (ostream &os, Member &s);
#endif
