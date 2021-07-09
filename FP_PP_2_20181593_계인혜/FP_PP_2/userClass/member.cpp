//member.cc
#define _CRT_SECURE_NO_WARNINGS
#include "member.h"
#include <sstream>

Member::Member() {}
Member::Member(const string newID) { setID(newID); }
Member::Member(const Member& s) {
	setID(s.ID);
	setPW(s.Password);
	setName(s.Name);
	setEmail(s.E_mail);
	setAddr(s.Address);
	setBirthday(s.Birthday);
	setGrade(s.Class);
	setLevel(s.Level); // proj2 added
}
Member& Member::operator=(const Member& s) {
	setID(s.ID);
	setPW(s.Password);
	setName(s.Name);
	setEmail(s.E_mail);
	setAddr(s.Address);
	setBirthday(s.Birthday);
	setGrade(s.Class);
	setLevel(s.Level); // proj2 added
	return *this;
}

bool Member::operator==(const Member& s) {
	return (getID() == s.ID);
}

bool Member::operator!=(const Member& s) {
	return (getID() != s.ID);
}

int Member::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	string birStr(Birthday, 11);
	string gradeStr = to_string(Class);
	string levStr(Level, 2); // proj2 added

	Buffer.Clear();
	numBytes = Buffer.Pack(ID.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Password.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(E_mail.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(birStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(gradeStr.c_str());
	if (numBytes == -1) return FALSE;
	// proj2 added
	numBytes = Buffer.Pack(levStr.c_str()); 
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Member::Unpack(IOBuffer& Buffer)
{
	int numBytes;
	char buf[256];
	string gradeStr;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	ID = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Password = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Name = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	E_mail = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Address = buf;
	numBytes = Buffer.Unpack(Birthday, 11);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Class = buf[0];
	// proj2 added
	numBytes = Buffer.Unpack(buf);//
	Level[0] = buf[0];//not sure
	if (numBytes == -1) return FALSE;
	return TRUE;
}

istream& operator >> (istream& is, Member& s) {

	string str;
	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, str);
	}
	catch (istream::failure e) {
		return is;
	}

	istringstream iss(str);
	string token;

	getline(iss, token, '|');
	s.setID(token.data());
	getline(iss, token, '|');
	s.setPW(token.data());
	getline(iss, token, '|');
	s.setName(token.data());
	getline(iss, token, '|');
	s.setEmail(token.data());
	getline(iss, token, '|');
	s.setAddr(token.data());
	getline(iss, token, '|');
	s.setBirthday(token.data());
	getline(iss, token, '|');
	s.setGrade(token[0]);
	//proj2 added
	getline(iss, token, '|');// not sure
	s.setLevel(token.data());
	return is;
}

ostream& operator << (ostream& os, Member& s) {

	//char a = (s.Class[0]);
	//char b = s.Class[1];
	//char ch = (s.Class[0] - '0') * 10 + s.Class[1] - '0';
	string levStr(s.Level, 2);
	os << "ID : " << s.ID << endl;
	os << "PW : " << s.Password << endl;
	os << "Name : " << s.Name << endl;
	os << "Email : " << s.E_mail << endl;
	os << "Address : " << s.Address << endl;
	os << "Birthday : " << s.Birthday << endl;
	os << "Grade : " << s.Class  << endl;
	os << "Level : " << levStr << endl << endl;
	return os;
}

//proj2 added
char* Member::Key() {
	key.assign(ID);
	return (char*)(key.c_str());
}