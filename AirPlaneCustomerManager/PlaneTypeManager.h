#pragma once
#include "Time.h"
#include "Box.h"
#include "MyLib.h"
#include "DataTypes.h"
#include <iomanip>
#include <string.h>
#include <conio.h>
#include "ReadAndWriteFiles.h"

void PMAddInterface(airCraftList*);
void PMEditInterface(airCraftList*);
void PMDeleteInterface(airCraftList*);
void PMSearchInterface(airCraftList*);
void block_char(char* b, int a, int x, int y);

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
	char inputChar = ' ';
	do {
		block_char(planeType, 100, 53, 10);
	} while (strlen(planeType) == 0);
	if (planeType[0] == '.')
		PMSearchInterface(AC);
	do {
		gotoxy(54, 11);
		std::cout << std::setw(31) << std::setfill(' ') << "";
		block_char(planeNumber, 100, 54, 11);
		if (planeNumber[0] == '.')
			PMSearchInterface(AC);
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
		if (totalSeats[0] == '.')
			PMSearchInterface(AC);
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

void PMSearchInterface(airCraftList* AC) {
	showCur(1);
	system("cls");
	menuCurTime();
	PMMainBox();
	AC->PMPrintPlaneTypeInforMainInterface(1);
	/*do {

	} while ();*/
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
		gotoxy(9, 7 + i % 19); std::cout << i + 1;
		gotoxy(31, 7 + i % 19); std::cout << ACList[i]->ACType;
		gotoxy(77, 7 + i % 19); std::cout << ACList[i]->ACNumber;
		gotoxy(108, 7 + i % 19); std::cout << ACList[i]->TotalSeats;
	}
}