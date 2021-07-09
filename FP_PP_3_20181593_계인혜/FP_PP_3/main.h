#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "dataGen.h"
#include "useIObuffer.h"
#include "./userClass/game.h"
#include "./userClass/purchase.h"
#include "./userClass/member.h"
#include "./iobuffer/btnode.h"
#include "./iobuffer/simpind.h"
#include "./iobuffer/btree.h"

void displayMenu();
void displaySysMenu();
void GamePurchaseSystem();

int searchRecord(int flag, string filename, string targetID);
int searchRecordPW(int flag, string filename, string targetID, string logPW);
void deleteRecord(string logID, int level);
void deleteMember(string targetID);
void deleteGame(string targetID);
void deletePurchase(string targetID);
void modifyRecord(string logID, int level);
void insertRecord(string logID, int level);
int checkAccess(string logID, string targetID);
void renewIdx();
void deleteBT();
void genPurchaseIdx();

using namespace std;

int idx[4];
const char * keys = "CSDTAMPIBWNGURKEHOLJYQZFXV";
const int BTreeSize = 4;
BTree <char> bt(BTreeSize);
char btKey;

template <class T>
void showData() {
	ifstream ifs(getTXT<T>());
	int n;

	ifs >> n;
	ifs.ignore(256, '\n');

	for (int i = 0; i < 10; i++) {
		T data;
		ifs >> data;
		cout << data;
	}
	ifs.close();
}

template <class T>
void dataTest() {

	ifstream ifs(getTXT<T>());
	DelimFieldBuffer buf('|', 1000);
	RecordFile<T> dataFile(buf);

	dataFile.Create(getDAT<T>(), ios::out | ios::trunc);
	cout << "dataTest here!" << endl;
	int count;
	char* mname = (char *)"listOfMember.txt";
	char* gname = (char *)"listOfGame.txt";
	char* pname = (char *)"listOfPurchase.txt";

	ifs >> count;
	ifs.ignore(256, '\n');

	if (strcmp((const char*)getTXT<T>(), (const char*)mname) == 0) idx[1] = count;
	else if (strcmp((const char*)getTXT<T>(), (const char*)gname) == 0) idx[2] = count;
	else if (strcmp((const char*)getTXT<T>(), (const char*)pname) == 0) idx[3] = count;

	for (int i = 0; i < count; i++) {
		T data;
		ifs >> data;
		if (dataFile.Write(data) == -1) {
			cout << "Write error in Test!\n";
			return;
		}
		if (i < 10) cout << data;
	}
	dataFile.Close();
	ifs.close();
}

#endif
