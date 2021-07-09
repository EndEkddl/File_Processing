#define _CRT_SECURE_NO_WARNINGS
#include "main.h"


void displayMenu() {
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << "1. showMember" << endl;
	cout << "2. showGame" << endl;
	cout << "3. showPurchase" << endl;
	cout << "4. MemberTest" << endl;
	cout << "5. GameTest" << endl;
	cout << "6. PurchaseTest" << endl;
	cout << "7. GamePurchaseSystem" << endl;
	cout << "8. Exit" << endl;
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	return;
}
void GamePurchaseSystem() {
	DelimFieldBuffer buffer('|', 256);
	RecordFile <Member> MemberFile(buffer);
	RecordFile <Game> GameFile(buffer);
	RecordFile <Purchase> PurchaseFile(buffer);

	char mname[18] = "fileOfMember.dat";
	char gname[16] = "fileOfGame.dat";
	char pname[20] = "fileOfPurchase.dat";

	MemberFile.Open(mname, ios::in);
	GameFile.Open(gname, ios::in);
	PurchaseFile.Open(pname, ios::in);

	while (1) {
		int menu;
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "1. Search" << endl;
		cout << "2. Insert" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Modify" << endl;
		cout << "5. Back to menu" << endl;
		cout << "++++++++++++++++++++++++++" << endl;
		cout << "input the number of menu >>> ";

		cin >> menu;
		cout << endl;
		switch (menu) {
		case 1:
			searchRecord();
			break;
		case 2:
			insertRecord();
			break;
		case 3:
			deleteRecord();
			break;
		case 4:
			modifyRecord();
			break;
		case 5:
			return;
		}
	}
	return;
}

void searchRecord() {
	int menu;

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Search Member" << endl;
	cout << "2. Search Game" << endl;
	cout << "3. Search Purchase" << endl;
	cout << "4. Back to menu" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> menu;
	cout << endl;

	if (menu == 1) {
		string id;
		Member m, mRead;

		cout << endl << "Enter an ID of member to search : " ;
		
		cin.ignore();
		getline(cin, id);
		cout << endl;
		
		m.setID(id);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Member> MemberFile(buffer);
		char mname[18] = "fileOfMember.dat";
		MemberFile.Open(mname, ios::in);

		
		while (MemberFile.Read(mRead) != -1) {
			if (m == mRead) {
				cout << "Success(search)!" << endl;
				cout << mRead << endl << endl;
				MemberFile.Close();
				return;
			}
		}
		cout << "Not in here!" << endl << endl;
		MemberFile.Close();
		return;
	}
	else if (menu == 2) {
		char game_id[9];
		Game g, gRead;
		cout << endl << "Enter an ID of Game to search : " ;

		cin.ignore();
		cin >> game_id;
		cout << endl;

		g.setID(game_id);
		DelimFieldBuffer buffer('|', 256);
		RecordFile <Game> GameFile(buffer);
		char gname[16] = "fileOfGame.dat";
		GameFile.Open(gname, ios::in);

		while (GameFile.Read(gRead) != -1) {
			if (gRead == g) {
				cout << "Success(search)!" << endl;
				cout << gRead << endl << endl;
				GameFile.Close();
				return;
			}
		}
		cout << "Not in here!" << endl << endl;
		GameFile.Close();
	}
	else if (menu == 3) {
		char purchase_id[13];
		Purchase p, pRead;
		cout << endl << "Enter an ID of Purchase to search : ";

		cin.ignore();
		cin >> purchase_id;
		cout << endl;


		p.setPurchaseID(purchase_id);
		DelimFieldBuffer buffer('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer);
		char pname[20] = "fileOfPurchase.dat";
		PurchaseFile.Open(pname, ios::in);

		while (PurchaseFile.Read(pRead) != -1) {
			if (pRead == p) {
				cout << "Success(search)!" << endl;
				cout << pRead << endl << endl;
				PurchaseFile.Close();
				return;
			}
		}
		cout << "Not in here!" << endl << endl;
		PurchaseFile.Close();
	}
	else if (menu == 4) {
		return;
	}
	return;
}

void insertRecord() {
	int menu;

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Insert Member" << endl;
	cout << "2. Insert Game" << endl;
	cout << "3. Insert Purchase" << endl;
	cout << "4. Back to menu" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> menu;
	cout << endl;

	if (menu == 1) {
		string id;
		Member m, mRead;
		cout << endl << "Enter an ID of member to insert : ";

		cin.ignore();
		getline(cin, id);

		m.setID(id);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Member> MemberFile(buffer);
		char name[18] = "fileOfMember.dat";
		MemberFile.Open(name, ios::in);

		while (MemberFile.Read(mRead) != -1) {
			if (mRead == m) {
				cout << "Error : Already exists!" << endl << endl;
				MemberFile.Close();
				return;
			}
		}
		MemberFile.Close();

		MemberFile.Open(name, ios::out);
		string password;
		cout << "Enter a password: ";
		getline(cin, password);
		m.setPW(password);

		string mname;
		cout << "Enter a name: ";
		getline(cin, mname);
		m.setName(mname);

		string Email;
		cout << "Enter a Email:  ";
		getline(cin, Email);
		m.setEmail(Email);

		string address;
		cout << "Enter a address: ";
		getline(cin, address);
		m.setAddr(address);

		string tmp;
		char birthday[11];
		cout << "Enter a birthday(xxxx/yy/zz): ";
		getline(cin, tmp);
		strcpy(birthday, tmp.c_str());
		m.setBirthday(birthday);

		tmp = "";
		char Class;
		cout << "Enter a class(S/A/B/C): ";
		getline(cin, tmp);
		Class = (tmp.c_str())[0];
		m.setGrade(Class);

		MemberFile.Append(m);
		MemberFile.Close();
		cout << "Success(insert)!" << endl << endl;
	}
	else if (menu == 2) {
		char game_id[9];
		Game g, gRead;

		cout << "Enter an ID of Game to insert : ";

		cin.ignore();
		cin >> game_id;

		g.setID(game_id);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Game> GameFile(buffer);
		char name[16] = "fileOfGame.dat";
		GameFile.Open(name, ios::in);

		while (GameFile.Read(gRead) != -1) {
			if (gRead == g) {
				cout << "Error : Already exists!" << endl << endl;
				GameFile.Close();
				return;
			}
		}
		GameFile.Close();

		GameFile.Open(name, ios::out);

		string title;
		cout << "Enter a Title: ";
		cin.ignore();
		getline(cin, title);
		g.setTitle(title);

		string tmp;
		char release[11];
		cout << "Enter a Release Date(xxxx/yy/zz): ";
		getline(cin, tmp);
		strcpy(release, tmp.c_str());
		g.setReleaseDate(release);

		string developer;
		cout << "Enter a Developer: ";
		//cin.ignore();
		getline(cin, developer);
		g.setDeveloper(developer);

		string platform;
		cout << "Enter a Platform: ";
		//cin.ignore();
		getline(cin, platform);
		g.setPlatform(platform);

		string tmp2;
		char score[3];
		cout << "Enter a Score(xx): ";
		getline(cin, tmp2);
		strcpy(score, tmp2.c_str());
		g.setScore(score);

		string tmp3;
		char price[4];
		cout << "Enter a Price(xxx): ";
		getline(cin, tmp3);
		strcpy(price, tmp3.c_str());
		g.setPrice(price);

		GameFile.Append(g);
		GameFile.Close();
		cout << "Success(insert)!" << endl << endl;
	}
	else if (menu == 3) {
		char purchase_id[13];
		Purchase p, pRead;

		cout << "Enter an ID of Purchase to insert : ";
		cin.ignore();
		cin >> purchase_id;
		p.setPurchaseID(purchase_id);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer);
		
		char name[20] = "fileOfPurchase.dat";
		PurchaseFile.Open(name, ios::in);

		while (PurchaseFile.Read(pRead) != -1) {
			if (pRead == p) {
				cout << "Error : Already exists!" << endl << endl;
				PurchaseFile.Close();
				return;
			}
		}
		PurchaseFile.Close();

		PurchaseFile.Open(name, ios::out);

		string tmp2;
		char gameID[9];
		cout << "Enter a gameID : ";
		cin.ignore();
		getline(cin, tmp2);
		strcpy(gameID, tmp2.c_str());
		p.setGameID(gameID);

		string memberID;
		cout << "Enter a memberID : ";
	//	cin.ignore();
		getline(cin, memberID);
		p.setMemberID(memberID);

		string tmp3;
		char purchaseDate[11];
		cout << "Enter a Purchase Date(xxxx/yy/zz) : ";
		getline(cin, tmp3);
		strcpy(purchaseDate, tmp3.c_str());
		p.setPurchaseDate(purchaseDate);

		PurchaseFile.Append(p);
		PurchaseFile.Close();
		cout << "Success(insert)!" << endl << endl;
	}
	else if (menu == 4)  return;

	return;
}

void deleteRecord() {
	int menu;

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Delete Member" << endl;
	cout << "2. Delete Game" << endl;
	cout << "3. Delete Purchase" << endl;
	cout << "4. Back to menu" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> menu;

	if (menu == 1) {
		string id;
		Member m, mRead;

		cout << "Enter an ID of Member to delete : ";
		cin.ignore();
		getline(cin, id);

		m.setID(id);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Member> MemberFile(buffer);

		DelimFieldBuffer buffer2('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer2);

		MemberFile.Open((char *)"fileOfMember.dat", ios::in);

		vector<int> delAddr;
		vector<Purchase> delPurchase;
		int mAddr;

		while ((mAddr = MemberFile.Read(mRead)) != -1) {
			if (mRead == m) {
				MemberFile.Close();

				Purchase p, pRead;
				PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::in);
				
				int pAddr;
				while ((pAddr = PurchaseFile.Read(pRead)) != -1) {
					if (id == pRead.getMemberID()) {
						char purchase_id[13];
						strncpy(purchase_id, pRead.getPurchaseID(), 12);
						purchase_id[0] = '*';	// delete symbol
						pRead.setPurchaseID(purchase_id);
						delAddr.push_back(pAddr);
						delPurchase.push_back(pRead);
					}
				}
				PurchaseFile.Close();

				PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
				for (int i = 0; i < delAddr.size(); i++) {
					PurchaseFile.Write(delPurchase[i], delAddr[i]);
				}
				PurchaseFile.Close();

				MemberFile.Open((char *)"fileOfMember.dat", ios::out);
				id[0] = '*';
				mRead.setID(id);
				MemberFile.Write(mRead, mAddr);
				MemberFile.Close();


				cout << "Success(Delete)!" << endl << endl;
				return;
			}
		}
		cout << "Not in here!" << endl << endl;
	}
	else if (menu == 2) {
		char gameID[9];
		Game g, gRead;

		cout << "Enter an ID of Game to delete : ";
		cin >> gameID;

		//cin.ignore();


		g.setID(gameID);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Game> GameFile(buffer);

		DelimFieldBuffer buffer2('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer2);

		GameFile.Open((char*)"fileOfGame.dat", ios::in);

		vector<int> delAddr;
		vector<Purchase> delPurchase;
		int gAddr;

		while ((gAddr = GameFile.Read(gRead)) != -1) {
			if (gRead == g) {
				GameFile.Close();

				Purchase p, pRead;
				PurchaseFile.Open((char*)"fileOfPurchase.dat", ios::in);

				int pAddr;
				while ((pAddr = PurchaseFile.Read(pRead)) != -1) {
					if (strncmp(gameID, pRead.getGameID(), 8) == 0) {
						char purchase_id[13];
						strncpy(purchase_id, pRead.getPurchaseID(), 12);
						purchase_id[0] = '*';	// delete symbol
						pRead.setPurchaseID(purchase_id);
						delAddr.push_back(pAddr);
						delPurchase.push_back(pRead);
					}
				}
				PurchaseFile.Close();

				PurchaseFile.Open((char*)"fileOfPurchase.dat", ios::out);
				for (int i = 0; i < delAddr.size(); i++) {
					PurchaseFile.Write(delPurchase[i], delAddr[i]);
				}
				PurchaseFile.Close();

				GameFile.Open((char*)"fileOfGame.dat", ios::out);
				gameID[0] = '*';
				gRead.setID(gameID);
				GameFile.Write(gRead, gAddr);
				GameFile.Close();


				cout << "Success(Delete)!" << endl << endl;
				return;
			}
		}
		cout << "Not in here!" << endl << endl;
	}
	else if (menu == 3) {

		char purchaseID[13];
		Purchase p, pRead;

		cout << "Enter an ID of Purchase to delete : ";
		cin >> purchaseID;

		//cin.ignore();
		p.setPurchaseID(purchaseID);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer);

		PurchaseFile.Open((char*)"fileOfPurchase.dat", ios::in | ios::out);


		int pAddr, flag = 0;
		int prev;

		while ((pAddr = PurchaseFile.Read(pRead)) != -1) {
			
			if (pRead == p) {

				PurchaseFile.Close();
				PurchaseFile.Open((char*)"fileOfPurchase.dat", ios::out);
				purchaseID[0] = '*';	// delete symbol
				pRead.setPurchaseID(purchaseID);
				PurchaseFile.Write(pRead, pAddr);
				PurchaseFile.Close();
				flag = 1;
				cout << "Success(Delete)!" << endl << endl;
				return; 
			}
		}
		cout << "Not in here!" << endl << endl;

	}
	else if (menu == 4) return;
	
	return;
}

void modifyRecord() {
	int menu;

	cout << "++++++++++++++++++++++++++" << endl;
	cout << "1. Modify Member" << endl;
	cout << "2. Modify Game" << endl;
	cout << "3. Modify Purchase" << endl;
	cout << "4. Back to menu" << endl;
	cout << "++++++++++++++++++++++++++" << endl;
	cout << "input the number of menu >>> ";

	cin >> menu;

	if (menu == 1) {
		string id;
		Member m, mRead;

		cout << "Enter an ID of Member to Modify :" ;
		cin.ignore();
		getline(cin, id);
		cout << endl;
		m.setID(id);
		

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Member> MemberFile(buffer);

		MemberFile.Open((char *)"fileOfMember.dat", ios::in);

		int mAddr, flag = 0;
		while ((mAddr = MemberFile.Read(mRead)) != -1) {
			if (m == mRead) {
				flag = 1;
				MemberFile.Close();

				int select;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "1. Modify password" << endl;
				cout << "2. Modify name" << endl;
				cout << "3. Modify E-mail" << endl;
				cout << "4. Modify address" << endl;
				cout << "5. Modify birthday" << endl;
				cout << "6. Modify class" << endl;
				cout << "7. Back to menu" << endl;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "input the number of menu >>> ";

				cin >> select;
				cout << endl;

				if (select == 1) {
					string password;
					int len, new_len;
					cout << "Enter new password : ";
					
					cin.ignore();
					getline(cin, password);
		
					len = mRead.getPW().length();
					new_len = password.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open((char *)"fileOfMember.dat", ios::out);
						password.append(len - new_len, ' ');
						mRead.setPW(password);
						MemberFile.Write(mRead, mAddr);
					}
					else {
						MemberFile.Close();

						MemberFile.Open((char *)"fileOfMember.dat", ios::out);
						string new_id = mRead.getID();
						string copy = new_id;
						copy[0] = '*';
						mRead.setID(copy);
						MemberFile.Write(mRead, mAddr);
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						mRead.setID(new_id);
						mRead.setPW(password);
						MemberFile.Append(mRead);
						MemberFile.Close();
						
					}
					cout << "Success(modify)!" << endl << endl;
				}

				else if (select == 2) {
					string name;
					int len, new_len;
					cout << "Enter new name : ";

					cin.ignore();
					getline(cin, name);
					
					len = mRead.getName().length();
					new_len = name.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open((char *)"fileOfMember.dat", ios::out);
						name.append(len - new_len, ' ');
						mRead.setName(name);
						MemberFile.Write(mRead, mAddr);
					}
					else {
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						string new_id = mRead.getID();
						string copy = new_id;
						copy[0] = '*';
						mRead.setID(copy);
						MemberFile.Write(mRead, mAddr);
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						mRead.setID(new_id);
						mRead.setName(name);
						MemberFile.Append(mRead);
						MemberFile.Close();
						
					}
					cout << "Success(modify)!" << endl << endl;
				}

				else if (select == 3) {
					string email;
					int len, new_len;

					cout << "Enter new E-mail : " << endl;
					
					cin.ignore();
					getline(cin, email);

					len = mRead.getEmail().length();
					new_len = email.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						email.append(len - new_len, ' ');
						mRead.setEmail(email);
						MemberFile.Write(mRead, mAddr);
					}
					else {
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						string new_id = mRead.getID();
						string copy = new_id;
						copy[0] = '*';
						mRead.setID(copy);
						MemberFile.Write(mRead, mAddr);
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						mRead.setID(new_id);
						mRead.setEmail(email);
						MemberFile.Append(mRead);
						MemberFile.Close();
						
					}
					cout << "Success(modify)!" << endl << endl;
				}

				else if (select == 4) {
					string address;
					int len, new_len;
					cout << "Enter new address : ";
					cin.ignore();
					getline(cin, address);

					len = mRead.getAddr().length();
					new_len = address.length();

					if (len >= new_len) {
						MemberFile.Close();
						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						address.append(len - new_len, ' ');
						mRead.setAddr(address);
						MemberFile.Write(mRead, mAddr);
					}
					else {
						MemberFile.Close();

						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						string new_id = mRead.getID();
						string copy = new_id;
						copy[0] = '*';
						mRead.setID(copy);
						MemberFile.Write(mRead, mAddr);
						MemberFile.Close();

						
						MemberFile.Open((char*)"fileOfMember.dat", ios::out);
						mRead.setID(new_id);
						mRead.setAddr(address);
						MemberFile.Append(mRead);
						MemberFile.Close();
					
					}
					cout << "Success(modify)!" << endl << endl;
				}

				else if (select == 5) {
					char birthday[11];
					string birthday_string;
					int len, new_len;
					cout << "Enter new birthday : ";

					cin.ignore();
					getline(cin, birthday_string);
					strncpy(birthday, birthday_string.c_str(), birthday_string.size());
					
					MemberFile.Close();
					MemberFile.Open((char*)"fileOfMember.dat", ios::out);
					mRead.setBirthday(birthday);
					MemberFile.Write(mRead, mAddr);
					cout << "Success(modify)!" << endl << endl;
				}

				else if (select == 7)
					return;
			}
		}

		if (!flag)
			cout << "Not in here!" << endl << endl;
		
	}
	else if (menu == 2) {
		char gameID[9];
		Game g, gRead;

		cout << "Enter a Game ID to modify : ";
		cin.ignore();
		cin >> gameID;
		cout << endl;

		g.setID(gameID);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Game> GameFile(buffer);

		GameFile.Open((char *)"fileOfGame.dat", ios::in);

		int gAddr, flag = 0;

		while ((gAddr = GameFile.Read(gRead)) != -1) {
			if (g == gRead) {
				GameFile.Close();

				int select;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "1. Modify Title" << endl;
				cout << "2. Modify Release date" << endl;
				cout << "3. Modify Developer" << endl;
				cout << "4. Modify Platform" << endl;
				cout << "5. Modify Score" << endl;
				cout << "6. Modify Price" << endl;
				cout << "7. Back to menu" << endl;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "input the number of menu >>> ";
				cin >> select;
				cout << endl;

				if (select == 1) {
					string title;
					int len, new_len;
					cout << "Enter new title : ";
					cin.ignore();
					getline(cin, title);
				
					len = gRead.getTitle().length();
					new_len = title.length();

					if (len >= new_len) {
						GameFile.Close();
						GameFile.Open((char *)"fileOfGame.dat", ios::out);
						title.append(len - new_len, ' ');
						gRead.setTitle(title);
						GameFile.Write(gRead, gAddr);
					}
					else {
						GameFile.Close();

						GameFile.Open((char *)"fileOfGame.dat", ios::out);
						string new_id = gRead.getID();
						string copy = new_id;

						copy[0] = '*';
						gRead.setID(copy.c_str());
						GameFile.Write(gRead, gAddr);
						GameFile.Close();
											
						GameFile.Open((char *)"fileOfGame.dat", ios::out);
						gRead.setID(new_id.c_str());
						gRead.setTitle(title);
						GameFile.Append(gRead);
						GameFile.Close();

					}
					cout << "Success(modify)!" << endl << endl;
					return;
				}

				else if (select == 2) {

					char release[11];
					string release_string;
					int len, new_len;
					cout << "Enter new release date : ";

					cin.ignore();
					getline(cin, release_string);
					strncpy(release, release_string.c_str(), release_string.size());

					GameFile.Close();
					GameFile.Open((char*)"fileOfGame.dat", ios::out);
					gRead.setReleaseDate(release);
					GameFile.Write(gRead, gAddr);
					cout << "Success(modify)!" << endl << endl;
					
					return;
				}

				else if (select == 3) {

					string developer;
					int len, new_len;
					cout << "Enter new developer : ";
					cin.ignore();
					getline(cin, developer);

					len = gRead.getDeveloper().length();
					new_len = developer.length();

					if (len >= new_len) {
						GameFile.Close();
						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						developer.append(len - new_len, ' ');
						gRead.setDeveloper(developer);
						GameFile.Write(gRead, gAddr);
					}
					else {
						GameFile.Close();

						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						string new_id = gRead.getID();
						string copy = new_id;

						copy[0] = '*';
						gRead.setID(copy.c_str());
						GameFile.Write(gRead, gAddr);
						GameFile.Close();

						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						gRead.setID(new_id.c_str());
						gRead.setDeveloper(developer);
						GameFile.Append(gRead);
						GameFile.Close();

					}
					cout << "Success(modify)!" << endl << endl;
					return;
				}

				else if (select == 4) {

					string platform;
					int len, new_len;
					cout << "Enter new platform : ";
					cin.ignore();
					getline(cin, platform);

					len = gRead.getPlatform().length();
					new_len = platform.length();

					if (len >= new_len) {
						GameFile.Close();
						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						platform.append(len - new_len, ' ');
						gRead.setPlatform(platform);
						GameFile.Write(gRead, gAddr);
					}
					else {
						GameFile.Close();

						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						string new_id = gRead.getID();
						string copy = new_id;

						copy[0] = '*';
						gRead.setID(copy.c_str());
						GameFile.Write(gRead, gAddr);
						GameFile.Close();

						GameFile.Open((char*)"fileOfGame.dat", ios::out);
						gRead.setID(new_id.c_str());
						gRead.setPlatform(platform);
						GameFile.Append(gRead);
						GameFile.Close();

					}
					cout << "Success(modify)!" << endl << endl;
					return;
				}

				else if (select == 5) {
					char score[3];
					string score_string;
					int len, new_len;
					cout << "Enter new score : ";

					cin.ignore();
					getline(cin, score_string);
					strncpy(score, score_string.c_str(), score_string.size());

					GameFile.Close();
					GameFile.Open((char*)"fileOfGame.dat", ios::out);
					gRead.setScore(score);
					GameFile.Write(gRead, gAddr);
					cout << "Success(modify)!" << endl << endl;
					
					return;
				}

				else if (select == 6) {
					char price[4];
					string price_string;
					int len, new_len;
					cout << "Enter new price : ";

					cin.ignore();
					getline(cin, price_string);
					strncpy(price, price_string.c_str(), price_string.size());

					GameFile.Close();
					GameFile.Open((char*)"fileOfGame.dat", ios::out);
					gRead.setPrice(price);
					GameFile.Write(gRead, gAddr);
					cout << "Success(modify)!" << endl << endl;
					return;
				}

				else if (select == 7)
					return;
			}
		}
		if (!flag)
			cout << "Not in here!" << endl;

	}
	else if (menu == 3) {
		char purchaseID[13];
		Purchase p, pRead;

		cout << "Enter a Purchase ID to modify : ";
		//cin.ignore();
		cin >> purchaseID;
		
		p.setPurchaseID(purchaseID);

		DelimFieldBuffer buffer('|', 256);
		RecordFile <Purchase> PurchaseFile(buffer);

		PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::in);

		int pAddr, flag = 0;
		while ((pAddr = PurchaseFile.Read(pRead)) != -1) {
			if (p == pRead) {
				PurchaseFile.Close();

				int select;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "1. Modify Game ID" << endl;
				cout << "2. Modify Member ID" << endl;
				cout << "3. Modify Purchase date" << endl;
				cout << "4. Back to menu" << endl;
				cout << "++++++++++++++++++++++++++" << endl;
				cout << "input the number of menu >>> ";

				cin >> select;
				cout << endl;

				if (select == 1) {
					char gameID[9];
					string gameIDStr;
					int len, new_len;
					cout << "Enter new Game ID : ";					
					cin.ignore();
					getline(cin, gameIDStr);
					strncpy(gameID, gameIDStr.c_str(), gameIDStr.size());
			//		memset(gameID, '0', 8);
				
				//	strncpy(gameID + 8 - gameIDStr.length(), gameIDStr.c_str(), gameIDStr.size());

					DelimFieldBuffer buffer2('|', 256);
					RecordFile <Game> GameFile(buffer2);
					Game g, gRead;
					g.setID(gameID);
					GameFile.Open((char *)"fileOfGame.dat", ios::in);

					int flag2 = 0;
					while (GameFile.Read(gRead) != -1) {
						if (g == gRead) {
							flag2 = 1;
							PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
							pRead.setGameID(gameID);
							PurchaseFile.Write(pRead, pAddr);
							PurchaseFile.Close();
						}
					}
					GameFile.Close();
					cout << "Success(modify)!" << endl << endl;

					if (!flag2)
						cout << "Not in here!" << endl << endl;
				}

				else if (select == 2) {
					string memberID;
					int len, new_len;
					cout << "Enter new Member ID : ";
					cin.ignore();
					getline(cin, memberID);
				
					len = pRead.getMemberID().length();
					new_len = memberID.length();

					DelimFieldBuffer buffer2('|', 256);
					RecordFile <Member> MemberFile(buffer2);
					Member m, mRead;

					m.setID(memberID);
					MemberFile.Open((char *)"fileOfMember.dat", ios::in);

					int flag2 = 0;

					while (MemberFile.Read(mRead) != -1) {
						if (m == mRead) {
							flag2 = 1;
							if (len >= new_len) {
								PurchaseFile.Close();
								PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
								memberID.append(len - new_len, ' ');
								pRead.setMemberID(memberID);
								PurchaseFile.Write(pRead, pAddr);
							}
							else {
								PurchaseFile.Close();

								PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
								char new_id[13];
								char copy[13];

								strncpy(new_id, pRead.getPurchaseID(), 13);
								strncpy(copy, pRead.getPurchaseID(), 13);
								copy[0] = '*';
								pRead.setPurchaseID(copy);
								PurchaseFile.Write(pRead, pAddr);
								PurchaseFile.Close();

								PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
								pRead.setPurchaseID(new_id);
								pRead.setMemberID(memberID);
								PurchaseFile.Append(pRead);
								PurchaseFile.Close();

							}
							cout << "Success(modify)!" << endl << endl; return;
						}

					}

					cout << "Not in here!" << endl << endl;
				}

				else if (select == 3) {
					char purchaseDate[11];
					string purchaseDateStr;
					int len, new_len;

					cout << "Enter new Purchase Date : ";
					cin.ignore();
					getline(cin, purchaseDateStr);
					strncpy(purchaseDate, purchaseDateStr.c_str(), purchaseDateStr.size());
					
					PurchaseFile.Close();
					PurchaseFile.Open((char *)"fileOfPurchase.dat", ios::out);
					pRead.setPurchaseDate(purchaseDate);
					PurchaseFile.Write(pRead, pAddr);
					cout << "Success(modify)!" << endl << endl; return;
				}
			}
		}

	}
	else if (menu == 4) return;
	return;
}
int main() {

	int menu;

//	memberGen(1000);
//	gameGen(1000);
//	purchaseGen(10000);


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

