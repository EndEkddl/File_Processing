//textind.cc
#include "textind.h"
#include <iostream>
#include <string>

TextIndex::TextIndex(int maxKeys, int unique)
	: NumKeys(0), Keys(0), RecAddrs(0)
{
	Init(maxKeys, unique);
}

TextIndex :: ~TextIndex()
{
	delete Keys; delete RecAddrs;
}

int TextIndex::Insert(const char* key, int recAddr)
{
	int i;
	int index = Find(key);
	if (Unique && index >= 0) return 0; // key already in
	if (NumKeys == MaxKeys) return 0; //no room for another key
	for (i = NumKeys - 1; i >= 0; i--)
	{
		if (strcmp(key, Keys[i]) > 0) break; // insert into location i+1
		Keys[i + 1] = Keys[i];
		RecAddrs[i + 1] = RecAddrs[i];
	}
	Keys[i + 1] = _strdup(key);
	RecAddrs[i + 1] = recAddr;
	NumKeys++;
	return 1;
}

int TextIndex::Remove(const char* key)
{
	// remove the element with its key 
	// in the arrays of Keys and RecAddrs
	int index = Find(key);
	if (index < 0) return 0; // key not in index
	for (int i = index; i < NumKeys; i++)
	{
		Keys[i] = Keys[i + 1];
		RecAddrs[i] = RecAddrs[i + 1];
	}
	NumKeys--;
	return 1;
}

int TextIndex::Search(const char* key) const
{
	
	// project 2 : chapter 7. 16 
	// return "recAddr" of key
	int l = 0, h = NumKeys - 1;
	while (l <= h) {
		int mid = (l+ h) / 2;
		int compare = strcmp(Keys[mid], key);
		if (compare > 0) h = mid - 1;
		else if (compare < 0) l = mid + 1;
		else return RecAddrs[mid];
	}
	return -1;
}

void TextIndex::Print(ostream& stream) const
{
	stream << "Text Index max keys " << MaxKeys
		<< " num keys " << NumKeys << endl;
	for (int i = 0; i < NumKeys; i++)
		stream << "\tKey[" << i << "] " << Keys[i]
		<< " RecAddr " << RecAddrs[i] << endl;
}

int TextIndex::Find(const char* key) const
{
	// return index
	for (int i = 0; i < NumKeys; i++)
		if (strcmp(Keys[i], key) == 0) return i;// key found
	return -1;// not found
}

int TextIndex::Init(int maxKeys, int unique)
{
	Unique = unique != 0;
	if (maxKeys <= 0)
	{
		MaxKeys = 0;
		return 0;
	}
	MaxKeys = maxKeys;
	Keys = new char* [maxKeys];
	RecAddrs = new int[maxKeys];
	return 1;
}

int TextIndex::FirstRecAddr() {
	return RecAddrs[0];
};

int TextIndex::NextRecAddr(const char* key) {
	int nextIdx = Find(key) + 1;
	if (nextIdx >= NumKeys) return -1;
	return RecAddrs[nextIdx];
};