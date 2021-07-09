//game.cc
#include "game.h"
#include <iostream>
#include <sstream>

Game::Game() { }
Game::Game(const char* newID) { setID(newID); }
Game::Game(const Game& s) {
	setID(s.ID);
	setTitle(s.Title);
	setReleaseDate(s.Release_date);
	setDeveloper(s.Developer);
	setPlatform(s.Platform);
	setScore(s.Score);
	setPrice(s.Price);
}
Game& Game::operator=(const Game& s) {
	setID(s.ID);
	setTitle(s.Title);
	setReleaseDate(s.Release_date);
	setDeveloper(s.Developer);
	setPlatform(s.Platform);
	setScore(s.Score);
	setPrice(s.Price);
	return *this;
}

bool Game::operator==(const Game& s) {
	if (strcmp(ID, s.ID) == 0)
		return true;
	else
		return false;
}

bool Game::operator!=(const Game& s) {
	if (strcmp(ID, s.ID) != 0)
		return true;
	else
		return false;
}

int Game::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	string idStr(ID, 9);
	string rdStr(Release_date, 11);
	string scoreStr(Score, 3);
	string priceStr(Price, 4);

	Buffer.Clear();
	numBytes = Buffer.Pack(idStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Title.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(rdStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Developer.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Platform.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(scoreStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(priceStr.c_str());
	if (numBytes == -1) return FALSE;

	return TRUE;
}

int Game::Unpack(IOBuffer& Buffer)
{
	int numBytes;
	char buf[256];
	string gradeStr;

	numBytes = Buffer.Unpack(ID, 9);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Title = buf;
	numBytes = Buffer.Unpack(Release_date, 11);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Developer = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	Platform = buf;
	numBytes = Buffer.Unpack(Score, 3);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(Price, 4);
	if (numBytes == -1) return FALSE;

	return TRUE;
}

istream& operator >> (istream& is, Game& s) {

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
	s.setTitle(token.data());
	getline(iss, token, '|');
	s.setReleaseDate(token.data());
	getline(iss, token, '|');
	s.setDeveloper(token.data());
	getline(iss, token, '|');
	s.setPlatform(token.data());
	getline(iss, token, '|');
	s.setScore(token.data());
	getline(iss, token, '|');
	s.setPrice(token.data());

	return is;
}

ostream& operator << (ostream& os, Game& s) {
	string idStr(s.ID, 9);
	string rdStr(s.Release_date, 11);
	string scoreStr(s.Score, 3);
	string priceStr(s.Price, 4);

	os << "ID : " << idStr << endl;
	os << "Title : " << s.Title << endl;
	os << "Release Date : " << rdStr << endl;
	os << "Developer : " << s.Developer << endl;
	os << "Platform : " << s.Platform << endl;
	os << "Score : " << scoreStr << endl;
	os << "Price : " << priceStr << endl << endl;

	return os;
}

//proj2 added
char* Game::Key() {
	key.assign(ID, 8);//not sure
	return (char*)(key.c_str());
}