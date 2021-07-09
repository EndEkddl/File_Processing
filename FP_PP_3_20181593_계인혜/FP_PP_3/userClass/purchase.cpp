#include "purchase.h"
#include <iostream>
#include <sstream>

Purchase::Purchase() {}
Purchase::Purchase(const char* newID) { setPurchaseID(newID); }
Purchase::Purchase(const Purchase& s) {
	setPurchaseID(s.PurchaseID);
	setGameID(s.GameID);
	setMemberID(s.MemberID);
	setPurchaseDate(s.Purchase_date);
	setKey(s.key);
}

Purchase& Purchase::operator=(const Purchase& s) {
	setPurchaseID(s.PurchaseID);
	setGameID(s.GameID);
	setMemberID(s.MemberID);
	setPurchaseDate(s.Purchase_date);
	setKey(s.key);
	return *this;
}

bool Purchase::operator==(const Purchase& s) {
	if (strcmp(s.PurchaseID, PurchaseID) == 0) return true;
	else return false;
}

bool Purchase::operator!=(const Purchase& s) {
	if (strcmp(s.PurchaseID, PurchaseID) != 0) return true;
	else return false;
}

int Purchase::Pack(IOBuffer& Buffer) const {
	int numBytes;
	string PurchaseIDStr(PurchaseID, 13);
	string GameIDStr(GameID, 9);
	string PurchaseDateStr(Purchase_date, 11);
	char tmp[2] = { key, '\0' };
	string keyStr(tmp, 1);

	Buffer.Clear();
	numBytes = Buffer.Pack(PurchaseIDStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(GameIDStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(MemberID.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(PurchaseDateStr.c_str());
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(keyStr.c_str());
	if (numBytes == -1) return FALSE;

	return TRUE;
}

int Purchase::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[256];
	char tmp[1000];

	numBytes = Buffer.Unpack(PurchaseID, 13);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(GameID, 9);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return FALSE;
	MemberID = buf;
	numBytes = Buffer.Unpack(Purchase_date, 11);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Unpack(tmp, 2);
	key = tmp[0];
	if (numBytes == -1) return FALSE;
	return TRUE;
}

istream& operator >> (istream& is, Purchase& s) {

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
	s.setPurchaseID(token.data());
	getline(iss, token, '|');
	s.setGameID(token.data());
	getline(iss, token, '|');
	s.setMemberID(token.data());
	getline(iss, token, '|');
	s.setPurchaseDate(token.data());
	getline(iss, token, '|');

	return is;
}

ostream& operator << (ostream& os, Purchase& s) {
	string PurchaseIDStr(s.PurchaseID, 13);
	string GameIDStr(s.GameID, 9);
	string PurchaseDateStr(s.Purchase_date, 11);
	char tmp[2] = { s.key, '\0' };
	string keyStr(tmp, 2);

	os << "Purchase ID : " << PurchaseIDStr << endl;
	os << "Game ID : " << GameIDStr << endl;
	os << "Member ID : " << s.MemberID << endl;
	os << "Purchase Date : " << PurchaseDateStr << endl;
	os << "Key : " << keyStr << endl << endl;
	return os;
}

char Purchase::Key() { return key; }