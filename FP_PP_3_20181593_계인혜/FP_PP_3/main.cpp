#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "./iobuffer/btree.h"
#include "./iobuffer/btnode.h"
#include "./iobuffer/btree.cpp"
#include "./iobuffer/btnode.cpp"
using namespace std;

Member* memberArr = new Member[12000];
Game* gameArr = new Game[12000];
Purchase* purchaseArr = new Purchase[50000];

void displayMenu() {
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << "1. showMember" << endl;
	cout << "2. showGame" << endl;
	cout << "3. showPurchase" << endl;
	cout << "4. MemberTest" << endl;
	cout << "5. GameTest" << endl;
	cout << "6. PurchaseTest" << endl;
	cout << "7. GamePurchaseSystem(Proj_2)" << endl;
	cout << "8. Exit" << endl;
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	return;
}
void displaySysMenu() {
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Search" << endl;
	cout << "2. Insert" << endl;
	cout << "3. Delete" << endl;
	cout << "4. Modify" << endl;
	cout << "5. Back to menu" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	return;
}
void GamePurchaseSystem() {
	DelimFieldBuffer buffer('|', 256);
	RecordFile <Member> MemberFile(buffer);
	RecordFile <Game> GameFile(buffer);
	RecordFile <Purchase> PurchaseFile(buffer);

	//proj2 added
	static string logID = "";
	static string logPW = "";
	static int level;
	static int flag = 0;
	int menu;
	string datFile;
	string targetID;


	if (flag == 0) {
		dataTest<Member>();
		dataTest<Game>();
		dataTest<Purchase>();
		renewIdx();
		flag = 1;
	}
	char mname[17] = "fileOfMember.dat";
	char gname[15] = "fileOfGame.dat";
	char pname[19] = "fileOfPurchase.dat";
	/*
		MemberFile.Open(mname, ios::in);
		GameFile.Open(gname, ios::in);
		PurchaseFile.Open(pname, ios::in);
	*/


	while (logID == "") {
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "          LOG-IN          " << endl;
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "Enter your ID : ";
		cin >> logID;
		cout << "Enter your PW : ";
		cin >> logPW;
		if (!searchRecord(0, mname, logID)) {
			cout << "LOG-IN FAILED!" << endl;
			logID = ""; logPW = "";
			continue;
		}
		if (!(level = searchRecordPW(0, mname, logID, logPW))) {
			cout << "LOG-IN FAILED!" << endl;
			logID = ""; logPW = "";
		}
	}

	while (1) {
		int input;

		displaySysMenu();
		cin >> menu;// not sure(string)

		switch (menu) {
		case 1: { // search
			while (1) {
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "1. Search Member" << endl;
				cout << "2. Search Game" << endl;
				cout << "3. Search Purchase" << endl;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "input the number of menu >>> ";
				cin >> input;

				if (input == 1) {
					datFile = "fileOfMember.dat"; break;
				}
				else if (input == 2) {
					datFile = "fileOfGame.dat"; break;
				}
				else if (input == 3) {
					datFile = "fileOfPurchase.dat"; break;
				}

			}

			cout << endl << "Enter an ID to search : ";
			cin >> targetID;
			if (datFile.compare(mname) == 0) {
				if (logID.compare("admin") != 0 && targetID.compare(logID) != 0) {
					cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
					break;
				}
			}
			else if (datFile.compare(pname) == 0) {
				if (logID.compare("admin") != 0 && targetID.compare(logID) != 0) {
					cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
					break;
				}
			}
			searchRecord(1, datFile, targetID);
			break;
		}
		case 2: { // insert
			insertRecord(logID, level); break;
		}
		case 3: { // delete
			deleteRecord(logID, level); break;
		}
		case 4: { // modify
			modifyRecord(logID, level); break;
		}
		default: {
			logID = "";	logPW = "";
			cout << "LOG-OUT!" << endl << endl; return;
		}
		}
	}
	cout << "Exit GamePurchaseSystem" << endl;
	return;
}
int searchRecord(int flag, string filename, string targetID) {
	Member m; Purchase p; Game g;
	Purchase* pArr = new Purchase[30];
	int ID = 0; int addr = 0;
	ifstream ifs(filename);
	int ifslast;
	int* addrArr = (int*)malloc(sizeof(int));
	int cnt = 0;
	char mname[13] = "fileOfMember";
	char gname[11] = "fileOfGame";
	char pname[19] = "fileOfPurchase.dat";

	if (ifs.fail()) {
		cout << filename << "open error!" << endl;
		return 0;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	if (filename.compare("fileOfMember.dat") == 0) {
		DelimFieldBuffer buffer('|', 1200);
		TextIndexedFile<Member> MemIdxedFile(buffer, 30, 1200);
		MemIdxedFile.Open(mname);
		char target[20];

		strcpy(target, targetID.c_str());
		if (MemIdxedFile.Read(target, m) != -1)
			ID = 1;
		ifs.close();
		buffer.Clear();
	}
	else if (filename.compare("fileOfGame.dat") == 0) {
		DelimFieldBuffer buffer('|', 1200);
		TextIndexedFile<Game> GameIdxedFile(buffer, 30, 1200);
		GameIdxedFile.Open(gname);
		char target[20];

		strcpy(target, targetID.c_str());
		if (GameIdxedFile.Read(target, g) != -1)
			ID = 2;
		ifs.close();
		buffer.Clear();
	}
	else if (filename.compare("fileOfPurchase.dat") == 0) {
		DelimFieldBuffer buffer('|', 12000);

		RecordFile <Purchase> PurchaseFile(buffer);
		PurchaseFile.Open(pname, ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifslast = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		while (ifs.tellg() < ifslast) {
			PurchaseFile.Read(p);
			ifs.seekg(p.getLength(), ifs.cur);
			if (!strcmp(p.getPurchaseID(), targetID.c_str())) {
				ID = 3;
				cnt += 1;
				break;
			}
			else if (!strcmp(p.getGameID(), targetID.c_str())) {
				ID = 3;
				cnt += 1;
				break;
			}
			else if (!p.getMemberID().compare(targetID)) {
				ID = 3;
				cnt += 1;

				addrArr = (int*)realloc(addrArr, cnt * sizeof(int));
				pArr[cnt - 1] = p;
				addrArr[cnt - 1] = addr;
			}
			addr += p.getLength();
		}
		PurchaseFile.Close();
		ifs.close();
		buffer.Clear();
	}
	else {
		cout << "Error in searchRecord function!" << endl;
		ifs.close();
	}

	if (ID) {
		if (flag) {
			cout << endl << "Finished searching!" << endl << endl;
			switch (ID) {
			case 1:	cout << m; break;
			case 2: cout << g; break;
			case 3:
				if (cnt == 1) {
					std::cout << p;
				}
				else {
					for (int i = 0; i < cnt; i++) {
						cout << pArr[i] << endl;
						cout << "++++++++++++++++++++++++++" << endl;
						cout << "start address : " << addrArr[i] << endl;
					}
				}

				break;
			}
			if (cnt == 1) {
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "start address : " << addr << endl;
			}
		}
		return 1;
	}
	else {
		if (flag) cout << "This ID does not exist" << endl << endl;
		return 0;
	}
}

int searchRecordPW(int flag, string filename, string targetID, string logPW) {
	Member m;
	ifstream ifs(filename);
	int PW = 0;
	int ifslast;
	char mname[17] = "fileOfMember.dat";

	if (ifs.fail() && flag) {
		std::cout << filename << " open error!" << endl;
		return 0;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	if (filename.compare("fileOfMember.dat") == 0) {
		DelimFieldBuffer buffer('|', 1200);
		RecordFile <Member> MemberFile(buffer);
		MemberFile.Open(mname, ios::in);
		ifs.clear();
		ifs.seekg(0, ifs.end);
		ifslast = ifs.tellg();
		ifs.seekg(0, ifs.beg);

		while (ifs.tellg() < ifslast) {
			MemberFile.Read(m);
			ifs.seekg(m.getLength(), ifs.cur);
			if (!m.getID().compare(targetID)) {
				if (!m.getPW().compare(logPW)) {
					if (atoi(m.getLevel()) == 9)
						PW = 9;
					else
						PW = 1;
					break;
				}
				else {
					PW = 0; break;
				}
			}
		}
		MemberFile.Close();
		ifs.close();
	}
	return PW;
}

void deleteRecord(string logID, int level) {

	string targetID;
	cout << "Enter ID : ";
	cin >> targetID;
	int find;
	if (level == 9) {
		if (targetID.compare(logID)) {
			if (!checkAccess(logID, targetID)) {
				cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
				return;
			}
		}
	}
	find = searchRecord(0, "fileOfMember.dat", targetID);
	if (!find) find = searchRecord(0, "fileOfGame.dat", targetID);
	if (!find) find = searchRecord(0, "fileOfPurchase.dat", targetID);
	if (!find) {
		cout << "This ID does not exist" << endl << endl;
		return;
	}

	deleteMember(targetID);
	deleteGame(targetID);
	deletePurchase(targetID);

	return;
}
void deleteMember(string targetID) {

	char mname[17] = "fileOfMember.dat";
	idx[0] = 0;
	ifstream ifs("fileOfMember.dat");
	if (ifs.fail()) {
		std::cout << "Open error!(fileOfMember.dat)" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Member m;
	int ifslast;
	int ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open(mname, ios::in);
	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifslast = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifslast) {
		MemberFile.Read(m);
		if (!m.getID().compare(targetID)) {
			ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			memberArr[idx[0]] = m;
			idx[0] += 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	MemberFile.Close();

	if (ID) {
		MemberFile.Create(mname, ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < idx[0]; i++) {
			if ((recaddr = MemberFile.Write(memberArr[i])) == -1)
				std::cout << "Write Error!" << endl;
		}
		MemberFile.Close();

		TextIndex MemberIndex(1200);
		MemberFile.Open(mname, ios::in);

		while (1) {
			Member m;
			int recaddr = MemberFile.Read(m);
			if (recaddr == -1) break;
			MemberIndex.Insert(m.Key(), recaddr);
		}
		MemberFile.Close();

		TextIndexBuffer idxbuf(30, 1200);
		BufferFile MemIdxFile(idxbuf);
		char indName[17] = "fileOfMember.ind";
		MemIdxFile.Create(indName, ios::out | ios::trunc);
		MemIdxFile.Rewind();
		idxbuf.Pack(MemberIndex);
		int result = MemIdxFile.Write();
		MemIdxFile.Close();

		cout << endl << "Finished deleting!(Member)" << endl << endl;
	}
	ifs.close();
}

void deleteGame(string targetID) {

	char gname[15] = "fileOfGame.dat";

	idx[0] = 0;
	ifstream ifs("fileOfGame.dat");
	if (ifs.fail()) {
		cout << "Open error!(fileOfGame.dat)" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Game g;
	int ifslast;
	int ID = 0;
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Game> GameFile(buffer);

	GameFile.Open(gname, ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifslast = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (ifs.tellg() < ifslast) {
		GameFile.Read(g);
		if (!memcmp(g.getID(), targetID.c_str(), strlen(g.getID()))) {
			ID = 1;
			ifs.seekg(g.getLength(), ifs.cur);
		}
		else {
			gameArr[idx[0]] = g;
			idx[0] += 1;
		}
		ifs.seekg(g.getLength(), ifs.cur);
	}
	GameFile.Close();


	if (ID) {
		idx[2] -= 1;
		GameFile.Create(gname, ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < idx[0]; i++) {
			if ((recaddr = GameFile.Write(gameArr[i])) == -1)
				std::cout << "Write Error!" << endl;
		}
		GameFile.Close();

		TextIndex GameIndex(1200);

		GameFile.Open(gname, ios::in);
		while (1) {
			int recaddr = GameFile.Read(g);
			if (recaddr == -1) break;
			GameIndex.Insert(g.Key(), recaddr);
		}
		GameFile.Close();

		char indName[15] = "fileOfGame.ind";
		TextIndexBuffer Gameidxbuffer(10, 1200);
		BufferFile GameIdxFile(Gameidxbuffer);
		GameIdxFile.Create(indName, ios::out || ios::trunc);
		GameIdxFile.Rewind();

		Gameidxbuffer.Pack(GameIndex);
		int result = GameIdxFile.Write();
		GameIdxFile.Close();

		cout << endl << "Finished deleting!(Game)" << endl << endl;
	}
	ifs.close();
}

void deletePurchase(string targetID) {

	char pname[19] = "fileOfPurchase.dat";
	char indName[19] = "fileOfPurchase.ind";

	idx[0] = 0;
	ifstream ifs("fileOfPurchase.dat");
	if (ifs.fail()) {
		cout << "Open error!(fileOfPurchase.dat)" << endl;
		return;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	Purchase m;
	int ifslast;
	int ID = 0;
	char key[150];
	int deleteIdx = 0;

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open(pname, ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifslast = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	int i = 0;
	while (ifs.tellg() < ifslast) {
		
		PurchaseFile.Read(m);
		if (!strcmp(m.getPurchaseID(), targetID.c_str())) {
			ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
			key[deleteIdx] = m.Key();
			deleteIdx++;
			idx[3]--;
		}
		else if (!strcmp(m.getGameID(), targetID.c_str())) {
			ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
			key[deleteIdx] = m.Key();
			deleteIdx++;
			idx[3]--;
		}
		else if (!m.getMemberID().compare(targetID)) {
			ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
			key[deleteIdx] = m.Key();
			deleteIdx++;
			idx[3]--;
		}
		else {
			purchaseArr[idx[0]] = m;
			idx[0] += 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	PurchaseFile.Close();

	if (ID) {
		PurchaseFile.Create(pname, ios::out | ios::trunc);
		int recaddr;
		for (int i = 0; i < idx[0]; i++) {
			if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
				cout << "Write Error!" << endl;
		}
		PurchaseFile.Close();
		cout << endl << "Finished deleting!(Purchase)" << endl << endl;
	}
	ifs.close();
}

void modifyRecord(string logID, int level) {
	string targetID;
	string filename;
	string input = "";
	int find;
	char mname[17] = "fileOfMember.dat";
	char gname[15] = "fileOfGame.dat";
	char pname[19] = "fileOfPurchase.dat";

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Modify Member" << endl;
	cout << "2. Modify Game" << endl;
	cout << "3. Modify Purchase" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> input;
	switch (atoi(input.c_str())) {
	case 1: filename = "fileOfMember.dat"; break;
	case 2: filename = "fileOfGame.dat"; break;
	case 3: filename = "fileOfPurchase.dat"; break;
	case 4: return;
	}


	cout << "Enter an ID to modify : ";
	cin >> targetID;

	if (level == 9) {
		if (filename.compare("fileOfGame.dat") == 0) {
			cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
			return;
		}
		else if (filename.compare("fileOfPurchase.dat") == 0) {
			if (targetID.compare(logID) != 0) {
				cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
				return;
			}
		}
		else if (filename.compare("fileOfMember.dat") == 0) {
			if (targetID.compare(logID) != 0) {
				cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
				return;
			}
		}
	}

	if (filename.compare("fileOfMember.dat") != 0 && filename.compare("fileOfPurchase.dat") != 0 && filename.compare("fileOfGame.dat") != 0) {
		cout << "WARNING : INVALID FILE NAME" << endl << endl;
		return;
	}

	find = searchRecord(0, filename, targetID);

	if (find == 1) {

		if (filename.compare("fileOfMember.dat") == 0) {
			idx[0] = 0;
			ifstream ifs("fileOfMember.dat");
			if (ifs.fail()) {
				cout << "Open error!(fileOfMember.dat)" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Member m;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Member> MemberFile(buffer);
			int ifslast;
			int ID = 0;
			MemberFile.Open(mname, ios::in);

			ifs.clear();
			ifs.seekg(0, ifs.end);
			ifslast = ifs.tellg();
			ifs.seekg(0, ifs.beg);

			while (idx[0] < idx[1]) {
				if (MemberFile.Read(m) == -1) {
					cout << "Read error!(fileOfMember.dat)" << endl;
					break;
				}
				if (ID == 0 && m.getID().compare(targetID) == 0) {
					ID = 1;
					string tmp;
					char updateTmp[100];

					cout << "Enter New Password : ";
					cin >> tmp;
					m.setPW(tmp);

					cout << "Enter New Name : ";
					cin >> tmp;
					m.setName(tmp);

					cout << "Enter New Email : ";
					cin >> tmp;
					m.setEmail(tmp);

					cout << "Enter New Address : ";
					cin >> tmp;
					m.setAddr(tmp);

					cout << "Enter New Birthday(xxxx/yy/zz) : ";
					cin >> updateTmp;
					m.setBirthday(updateTmp);

					cout << "Enter New Grade : ";
					cin >> updateTmp;
					m.setGrade(updateTmp[0]);

					cout << endl << m;
				}
				memberArr[idx[0]] = m;
				idx[0] += 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}

			ifs.close();
			MemberFile.Close();

			if (ID) {
				MemberFile.Create(mname, ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < idx[0]; i++) {
					if ((recaddr = MemberFile.Write(memberArr[i])) == -1)
						cout << "Write Error!" << endl;
				}
				MemberFile.Close();

				TextIndex MemberIndex(1200);
				MemberFile.Open(mname, ios::in);
				while (1) {
					Member m;
					int recaddr = MemberFile.Read(m);
					if (recaddr == -1) break;
					MemberIndex.Insert(m.Key(), recaddr);
				}
				MemberFile.Close();
				TextIndexBuffer IdxBuffer2(25, 1000);
				BufferFile MemIdxFile(IdxBuffer2);
				char idxMName[17] = "fileOfMember.ind";
				MemIdxFile.Create(idxMName, ios::out || ios::trunc);
				MemIdxFile.Rewind();
				IdxBuffer2.Pack(MemberIndex);
				MemIdxFile.Write();
				MemIdxFile.Close();
			}
			cout << endl << "Finished modifying!" << endl << endl;

		}
		else if (filename.compare("fileOfGame.dat") == 0) {
			idx[0] = 0;
			ifstream ifs("fileOfGame.dat");
			if (ifs.fail()) {
				cout << "Open error!(fileOfGame.dat)" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Game g;
			int ifslast;
			int ID = 0;
			DelimFieldBuffer buffer('|', 1000);
			RecordFile <Game> GameFile(buffer);
			GameFile.Open(gname, ios::in);

			ifs.clear();
			ifs.seekg(0, ifs.end);
			ifslast = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			while (idx[0] < idx[2]) {
				if (GameFile.Read(g) == -1) {
					cout << "Read error!(fileOfGame.dat)" << endl;
					break;
				}
				if (!memcmp(g.getID(), targetID.c_str(), strlen(g.getID()))) {
					ID = 1;
					string tmp;
					char updateTmp[100];

					cout << "Enter New Title : ";
					cin >> tmp;
					g.setTitle(tmp);

					cout << "Enter New Release Date(xxxx/yy/zz) : ";
					cin >> updateTmp;
					g.setReleaseDate(updateTmp);

					cout << "Enter New Developer : ";
					cin >> tmp;
					g.setDeveloper(tmp);

					cout << "Enter New Platform : ";
					cin >> tmp;
					g.setPlatform(tmp);

					cout << "Enter New Score(0~999) : ";
					cin >> updateTmp;
					g.setScore(updateTmp);

					cout << "Enter New Price(0~9999) : ";
					cin >> updateTmp;
					g.setPrice(updateTmp);

					ifs.seekg(g.getLength(), ifs.cur);

					cout << endl << g;

				}
				gameArr[idx[0]] = g;
				idx[0] += 1;
				ifs.seekg(g.getLength(), ifs.cur);
			}
			GameFile.Close();


			if (ID) {
				GameFile.Create(gname, ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < idx[0]; i++) {
					if ((recaddr = GameFile.Write(gameArr[i])) == -1)
						std::cout << "Write Error!" << endl;
				}
				GameFile.Close();

				TextIndex GameIndex(1200);

				GameFile.Open(gname, ios::in);
				while (1) {
					Game g;
					int recaddr = GameFile.Read(g);
					if (recaddr == -1) break;
					GameIndex.Insert(g.Key(), recaddr);
				}
				GameFile.Close();

				TextIndexBuffer Gameidxbuffer(10, 1200);
				BufferFile GameIdxFile(Gameidxbuffer);
				char idxGName[15] = "fileOfGame.ind";
				GameIdxFile.Create(idxGName, ios::out | ios::trunc);
				GameIdxFile.Rewind();

				Gameidxbuffer.Pack(GameIndex);
				int result = GameIdxFile.Write();
				GameIdxFile.Close();
			}
			ifs.close();
			cout << endl << "Finished modifying!" << endl << endl;
		}
		else if (filename.compare("fileOfPurchase.dat") == 0) {
			idx[0] = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail()) {
				cout << "Open error!(fileOfPurchase.dat)" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Purchase p;
			int ifslast;
			int ID = 0;
			DelimFieldBuffer buffer('|', 10000);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open(pname, ios::in);

			ifs.clear();
			ifs.seekg(0, ifs.end);
			ifslast = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			while (ifs.tellg() < ifslast) {
				if (PurchaseFile.Read(p) == -1) {
					break;
				}
				if (!strcmp(p.getPurchaseID(), targetID.c_str()) || !strcmp(p.getGameID(), targetID.c_str()) || !p.getMemberID().compare(targetID)) {
					ID = 1;
					char updateTmp[100];
					cout << "Enter New Purchase Date(xxxx/yy/zz) : ";
					cin >> updateTmp;
					p.setPurchaseDate(updateTmp);

					ifs.seekg(p.getLength(), ifs.cur);
					cout << endl << "Finished modifying!" << endl << endl;
					cout << endl << p;
				}
				purchaseArr[idx[0]] = p;
				idx[0] += 1;
				ifs.seekg(p.getLength(), ifs.cur);
			}
			PurchaseFile.Close();
			if (ID) {
				PurchaseFile.Create(pname, ios::out | ios::trunc);
				int recaddr;
				for (int i = 0; i < idx[0]; i++) {
					if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
						cout << "Write Error!" << endl;
				}
				PurchaseFile.Close();
			}
			ifs.close();
		}

	}
	else cout << "This ID does not exist" << endl << endl;

	return;
}

void insertRecord(string logID, int level) {
	string targetID;
	string filename;
	string input;
	int find;
	char mname[13] = "fileOfMember";
	char gname[11] = "fileOfGame";
	char pname[19] = "fileOfPurchase.dat";

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Insert Member" << endl;
	cout << "2. Insert Game" << endl;
	cout << "3. Insert Purchase" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> input;

	switch (atoi(input.c_str())) {
	case 1: filename = "fileOfMember.dat"; break;
	case 2: filename = "fileOfGame.dat"; break;
	case 3: filename = "fileOfPurchase.dat"; break;
	case 4: return;
	}

	cout << endl << "Enter an ID to insert : ";
	cin >> targetID;

	if (level == 9) {
		if (filename.compare("fileOfMember.dat") == 0 || filename.compare("fileOfGame.dat") == 0) {
			cout << "WARNING : YOU DON'T HAVE PERMISSION" << endl << endl;
			return;
		}
		if (filename.compare("fileOfMember.dat") != 0 && filename.compare("fileOfPurchase.dat") != 0 && filename.compare("fileOfGame.dat") != 0) {
			cout << "WARNING : INVALID FILE NAME" << endl << endl;
			return;
		}
	}

	find = searchRecord(0, filename, targetID);
	if (find) {
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "Already Exist!" << endl;
		cout << "++++++++++++++++++++++++++" << endl;
	}
	else {
		if (filename.compare("fileOfMember.dat") == 0) {

			Member m;
			string tmp;
			char updateTmp[100];

			m.setID(targetID);

			cout << "Enter New Password : ";
			cin >> tmp;
			m.setPW(tmp);

			cout << "Enter New Name : ";
			cin >> tmp;
			m.setName(tmp);

			cout << "Enter New Email : ";
			cin >> tmp;
			m.setEmail(tmp);

			cout << "Enter New Address : ";
			cin >> tmp;
			m.setAddr(tmp);

			cout << "Enter New Birthday(xxxx/yy/zz) : ";
			cin >> updateTmp;
			m.setBirthday(updateTmp);

			cout << "Enter New Grade : ";
			cin >> updateTmp;
			m.setGrade(updateTmp[0]);

			m.setLevel(m.getLevel());

			DelimFieldBuffer buffer('|', 1200);
			TextIndexedFile<Member> MemIdxedFile(buffer, 30, 1200);
			MemIdxedFile.Open(mname);
			MemIdxedFile.Append(m);
			MemIdxedFile.Close();
			cout << endl << "Finished inserting!" << endl << endl;
			idx[1] += 1;
		}
		else if (filename.compare("fileOfGame.dat") == 0) {

			Game g;
			string tmp;
			char updateTmp[100];

			if (strlen(targetID.c_str()) != 8) {
				cout << "WARNING : INVALID ID LENGTH (LIMIT : 8)" << endl << endl;
				return;
			}
			g.setID(targetID.c_str());

			cout << "Enter New Title : ";
			cin >> tmp;
			g.setTitle(tmp);

			cout << "Enter New Release Date(xxxx/yy/zz) : ";
			cin >> updateTmp;
			g.setReleaseDate(updateTmp);

			cout << "Enter New Developer : ";
			cin >> tmp;
			g.setDeveloper(tmp);

			cout << "Enter New Platform : ";
			cin >> tmp;
			g.setPlatform(tmp);

			cout << "Enter New Score(0~999) : ";
			cin >> updateTmp;
			g.setScore(updateTmp);

			cout << "Enter New Price(0~9999) : ";
			cin >> updateTmp;
			g.setPrice(updateTmp);

			DelimFieldBuffer buffer('|', 1200);
			TextIndexedFile<Game> GameIdxedFile(buffer, 30, 1200);
			GameIdxedFile.Open(gname);
			GameIdxedFile.Append(g);
			GameIdxedFile.Close();
			cout << endl << "Finished inserting!" << endl << endl;
			idx[2] += 1;
		}
		else if (filename.compare("fileOfPurchase.dat") == 0) {
			idx[0] = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail()) {
				cout << "Open error!(fileOfPurchase.dat)" << endl;
				return;
			}
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');

			Purchase n;
			int ifslast;
			DelimFieldBuffer buffer('|', 12000);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open(pname, ios::in);

			ifs.clear();
			ifs.seekg(0, ifs.end);
			ifslast = ifs.tellg();
			ifs.seekg(0, ifs.beg);
			Purchase m_temp;
			while (ifs.tellg() < ifslast) {
				PurchaseFile.Read(n);
				if (!strcmp(m_temp.getPurchaseID(), n.getPurchaseID())) {
					break;
				}
				m_temp = n;

				purchaseArr[idx[0]] = n;
				idx[0] += 1;
				ifs.seekg(n.getLength(), ifs.cur);
			}

			Purchase p;
			char updateTmp[100];
			string tmp;

			if (strlen(targetID.c_str()) != 12) {
				cout << "WARNING : INVALID ID LENGTH (LIMIT : 12)" << endl << endl;
				return;
			}
			p.setPurchaseID(targetID.c_str());

			cout << "Enter New Game ID : ";
			cin >> tmp;
			if (strlen(tmp.c_str()) != 8) {
				cout << "WARNING : INVALID ID LENGTH (LIMIT : 8)" << endl << endl;
				return;
			}
			int find_flag = searchRecord(0, "fileOfGame.dat", tmp);
			if (!find_flag) {
				cout << "This ID does not exist" << endl << endl;
				return;
			}
			p.setGameID(tmp.c_str());

			cout << "Enter New Member ID : ";
			cin >> tmp;

			find_flag = searchRecord(0, "fileOfMember.dat", tmp);
			if (!find_flag) {
				cout << "This ID does not exist" << endl << endl;
				return;
			}
			p.setMemberID(tmp);

			cout << "Enter New Purchase Date(xxxx/yy/zz) : ";
			cin >> updateTmp;
			p.setPurchaseDate(updateTmp);

			purchaseArr[idx[0]] = p;
			idx[0] += 1;

			PurchaseFile.Close();
			PurchaseFile.Create(pname, ios::out | ios::trunc);
			int recaddr;
			for (int i = 0; i < idx[0]; i++) {
				if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1)
					std::cout << "Write Error!" << endl;
			}
			PurchaseFile.Close();
			cout << endl << "Finished inserting!" << endl << endl;
			idx[3] += 1;
			ifs.close();

		}

	}
}

int checkAccess(string logID, string targetID) {
	int ifslast;
	int ID = 0;
	Purchase p;
	ifstream ifs("fileOfPurchase.dat");
	char pname[20] = "fileOfPurchase.dat";

	if (ifs.fail()) {
		cout << "Open error!(fileOfPurchase.dat)" << endl;
		return 0;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open(pname, ios::in);
	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifslast = ifs.tellg();
	ifs.seekg(0, ifs.beg);

	while (ifs.tellg() < ifslast) {
		PurchaseFile.Read(p);
		ifs.seekg(p.getLength(), ifs.cur);
		if (logID.compare(p.getMemberID()) == 0) {
			if (!strcmp(p.getPurchaseID(), targetID.c_str())) {
				ID = 1;
				break;
			}
			else if (!strcmp(p.getGameID(), targetID.c_str())) {
				ID = 1;
				break;
			}
			else if (!p.getMemberID().compare(targetID)) {
				ID = 1;
				break;
			}

		}
	}
	PurchaseFile.Close();
	ifs.close();

	return ID;
}
void renewIdx() {
	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);
	TextIndex MemberIndex(1200);

	char mname[17] = "fileOfMember.dat";
	char gname[15] = "fileOfGame.dat";
	char pname[20] = "fileOfPurchase.dat";
	char mIndName[17] = "fileOfMember.ind";
	char gIndName[15] = "fileOfGame.ind";
	char pIndName[20] = "fileOfPurchase.ind";

	MemberFile.Open(mname, ios::in);
	while (1) {
		Member m;
		int recaddr = MemberFile.Read(m);
		if (recaddr == -1) break;
		MemberIndex.Insert(m.Key(), recaddr);
	}
	MemberFile.Close();

	TextIndexBuffer idxbuf(30, 1200);
	BufferFile MemIdxFile(idxbuf);
	MemIdxFile.Create(mIndName, ios::out | ios::trunc);
	MemIdxFile.Rewind();

	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();

	DelimFieldBuffer buffer1('|', 1000);
	RecordFile <Game> GameFile(buffer1);
	TextIndex GameIndex(1200);

	GameFile.Open(gname, ios::in);
	while (1) {
		Game g;
		int recaddr = GameFile.Read(g);
		if (recaddr == -1) break;
		GameIndex.Insert(g.Key(), recaddr);
	}
	GameFile.Close();

	TextIndexBuffer Gameidbuffer(30, 1200);
	BufferFile GameIdxFile(Gameidbuffer);
	GameIdxFile.Create(gIndName, ios::out | ios::trunc);
	GameIdxFile.Rewind();

	Gameidbuffer.Pack(GameIndex);
	result = GameIdxFile.Write();
	GameIdxFile.Close();

	result = 0;
	DelimFieldBuffer buffer2('|', 1200);
	RecordFile <Purchase> PurchaseFile(buffer2);
	result = bt.Create(pIndName, ios::in | ios::out | ios::trunc);
	if (!result) {
		std::cout << "Please delete fileOfPurchase.ind" << endl;
		return;
	}
	PurchaseFile.Open(pname, ios::in);

	char key = 1;
	while (1) {
		Purchase p;
		int recaddr = PurchaseFile.Read(p);
		if (recaddr == -1) break;
		p.setKey(key);
		bt.Insert(p.Key(), recaddr);
		key += 1;
	}
	PurchaseFile.Close();
}

void deleteKey() {
	string temp;
	char pname[20] = "fileOfPurchase.dat";
	char pIndName[20] = "fileOfPurchase.ind";

	cout << "Want key: ";
	cin >> temp;
	int temp_int = atoi(temp.c_str());
	char temp_char = (char)temp_int;
	if (bt.Search(temp_char) == -1) {
		cout << "this key doesn't exist in DB." << endl;
		return;
	}
	else {
		int recaddr;
		DelimFieldBuffer buffer('|', 1000);
		RecordFile<Purchase> PurchaseFile(buffer);
		PurchaseFile.Open(pname, ios::in);
		idx[0] = 0;

		while (1) {
			Purchase p;
			if (PurchaseFile.Read(p) == -1)
				break;
			if (p.Key() == temp_char) {
				cout << p;
				continue;
			}
			purchaseArr[idx[0]] = p;
			idx[0]++;
		}
		PurchaseFile.Close();
		PurchaseFile.Create(pname, ios::out | ios::trunc);
		for (int i = 0; i < idx[0]; i++) {
			recaddr = PurchaseFile.Write(purchaseArr[i]);
			BTreeNode<char> * BTNode = bt.FindLeaf(purchaseArr[i].Key());
			int find_key = true;
			for (int j = 0; j < BTNode->numKeys(); j++) {
				if (BTNode->Keys[j] == purchaseArr[i].Key()) {
					BTNode->RecAddrs[j] = recaddr;
					find_key = false;
					break;
				}
			}
			if (find_key)
				BTNode->RecAddrs[BTNode->numKeys()] = recaddr;
			bt.Store(BTNode);
		}
		bt.Remove(temp_char);
		PurchaseFile.Close();
		cout << "Deleting Complete from fileOfPurchase.dat" << endl;
	}
}
int main() {

	int menu;

	//	memberGen(1000);
	//	gameGen(1000);
	//	purchaseGen(10000);
	idx[0] = 0;
	while (1) {
		displayMenu();

		cin >> menu;
		cout << endl;
		switch (menu) {
		case 1: showData<Member>(); break;
		case 2: showData<Game>(); break;
		case 3: showData<Purchase>(); break;
		case 4: dataTest<Member>(); break;
		case 5: dataTest<Game>(); break;
		case 6: dataTest<Purchase>(); break;
		case 7: GamePurchaseSystem(); break;
		case 8: return 0;
		default: break;
		}

	}

	return 0;
}

