//textind.h
#ifndef TEXTIND_H
#define TEXTIND_H
#include <iostream>

using namespace std;

class TextIndex
{
public:
	TextIndex(int maxKeys = 100, int unique = 1);
	~TextIndex();
	int Insert(const char* key, int recAddr);
	int Remove(const char* key);
	int Search(const char* key) const;
	void Print(ostream&) const;

	// project2 : chapter 7. 13
	int FirstRecAddr();
	int NextRecAddr(const char* key);

protected:
	int MaxKeys;
	int NumKeys;
	char** Keys;
	int* RecAddrs;
	int Find(const char* key) const;
	int Init(int maxKeys, int unique);
	int Unique; 
	friend class TextIndexBuffer;
};

#endif