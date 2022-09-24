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

void PMAddInterface(airCraftList*);
void PMEditInterface(airCraftList*);
void PMDeleteInterface(airCraftList*);
void PMSearchInterface(airCraftList*);
void block_char(char* b, int a, int x, int y);
void block_char_search(char* b, int a, int x, int y, airCraftList* AC);

void PMMainInterface(airCraftList* AC) {
	int page = 0;
	char inputChar;
	do {
	PMStartingPage:
		showCur(0);
		system("cls");
		AC->PMPrintPlaneTypeInforMainInterface(page);
		menuCurTime();
		PMMainBox();
		inputChar = _getch();
		if (inputChar == 59)
			PMAddInterface(AC);
		if (inputChar == 61)
			PMEditInterface(AC);
		if (inputChar == 127)
			PMDeleteInterface(AC);
		if (inputChar == 80 && AC->getTotalAC() / 19 * (page + 1) > 0 && page < AC->getTotalAC() / 19) {
			page++;
		}
		if (inputChar == 72 && page > 0)
			page--;
	} while (inputChar != 27);
	AC->writeAirCraftFile();
}

void PMAddInterface(airCraftList* AC) {
	showCur(1);
	system("cls");
	menuCurTime();
	PMAddBox();
	flushConsoleInputBuffer();
	int i = 0;
	char* planeNumber = new char[100];
	char* planeType = new char[100];
	char* totalSeats = new char[100];
	do {
		block_char(planeType, 100, 53, 10);
	} while (strlen(planeType) == 0);
	if (planeType[0] == '.') {
		PMSearchInterface(AC);
		return;
	}
	do {
		gotoxy(54, 11);
		std::cout << std::setw(31) << std::setfill(' ') << "";
		block_char(planeNumber, 100, 54, 11);
		if (planeNumber[0] == '.') {
			PMSearchInterface(AC);
			return;
		}
		gotoxy(88, 5);
		std::cout << std::setw(30) << std::setfill(' ') << "";
		if (strlen(planeNumber) > 6 || strlen(planeNumber) < 6) {
			gotoxy(88, 5);
			std::cout << "Plane Number has 6 characters";
		}
	} while (strlen(planeNumber) > 6 || strlen(planeNumber) < 6);
	do {
		gotoxy(59, 12);
		std::cout << std::setw(25) << std::setfill(' ') << "";
		gotoxy(59, 12);
		block_char(totalSeats, 100, 59, 12);
		if (totalSeats[0] == '.') {
			PMSearchInterface(AC);
			return;
		}
		gotoxy(88, 5);
		std::cout << std::setw(19) << std::setfill(' ') << "";
		if (atoi(totalSeats) <= 0 || atoi(totalSeats) > 200) {
			gotoxy(88, 5);
			std::cout << "ToTal Seats <= 200";
		}
	} while (atoi(totalSeats) <= 0 || atoi(totalSeats) > 200);
	AC->insertAirCraft(planeType, planeNumber, atoi(totalSeats));
	/*char* b = AC->getACNumber("Boeing");
	gotoxy(10, 1);
	std::cout << b;
	system("pause");*/
	delete[] totalSeats;
}

void PMEditInterface(airCraftList* AC) {
	showCur(1);
	system("cls");
	menuCurTime();
}

void PMDeleteInterface(airCraftList* AC) {
	system("cls");
	menuCurTime();
}
//

void PMSearchInterface(airCraftList* AC) {
	int page = 0;
	showCur(1);
	AC->PMPrintPlaneTypeInforSearchInterface(page);
	char* planeType = new char[100];
	do {
		block_char_search(planeType, 100, 41, 3, AC);
	} while (strlen(planeType) == 0);
	if (planeType[0] == '.')
		return;
	delete[] planeType;
}

airCraftList::airCraftList() {
	TotalAC = 0;
}

airCraftList::~airCraftList() {
	for (int i = 0; i < TotalAC; i++) {
		delete[] ACList[i]->ACNumber, ACList[i]->ACType;
		//delete ACList[i];
	}
}

int airCraftList::insertAirCraft(char* acType,
	char* acNumber, int totalSeats) {
	for (int i = 0; i < TotalAC; i++)
		if (ACList[i]->ACNumber == acNumber)
			return 0;
	ACList[TotalAC] = new airCraft();
	for (int i = 0; i < strlen(acType); i++)
		ACList[TotalAC]->ACType[i] = acType[i];
	for (int i = 0; i < strlen(acNumber); i++)
		ACList[TotalAC]->ACNumber[i] = acNumber[i];
	ACList[TotalAC]->TotalSeats = totalSeats;
	TotalAC++;
	return 1;
}

void block_char(char* b, int a, int x, int y)
{
	b[0] = '\0';
	int i = 0;
	char inputChar;
	gotoxy(x, y);
	while (1)
	{
		inputChar = _getch();
		if (i <= a && inputChar >= 48 && inputChar <= 122 
			|| inputChar == 32) {
			gotoxy(x + i, y);
			b[i] = inputChar;
			std::cout << inputChar;
			i++;
		}
		if (inputChar == 8 && i > 0) {
			gotoxy(x + i - 1, y);
			std::cout << " ";
			gotoxy(x + i - 1, y);
			i--;
		}
		if (inputChar == 27) {
			b[0] = '.';
			b[1] = '\0';
			return;
		}
		if (inputChar == 13) {
			b[i] = '\0';
			return;
		}
	}
}

void block_char_search(char* b, int a, int x, int y, airCraftList* AC) {
	//showCur(0);
	b[0] = '\0';
	int i = 0;
	char inputChar;
	int count1 = 0;
	vector<int> pos;
	search:
	gotoxy(x, y);
	while (1)
	{
		inputChar = _getch();
		if (i < 6 && inputChar >= 48 && inputChar <= 122
			|| inputChar == 32) {
			gotoxy(x + i, y);
			b[i] = inputChar;
			std::cout << inputChar;
			i++;
			b[i] = '\0';
			AC->PMPrintPlaneTypeInforSearchInterface(b, count1, pos);
			gotoxy(x + i, y);
		}
		if (inputChar == 8 && i > 0) {
			gotoxy(x + i - 1, y);
			std::cout << " ";
			gotoxy(x + i - 1, y);
			i--;
			b[i] = '\0';
			AC->PMPrintPlaneTypeInforSearchInterface(b, count1, pos);
			gotoxy(x + i, y);
		}
		if (inputChar == 8 && i == 0) {
			AC->PMPrintPlaneTypeInforSearchInterface(0);
			showCur(1);
			gotoxy(41, 3);
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
			if (count1 == -1)
				count1 = AC->getTotalAC();
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
							AC->PMPrintPlaneTypeInforSearchInterface(b, count1, pos, page);
							key = 18;
							count2--;
						}
					}
				}
				else if (inputChar == 80) {  // fix position 24/9
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
							AC->PMPrintPlaneTypeInforSearchInterface(b, count1, pos, page);
							goto choose;
						}
					}
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

char* airCraftList::getACNumber(const char* acType) const {
	for (int i = 0; i < TotalAC; i++) {
		if (strcmp(acType,ACList[i]->ACType) == 0)
			return ACList[i]->ACNumber;
	}
	char* b = new char[2];
	b[0] = '.';
	b[1] = '\0';
	return b;
}

char* airCraftList::getACType(const char* acType) const {
	for (int i = 0; i < TotalAC; i++) {
		if (strcmp(acType, ACList[i]->ACType) == 0)
			return ACList[i]->ACType;
	}
	char* b = new char[2];
	b[0] = '.';
	b[1] = '\0';
	return b;
}

int airCraftList::getTotalSeats(const char* acType) const {
	for (int i = 0; i < TotalAC; i++) {
		if (strcmp(acType, ACList[i]->ACType) == 0)
			return ACList[i]->TotalSeats;
	}
	return 0;
}

int airCraftList::getTotalAC() const {
	return TotalAC;
}

void airCraftList::PMPrintPlaneTypeInforMainInterface(int j) const {
	system("cls");
	PMMainBox();
	gotoxy(103, 28); std::cout << j + 1 << "/" << (TotalAC / 19) + 1;
	for (int i = 19 * j; (i < TotalAC && i < 19 * (j + 1)) || (i == 0 && TotalAC == 1); i++) {
		gotoxy(8, 7 + i % 19); std::cout << i + 1;
		gotoxy(31, 7 + i % 19); std::cout << ACList[i]->ACType;
		gotoxy(77, 7 + i % 19); std::cout << ACList[i]->ACNumber;
		gotoxy(107, 7 + i % 19); std::cout << ACList[i]->TotalSeats;
	}
}

void airCraftList::PMPrintPlaneTypeInforSearchInterface(int j) const {
	system("cls");
	menuCurTime();
	PMSearchBox();
	gotoxy(103, 28); std::cout << j + 1 << "/" << (TotalAC / 19) + 1;
	for (int i = 19 * j; (i < TotalAC && i < 19 * (j + 1)) || (i == 0 && TotalAC == 1); i++) {
		gotoxy(8, 7 + i % 19); std::cout << i + 1;
		gotoxy(31, 7 + i % 19); std::cout << ACList[i]->ACType;
		gotoxy(77, 7 + i % 19); std::cout << ACList[i]->ACNumber;
		gotoxy(107, 7 + i % 19); std::cout << ACList[i]->TotalSeats;
	}
}

void airCraftList::PMPrintPlaneTypeInforSearchInterface(char* c) const {
	for (int i = 0; i < 19; i++) {
		gotoxy(8, 7 + i); std::cout << std::setw(4) << std::setfill(' ') << " ";
		gotoxy(31, 7 + i); std::cout << std::setw(30) << std::setfill(' ') << " ";
		gotoxy(77, 7 + i); std::cout << std::setw(6) << std::setfill(' ') << " ";
		gotoxy(107, 7 + i); std::cout << std::setw(11) << std::setfill(' ') << " ";
	}
	int j = 0, count = 0;
	for (int i = 0; i < TotalAC && count < 19; i++) {
		string str = ACList[i]->ACNumber;
		int found = str.find(c);
		if (found != string::npos) {
			gotoxy(8, 7 + count); std::cout << count + 1;
			gotoxy(31, 7 + count); std::cout << ACList[i]->ACType;
			gotoxy(77, 7 + count); std::cout << ACList[i]->ACNumber;
			gotoxy(107, 7 + count); std::cout << ACList[i]->TotalSeats;
			count++;
		}
	}
	gotoxy(105, 28); std::cout << count / 19 + 1;
}

void airCraftList::PMPrintPlaneTypeInforSearchInterface(char* c, int& _count, vector<int>& pos) const { //fix position 24/9
	if (c[0] == '\0') {
		_count = -1;
		return;
	}
	for (int i = 0; i < 19; i++) {
		gotoxy(8, 7 + i); std::cout << std::setw(4) << std::setfill(' ') << " ";
		gotoxy(31, 7 + i); std::cout << std::setw(30) << std::setfill(' ') << " ";
		gotoxy(77, 7 + i); std::cout << std::setw(6) << std::setfill(' ') << " ";
		gotoxy(107, 7 + i); std::cout << std::setw(11) << std::setfill(' ') << " ";
	}
	int j = 0, count = 0;
	pos.clear();
	for (int i = 0; i < TotalAC; i++) {
		string str = ACList[i]->ACNumber;
		int found = str.find(c);
		if (found != string::npos) {
			if (count < 19) {
				gotoxy(8, 7 + count); std::cout << count + 1;
				gotoxy(31, 7 + count); std::cout << ACList[i]->ACType;
				gotoxy(77, 7 + count); std::cout << ACList[i]->ACNumber;
				gotoxy(107, 7 + count); std::cout << ACList[i]->TotalSeats;
			}
			pos.push_back(i);
			count++;
		}
	}
	_count = count;
	gotoxy(105, 28); std::cout << count / 19 + 1;
}

void airCraftList::PMPrintPlaneTypeInforSearchInterface(char* c, int _count, vector<int> pos, int page) const {
	for (int i = 0; i < 19; i++) {
		gotoxy(8, 7 + i); std::cout << std::setw(4) << std::setfill(' ') << " ";
		gotoxy(31, 7 + i); std::cout << std::setw(30) << std::setfill(' ') << " ";
		gotoxy(77, 7 + i); std::cout << std::setw(6) << std::setfill(' ') << " ";
		gotoxy(107, 7 + i); std::cout << std::setw(11) << std::setfill(' ') << " ";
	}
	int count = 0, j = 0; 
	if (c[0] == '.' && _count == TotalAC) {
		PMPrintPlaneTypeInforSearchInterface(page);
		return;
	}
	for (int i : pos) {
		if (count >= 19 * page && count < 19 * (page + 1)) {
			gotoxy(8, 7 + count % 19); std::cout << count + 1;
			gotoxy(31, 7 + count % 19); std::cout << ACList[i]->ACType;
			gotoxy(77, 7 + count % 19); std::cout << ACList[i]->ACNumber;
			gotoxy(107, 7 + count % 19); std::cout << ACList[i]->TotalSeats;
		}
		count++;
	}
	gotoxy(103, 28); std::cout << page + 1 << "/" << _count / 19 + 1;
}
//