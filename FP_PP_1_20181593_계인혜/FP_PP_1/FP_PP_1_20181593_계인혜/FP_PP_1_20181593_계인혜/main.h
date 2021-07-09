#ifndef __MAIN_H
#define __MAIN_H

#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "dataGen.h"

#include "useIObuffer.h"
#include "./userClass/game.h"
#include "./userClass/purchase.h"
#include "./userClass/member.h"

void displayMenu();
void GamePurchaseSystem();
void searchRecord();
void insertRecord();
void deleteRecord();
void modifyRecord();

using namespace std;

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
	DelimFieldBuffer buf('|', 256);
	RecordFile<T> dataFile(buf);

	dataFile.Create(getDAT<T>(), ios::out | ios::trunc);

	int count;
	ifs >> count;
	ifs.ignore(256, '\n');

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
