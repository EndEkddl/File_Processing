// purchase.h
#ifndef PURCHASE_H
#define PURCHASE_H
#include <iostream>
#include <string>
#include "../useIOBuffer.h"

using namespace std;

class Purchase
{
private:
	char PurchaseID[13];
	char GameID[9];
	string MemberID;	
	char Purchase_date[11];
public:
	//operations
	Purchase();
	Purchase(const char* newID);
	Purchase(const Purchase& s);

	Purchase& operator = (const Purchase& s);
	bool operator == (const Purchase& s);
	bool operator != (const Purchase& s);

	friend istream& operator >> (istream& is, Purchase& s);
	friend ostream& operator << (ostream& os, Purchase& s);

	void setPurchaseID(const char* newID) { memcpy(PurchaseID, newID, 13); };
	void setGameID(const char* newID) { memcpy(GameID, newID, 9); };
	void setPurchaseDate(const char* newPD) { memcpy(Purchase_date, newPD, 11); };
	void setMemberID(const string newID) { MemberID = newID; };

	char* getPurchaseID() { return PurchaseID; };
	string getMemberID() { return MemberID; };
	char* getPurchaseDate() { return Purchase_date; };
	char* getGameID() { return GameID; };
	int getLength() { return strlen(PurchaseID) + strlen(GameID) + MemberID.size() + strlen(Purchase_date); }

	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
};

istream& operator >> (istream& is, Purchase& s);
ostream& operator << (ostream& os, Purchase& s);
#endif
