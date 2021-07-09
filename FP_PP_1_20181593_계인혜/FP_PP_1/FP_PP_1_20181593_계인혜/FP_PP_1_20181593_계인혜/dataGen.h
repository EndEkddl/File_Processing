#ifndef __DATA_GEN_H__
#define __DATA_GEN_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "userClass/member.h"
#include "userClass/game.h"
#include "userClass/purchase.h"
#include "iobuffer/recfile.h"

using namespace std;

void memberGen(int size);
void gameGen(int size);
void purchaseGen(int size);
string randomGen(int bound, int size);
string formatting(int num,int size);

template <class T>
char* getTXT() {

	if (is_same<T, Member>::value)
		return (char*)"listOfMember.txt";
	else if (is_same<T, Game>::value)
		return (char*)"listOfGame.txt";
	else if (is_same<T, Purchase>::value)
		return (char*)"listOfPurchase.txt";
}

template <class T>
char* getDAT() {

	if (is_same<T, Member>::value)
		return (char*)"fileOfMember.dat";
	else if (is_same<T, Game>::value)
		return (char*)"fileOfGame.dat";
	else if (is_same<T, Purchase>::value)
		return (char*)"fileOfPurchase.dat";
}

#endif