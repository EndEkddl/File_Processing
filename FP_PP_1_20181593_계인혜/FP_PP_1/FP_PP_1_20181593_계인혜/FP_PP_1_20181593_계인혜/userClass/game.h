// game.h
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "../useIOBuffer.h"
using namespace std;

class Game
{
private:
	char ID[9];
	string Title;
	char Release_date[11];
	string Developer;
	string Platform;
	char Score[3];
	char Price[4];
public:
	//operations
	Game();
	Game(const char* newID);
	Game(const Game &s);

	Game & operator = (const Game &s);
	bool operator == (const Game &s);
	bool operator != (const Game &s);

	friend istream & operator >> (istream &is, Game &s);
	friend ostream & operator << (ostream &os, Game &s);

	void setID(const char* newID) { memcpy(ID, newID, 9); }
	void setTitle(const string newTitle) { Title = newTitle; }
	void setReleaseDate(const char* newRD) { memcpy(Release_date, newRD, 11); }
	void setDeveloper(const string newDev) { Developer = newDev; }
	void setPlatform(const string newPlat) { Platform = newPlat; }
	void setScore(const char* newScore) { memcpy(Score, newScore, 3); }
	void setPrice(const char* newPrice) { memcpy(Price, newPrice, 4); }

	char* getID() { return ID; }
	string getTitle() { return Title; }
	char* getReleaseDate() { return Release_date; }
	string getDeveloper() { return Developer; }
	string getPlatform() { return Platform; }
	char* getScore() { return Score; }
	char* getPrice() { return Price; }


	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
};

istream & operator >> (istream &is, Game &s);
ostream & operator << (ostream &os, Game &s);
#endif
