#pragma once
#include "Time.h"
#include "Box.h"
#include "MyLib.h"
#include "DataTypes.h"
#include <iomanip>
#include <string>
#include <conio.h>

void PMPrintPlaneTypeInfor();
void PMAddInterface();
void PMEditInterface();
void PMDeleteInterface();

void PMMainInterface() {
	char inputChar;
	do {
	PMStartingPage:
		showCur(0);
		system("cls");
		menuCurTime();
		PMPrintPlaneTypeInfor();
		PMMainBox();
		inputChar = _getch();
		if (inputChar == 59)
			PMAddInterface();
		if (inputChar == 61)
			PMEditInterface();
		if (inputChar == 127)
			PMDeleteInterface();
	} while (inputChar != 27);
}

void PMPrintPlaneTypeInfor() {

}

void PMAddInterface() {
	showCur(1);
	system("cls");
	PMSearchBox();
	flushConsoleInputBuffer();
	string inputStr;
	_getline
	do {
	} while (inputStr != " ");
}

void PMEditInterface() {
	showCur(1);
	system("cls");
}

void PMDeleteInterface() {
	system("cls");
}