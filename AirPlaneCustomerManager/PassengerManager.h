#pragma once
#include "Time.h"
#include "Box.h"
#include "MyLib.h"
#include "DataTypes.h"
#include <iomanip>
#include <string.h>
#include <conio.h>
#include "ReadAndWriteFiles.h"
#include <vector>
#include <ctime>
#include <sstream>
#include "PlaneTypeManager.h"

void PaMAddInterface(PassengerList*, vector<Passenger*>&);
void PaMSearchInterface(PassengerList*, vector<Passenger*>&, int);
void PamDeleteInterface(PassengerList*, const string&);
void block_char(char*, int, int, int);
void block_char_number(char*, int, int, int);

void PaMMainInterface(PassengerList* PL) {
	int page = 0;
	char inputChar;
	vector<Passenger*> v;
	do {
	PaMStartingPage:
		showCur(0);
		PL->PaMPrintPassengerInforMainInterface(page, v);
		inputChar = _getch();
		if (inputChar == 59) // F1
			PaMAddInterface(PL, v);
		//if (inputChar == 61) //F3
		//	PaMSearchInterface(PL, v, 1);
		if (inputChar == 83) // Delete
			PaMSearchInterface(PL, v, 1);
		if (inputChar == 80 && PL->getTotalPassenger() / 19 * (page + 1) > 0
			&& page < PL->getTotalPassenger() / 19) {
			page++;
		} // up 
		if (inputChar == 72 && page > 0)
			page--; // down
	} while (inputChar != 27); // esc
}

void PaMAddInterface(PassengerList* PL, vector<Passenger*>& v) {
	system("cls");
	PaMAddBox();
	menuCurTime();
	flushConsoleInputBuffer();
	char inputChar;
	char* ssid = new char[13];
	char* Name = new char[80];
	char* token = new char[80];
	string lName, fName;
	ssid[0] = Name[0] = token[0] = '\0';
	SEX sex = { NOINFOR };
	do {
	addI:
		do {
			gotoxy(36, 10); std::cout << "SSID: ";
			if (ssid[0] != '\0') {
				std::cout << std::setw(12) << std::setfill(' ') << "";
			}
			showCur(1);
			block_char_number(ssid, 12, 42, 10);
			if (ssid[0] == '.') {
				PaMSearchInterface(PL, v, 0);
				return;
			}
			gotoxy(88, 4);
			std::cout << std::setw(30) << std::setfill(' ') << ""; 
			gotoxy(88, 5);
			std::cout << std::setw(30) << std::setfill(' ') << "";
			showCur(0);
			for (int i = 0; i < v.size(); i++)
				if (strcmp(PL->getSSID(v[i]), ssid) == 0) {
					goto Err;
				}
			if (strlen(ssid) == 0 || strlen(ssid) != 12 && strlen(ssid) != 9) {
				Err:
				gotoxy(88, 4);
				std::cout << "Invalid Social Security ID!!!";
				gotoxy(88, 5);
				std::cout << "Please input again!";
				continue;
			}
			break;
		} while (1);
		gotoxy(34, 12);
		std::cout << std::setw(85 - 33) << std::setfill(' ') << "";
		boxnho(34, 85, 8, 13);
		do {
			gotoxy(36, 11); std::cout << "Name: ";
			if (Name[0] != '\0') {
				std::cout << std::setw(40) << std::setfill(' ') << "";
				if (strlen(Name) > 40)
					std::cout << std::setw(strlen(Name) - 40)
					<< std::setfill(' ') << "";
			}
			showCur(1);
			block_char(Name, 80, 42, 11);
			if (Name[0] == '.') {
				PaMSearchInterface(PL, v, 0);
				return;
			}
			gotoxy(88, 4);
			std::cout << std::setw(30) << std::setfill(' ') << "";
			gotoxy(88, 5);
			std::cout << std::setw(30) << std::setfill(' ') << "";
			showCur(0);
			char c[100];
			strcpy(c, Name);
			token = std::strtok(c, " ");
			if (strlen(Name) == 0 || strlen(token) == strlen(Name) 
				|| strlen(token) + 1 == strlen(Name)) {
				gotoxy(88, 4);
				std::cout << "Invalid Name!!!";
				gotoxy(88, 5);
				std::cout << "Please input again!";
				continue;
			}
			lName.assign(token);
			token = strtok(NULL, "");
			fName.assign(token);
			break;
			Sleep(400);
		} while (1); 
		gotoxy(34, 13);
		std::cout << std::setw(85 - 33) << std::setfill(' ') << "";
		boxnho(34, 85, 8, 14);
		gotoxy(36, 12); std::cout << "Sex: ";
		SexBox();
		int inpt = 0;
		do {
			inputChar = _getch();
			if (inputChar == 27) {
				system("cls");
				PaMSearchInterface(PL, v, 0);
				return;
			}
			if (inputChar == 13)
				break;
			if (inputChar == 72)
				if (inpt == 1) {
					gotoxy(52, 14 + inpt); std::cout << "   ";
					inpt--;
					gotoxy(52, 14 + inpt); std::cout << "==>";
				}
				else {
					gotoxy(52, 14 + inpt); std::cout << "   ";
					inpt = 1;
					gotoxy(52, 14 + inpt); std::cout << "==>";
				}
			if (inputChar == 80)
				if (inpt == 0) {
					gotoxy(52, 14 + inpt); std::cout << "   ";
					inpt++;
					gotoxy(52, 14 + inpt); std::cout << "==>";
				}
				else {
					gotoxy(52, 14 + inpt); std::cout << "   ";
					inpt = 0;
					gotoxy(52, 14 + inpt); std::cout << "==>";
				}
		} while (1);
		switch (inpt) {
		case 0: {
			sex = MALE;
			break;
		}
		case 1: {
			sex = FEMALE;
			break;
		}
		}
		PL->insertPassenger(ssid, lName, fName, sex);
		PL->writeFile(); Sleep(400);
		system("cls");
		gotoxy(55, 13);
		std::cout << "Adding Flight";
		Sleep(400);
		std::cout << ".";
		Sleep(400);
		std::cout << ".";
		Sleep(400);
		std::cout << ".";
		break;
	} while (1);
	delete[] ssid, Name, token;
	PaMSearchInterface(PL, v, 0);
	return;
}

void PaMSearchInterface(PassengerList* PL, vector<Passenger*>& v, 
	int function) {
	showCur(1);
	char* input = new char[13]; 
	begin:
	PL->PaMPrintPassengerInforMainInterface(0, v);
	do {
		PL->block_char_search_PaM(input, 12, 40, 3, v, function);
	} while (strlen(input) == 0);
	if (input[0] == '?')
		goto begin;
	if (input[0] == '.')
		return;
	delete[] input;
}

void PaMDeleteInterface(PassengerList* PL, const string& ssid) {
	system("cls");
	menuCurTime();
	PMDeleteBox();
	char inputChar;
	int inpt = 0;
	do {
		inputChar = _getch();
		if (inputChar == 72)
			if (inpt == 1) {
				gotoxy(56, 12 + inpt); std::cout << "   ";
				inpt--;
				gotoxy(56, 12 + inpt); std::cout << "==>";
			}
			else {
				gotoxy(56, 12 + inpt); std::cout << "   ";
				inpt = 1;
				gotoxy(56, 12 + inpt); std::cout << "==>";
			}
		if (inputChar == 80)
			if (inpt == 0) {
				gotoxy(56, 12 + inpt); std::cout << "   ";
				inpt++;
				gotoxy(56, 12 + inpt); std::cout << "==>";
			}
			else {
				gotoxy(56, 12 + inpt); std::cout << "   ";
				inpt = 0;
				gotoxy(56, 12 + inpt); std::cout << "==>";
			}
		if (inputChar == 27) {
			system("cls");
			return;
		}
		if (inputChar == 13)
			break;
	} while (1);
	switch (inpt) {
	case 0: {
		PL->deletePassenger(ssid);
		PL->writeFile();
		system("cls");
		gotoxy(55, 13);
		std::cout << "Deleting";
		Sleep(400);
		std::cout << ".";
		Sleep(400);
		std::cout << ".";
		Sleep(400);
		std::cout << ".";
		Sleep(400);
		break;
	}
	case 1: {
		break;
	}
	}
}

// PassengerList class definition
PassengerList::PassengerList() {
	root = nullptr;
	pCount = 0;
}

PassengerList::~PassengerList() {
	clear();
}

void PassengerList::clear() {
	postOrderDeleteTree(root);
	pCount = 0;
}

void PassengerList::postOrderDeleteTree(Passenger* subroot) {
	if (subroot != nullptr) {
		postOrderDeleteTree(subroot->left);
		postOrderDeleteTree(subroot->right);
		delete subroot;
		subroot = nullptr;
	}
}

bool PassengerList::insertPassenger(const string& ssid, const string& lastname,
	const string& firstname, const SEX& sex) {
	Passenger* newpassenger = new Passenger(ssid, lastname, firstname, sex);
	bool check = true;
	root = recursiveInsert(root, newpassenger, check);
	if (check == true)
		pCount++;
	return check;
}

Passenger* PassengerList::recursiveInsert(Passenger* subroot, Passenger* newpassenger,
	bool& check) {
	if (subroot == nullptr) {
		subroot = newpassenger;
		return subroot;
	}
	if (newpassenger->sSID.compare(subroot->sSID) < 0)
		subroot->left = recursiveInsert(subroot->left, newpassenger, check);
	else if (newpassenger->sSID.compare(subroot->sSID) > 0)
		subroot->right = recursiveInsert(subroot->right, newpassenger, check);
	else {
		check = false;
		return subroot;
	}
	int bf = getBalanceFactor(subroot);
	if (bf > 1 && newpassenger->sSID.compare(subroot->left->sSID) < 0)
		return rotateRight(subroot);
	if (bf < -1 && newpassenger->sSID.compare(subroot->right->sSID) > 0)
		return rotateLeft(subroot);
	if (bf > 1 && newpassenger->sSID.compare(subroot->left->sSID) > 0) {
		subroot->left = rotateLeft(subroot->left);
		return rotateRight(subroot);
	}
	if (bf < -1 && newpassenger->sSID.compare(subroot->right->sSID) < 0) {
		subroot->right = rotateRight(subroot->right);
		return rotateLeft(subroot);
	}
	return subroot;
}

Passenger* PassengerList::rotateLeft(Passenger* subroot) {
	Passenger* righttree = subroot->right;
	subroot->right = righttree->left;
	righttree->left = subroot;
	return righttree;
}

Passenger* PassengerList::rotateRight(Passenger* subroot) {
	Passenger* lefttree = subroot->left;
	subroot->left = lefttree->right;
	lefttree->right = subroot;
	return lefttree;
}

void PassengerList::deletePassenger(const string& ssid) {
	root = recursiveDelete(root, ssid);
	pCount--;
}

Passenger* PassengerList::recursiveDelete(Passenger* subroot, const string& ssid) {
	if (subroot == nullptr)
		return subroot;
	if (ssid.compare(subroot->sSID) < 0)
		subroot->left = recursiveDelete(subroot->left, ssid);
	else if (ssid.compare(subroot->sSID) > 0)
		subroot->right = recursiveDelete(subroot->right, ssid);
	else {
		if (subroot->left == nullptr) {
			Passenger* temp = subroot->right;
			delete subroot;
			subroot = temp;
		}
		else if (subroot->right == nullptr) {
			Passenger* temp = subroot->left;
			delete subroot;
			subroot = temp;
		}
		else {
			Passenger* temp = minValuePassenger(subroot->right);
			copyPassengerData(subroot, temp);
			recursiveDelete(subroot->right, temp->sSID);
		}
	}
	int bf = getBalanceFactor(subroot);
	if (bf == 2 && getBalanceFactor(subroot->left) >= 0)
		return rotateRight(subroot);
	else if (bf == 2 && getBalanceFactor(subroot->left) == -1) {
		subroot->left = rotateLeft(subroot->left);
		return rotateRight(subroot);
	}
	else if (bf == -2 && getBalanceFactor(subroot->right) <= 0)
		return rotateLeft(subroot);
	else if (bf == -2 && getBalanceFactor(subroot->right) == 1) {
		subroot->right = rotateRight(subroot->right);
		return rotateLeft(subroot);
	}
	return subroot;
}

Passenger* PassengerList::minValuePassenger(Passenger* parent) {
	Passenger* p = parent;
	while (p->left != nullptr)
		p = p->left;
	return p;
}

int PassengerList::height(Passenger* subroot) {
	if (subroot == nullptr)
		return -1;
	int lHeight = height(subroot->left);
	int rHeight = height(subroot->right);
	return ((lHeight > rHeight) ? lHeight + 1 : rHeight + 1);
}

int PassengerList::getBalanceFactor(Passenger* subroot) {
	if (subroot == nullptr)
		return -1;
	return (height(subroot->left) - height(subroot->right));
}

void PassengerList::copyPassengerData(Passenger* lhs, Passenger* rhs) {
	lhs->sSID = rhs->sSID;
	lhs->firstName = rhs->firstName;
	lhs->lastName = rhs->lastName;
	lhs->sex = rhs->sex;
}

const Passenger* PassengerList::searchPassenger(const string& ssid) const {
	Passenger* pSearch = root;
	while (pSearch != nullptr &&
		pSearch->sSID.compare(ssid) != 0) {
		if (ssid.compare(pSearch->sSID) < 0)
			pSearch = pSearch->left;
		else
			pSearch = pSearch->right;
	}
	return pSearch;
}

void PassengerList::addPassengerToVector(vector<Passenger*>& v) const {
	inOrderDFT(root, v);
}

void PassengerList::inOrderDFT(Passenger* subroot, vector<Passenger*>& v) const {
	if (subroot != nullptr) {
		inOrderDFT(subroot->left, v);
		v.push_back(subroot);
		inOrderDFT(subroot->right, v);
	}
}

int PassengerList::getTotalPassenger() const {
	return pCount;
}

char* PassengerList::getSSID(const Passenger* passenger) const {
	char b[100];
	strcpy(b, passenger->sSID.c_str());
	return b;
}

void PassengerList::PaMPrintPassengerInforMainInterface(int j, vector<Passenger*>& v) const {
	v.clear();
	inOrderDFT(this->root, v);
	system("cls");
	menuCurTime();
	PaMSearchBox();
	char* input = new char[100];
	gotoxy(103, 28); std::cout << j + 1 << "/" << (v.size() / 19) + 1;
	for (int i = 19 * j; (i < v.size() && i < 19 * (j + 1)) || (i == 0 && v.size() == 1); i++) {
		gotoxy(7, 7 + i % 19); std::cout << i + 1;
		gotoxy(23, 7 + i % 19); std::cout << v[i]->sSID;
		gotoxy(66, 7 + i % 19); std::cout << v[i]->lastName;
		gotoxy(66 + v[i]->lastName.length() + 1, 7 + i % 19);
		std::cout << v[i]->firstName;
		gotoxy(108, 7 + i % 19);
		switch (v[i]->sex) {
		case 0: {
			std::cout << "NO-INFOR";
			break;
		}
		case 1: {
			std::cout << "  MALE";
			break;
		}
		case 2: {
			std::cout << " FEMALE";
			break;
		}
		}
	}
	delete[] input;
}

void PassengerList::PaMPrintPassengerInforSearchInterface(char* c,
	int& _count, vector<Passenger*>& passenger, vector<Passenger*>& pos) {
	if (c[0] == '\0') {
		_count = -1;
		return;
	}
	for (int i = 0; i < 19; i++) {
		gotoxy(7, 7 + i); std::cout << std::setw(3) << std::setfill(' ') << "";
		gotoxy(23, 7 + i); std::cout << std::setw(12) << std::setfill(' ') << "";
		gotoxy(66, 7 + i); std::cout << std::setw(35) << std::setfill(' ') << "";
		gotoxy(108, 7 + i); std::cout << std::setw(9) << std::setfill(' ') << "";
	}
	int count = 0, j = 0;
	pos.clear();
	char* input = new char[100];
	for (int i = 0; i < pCount; i++) {
		string str = passenger[i]->sSID;
		int found = str.find(c);
		if (found != string::npos) {
			if (count < 19) {
				gotoxy(7, 7 + count); std::cout << count + 1;
				gotoxy(23, 7 + count); std::cout << passenger[i]->sSID;
				gotoxy(66, 7 + count); 
				std::cout << passenger[i]->lastName << " "
					<< passenger[i]->firstName;
				gotoxy(108, 7 + count);
				switch (passenger[i]->sex) {
				case 0: {
					std::cout << "NO-INFOR";
					break;
				}
				case 1: {
					std::cout << "  MALE";
					break;
				}
				case 2: {
					std::cout << " FEMALE";
					break;
				}
				}
			}
			pos.push_back(passenger[i]);
			count++;
		}
	}
	_count = count;
	gotoxy(103, 28); std::cout << 1 << "/" << count / 19 + 1;
	delete[] input;
}

void PassengerList::PaMPrintPassengerInforSearchInterface(const char* c,
	int _count, const vector<Passenger*>& passenger, int page) const {
	for (int i = 0; i < 18; i++) {
		gotoxy(7, 7 + i); std::cout << std::setw(3) << std::setfill(' ') << "";
		gotoxy(23, 7 + i); std::cout << std::setw(12) << std::setfill(' ') << "";
		gotoxy(66, 7 + i); std::cout << std::setw(35) << std::setfill(' ') << "";
		gotoxy(108, 7 + i); std::cout << std::setw(9) << std::setfill(' ') << "";
	}
	int j = 0;
	if (c[0] == '.' && _count == pCount) {
		vector<Passenger*> v;
		PaMPrintPassengerInforMainInterface(0, v);
		return;
	}
	char* input = new char[100];
	for (int i = 0; i < _count; i++) {
		if (i >= 19 * page && i < 19 * (page + 1)) {
			gotoxy(7, 7 + i % 19); std::cout << i + 1;
			gotoxy(23, 7 + i % 19); std::cout << passenger[i]->sSID;
			std::cout << passenger[i]->lastName << " "
				<< passenger[i]->firstName;
			gotoxy(108, 7 + i % 19);
			switch (passenger[i]->sex) {
			case 0: {
				std::cout << "NO-INFOR";
				break;
			}
			case 1: {
				std::cout << "  MALE";
				break;
			}
			case 2: {
				std::cout << " FEMALE";
				break;
			}
			}
		}
	}
	gotoxy(103, 28); std::cout << page + 1 << "/" << _count / 19 + 1;
	delete[] input;
}

void PassengerList::block_char_search_PaM(char* b, int a, int x, int y,
	vector<Passenger*>& passenger, int function) {
	passenger.clear();
	addPassengerToVector(passenger);
	vector<Passenger*> pos;
	//showCur(0);
editI:
	b[0] = '\0';
	int i = 0;
	char inputChar;
	int count1 = 0;
search:
	gotoxy(x, y);
	while (1)
	{
		inputChar = _getch();
		if (i < 12 && inputChar >= 48 && inputChar <= 57) {
			gotoxy(x + i, y);
			b[i] = inputChar;
			std::cout << inputChar;
			i++;
			b[i] = '\0';
			PaMPrintPassengerInforSearchInterface(b, count1, passenger, pos);
			gotoxy(x + i, y);
		}
		if (inputChar == 8 && i > 0) {
			gotoxy(x + i - 1, y);
			std::cout << " ";
			gotoxy(x + i - 1, y);
			i--;
			b[i] = '\0';
			PaMPrintPassengerInforSearchInterface(b, count1, passenger, pos);
			gotoxy(x + i, y);
		}
		if (inputChar == 8 && i == 0) {
			PaMPrintPassengerInforMainInterface(0, pos);
			showCur(1);
			gotoxy(x, y);
			//system("pause");
		}
		if (inputChar == 27) {
			b[0] = '.';
			b[1] = '\0';
			return;
		}
		if (inputChar == 13) {
			if (b[0] == '\0')
				count1 = -1;
			if (count1 == 0)
				continue;
			if (count1 == -1) {
				count1 = getTotalPassenger();
				pos = passenger;
			}
			showCur(0);
			b[0] = '.';
			b[1] = '\0';
			int page = 0;
			int count = count1 / 19;
			int count2 = 0;
		choose:
			gotoxy(2, 7);
			std::cout << "==>";
			int key = 0;
			char inputChar;
			do {
				inputChar = _getch();
				if (inputChar == 72) {
					if (key > 0) {
						gotoxy(2, 7 + key); std::cout << "   ";
						key--;
						count2--;
					}
					else if (key == 0) {
						if (page > 0 && page <= count) {
							gotoxy(2, 7); std::cout << "   ";
							page--;
							PaMPrintPassengerInforSearchInterface(b, count1, pos, page);
							gotoxy(x + i, y);
							key = 18;
							count2--;
						}
					}
				}
				else if (inputChar == 80) {
					if (key < 18 && key < count1 - 1 && count2 < count1 - 1) {
						//if (key)
						gotoxy(2, 7 + key); std::cout << "   ";
						key++;
						count2++;
					}
					else if (key == 18) {
						if (page < count) {
							gotoxy(2, 25); std::cout << "   ";
							page++;
							count2++;
							PaMPrintPassengerInforSearchInterface(b, count1, pos, page);
							gotoxy(x + i, y);
							goto choose;
						}
					}
				}
				if (inputChar == 13 && function != 0) {
					PaMDeleteInterface(getInstance(), pos[count2]->sSID);
					b[0] = '?';
					b[1] = '\0';
					return;
				}
				gotoxy(2, 7 + key);
				cout << "==>";
			} while (inputChar != 27);
			b[0] = '.';
			b[1] = '\0';
			return;
		}
	}
}

// Passengers class definition
Passenger::Passenger(string ssid, string ln, string fn, SEX sex)
	: sSID(ssid), lastName(ln), firstName(fn), sex(sex) {
	left = right = nullptr;
	BF = 0;
}