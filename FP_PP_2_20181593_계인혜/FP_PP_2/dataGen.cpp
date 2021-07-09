#define _CRT_SECURE_NO_WARNINGS
#include "dataGen.h"

using namespace std;

string randomGen(int size) {
	string ret = "";
	for (int i = 0; i < size; i++) {
		ret += (char)((rand() % 10) + '0');
	}
	return ret;
}

string formatting(int num, int size) {
	string ret = "";

	for (int i = 0; i < size; i++) { ret += "0"; }

	char mod;
	for (;;) {
		if (num <= 0) break;
		mod = (char)((num % 10) + '0');
		ret[size - 1] = mod;
		size--;
		num /= 10;
	}
	return ret;
}
void memberGen(int size) {
	ofstream ofs(getTXT<Member>());

	string ID;
	string Password;
	string Name;
	string E_mail;
	string Address;
	char Birthday[11];
	char Class[2];
	char Level[2];

	srand(time(NULL));

	ofs << size << '\n';

	for (int i = 1; i <= size; i++) {
		string tmp;
		int x;
		ID = "memID" + to_string(i);
		Password = "memPW" + to_string(i);
		Name = "mName_" + to_string(i);
		E_mail = ID + "@gmail.com";
		Address = "mAdd_" + to_string(i);
		tmp = "";
		x = 1980 + (rand() % 30);
		tmp += formatting(x, 4).c_str();
		tmp += "/";
		x = rand() % 12 + 1; tmp += formatting(x, 2).c_str();
		tmp += "/";
		x = rand() % 31 + 1; tmp += formatting(x, 2).c_str();
		strcpy(Birthday, tmp.c_str());

		string temp = "";
		temp += (char)((rand() % 3) + 'A');

		strcpy(Class, temp.c_str());

		strcpy(Level, "9");
		ofs << ID << '|' << Password << '|' << Name << '|'
			<< E_mail << '|' << Address << '|' << Birthday << '|' << Class << '|' << Level << endl;
	}
}

void gameGen(int size) {
	ofstream ofs(getTXT<Game>());

	char ID[9];
	string Title;
	char Release_date[11];
	string Developer;
	string Platform;
	char Score[3];
	char Price[4];

	srand(time(NULL));

	ofs << size << endl;

	for (int i = 1; i <= size; i++) {
		int x;
		string tmp;
		strcpy(ID, formatting(i, 8).c_str());
		tmp = "";
		Title = "gTitle_" + to_string(i);

		x = rand() % 20 + 2000;
		tmp = formatting(x, 4).c_str();
		tmp += "/";

		x = rand() % 12 + 1;
		tmp += formatting(x, 2).c_str();
		tmp += "/";
		x = rand() % 31 + 1;
		tmp += formatting(x, 2).c_str();
		strcpy(Release_date, tmp.c_str());

		Developer = "gm_dev" + to_string(i);
		Platform = "gm_Pf" + to_string(i);
		x = rand() % 100;
		strcpy(Score, formatting(x, 2).c_str());
		x = rand() % 1000;
		strcpy(Price, formatting(x, 3).c_str());

		ofs << ID << '|' << Title << '|' << Release_date << '|'
			<< Developer << '|' << Platform << '|' << Score << '|' << Price << endl;
	}
}

void purchaseGen(int size) {
	ofstream ofs(getTXT<Purchase>());

	char PurchaseID[13];
	char GameID[9];
	string MemberID;
	char PurchaseDate[11];

	srand(time(NULL));

	ofs << size << endl;

	for (int i = 1; i <= size; i++) {
		string tmp = "";
		int x;
		strcpy(PurchaseID, formatting(i, 12).c_str());

		x = rand() % 1000 + 1;
		strcpy(GameID, formatting(x, 8).c_str());

		tmp = "";
		x = rand() % 1000 + 1;
		MemberID = "memID" + to_string(x);

		x = rand() % 20 + 2000;
		tmp = formatting(x, 4).c_str();
		tmp += "/";

		x = rand() % 12 + 1;
		tmp += formatting(x, 2).c_str();
		tmp += "/";
		x = rand() % 31 + 1;
		tmp += formatting(x, 2).c_str();
		strcpy(PurchaseDate, tmp.c_str());


		ofs << PurchaseID << '|' << GameID << '|' << MemberID << '|'
			<< PurchaseDate << endl;
	}
}