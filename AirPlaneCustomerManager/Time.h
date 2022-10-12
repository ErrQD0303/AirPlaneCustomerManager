#pragma once
#include <iostream>
#include <ctime>
#include "MyLib.h"
using namespace std;

void curTime(int& year, int& month, 
	int& day, int& hour, int& min) {
	time_t CurTime = time(0);
	tm* ct = new tm;
	localtime_s(ct, &CurTime);
	year = 1900 + ct->tm_year;
	month = 1 + ct->tm_mon;
	day = ct->tm_mday;
	hour = ct->tm_hour;
	min = ct->tm_min;
}

void menuCurTime() {
	int year, month, day, hour, min;
	curTime(year, month, day, hour, min);
	if (hour >= 10) {
		gotoxy(85, 0); cout << hour;
	}
	else {
		gotoxy(85, 0); cout << "0" << hour;
	}
	gotoxy(87, 0);
	if (min < 10)
		cout << ":0" << min;
	else
		cout << ":" << min;
	gotoxy(91, 0);
	if (day < 10) {
		std::cout << '0' << day;
	}
	else
		std::cout << day;
	gotoxy(93, 0);
	if (month < 10) {
		std::cout << "/0" << month;
	}
	else
		std::cout << "/" << month;
	gotoxy(96, 0); cout << "/" << year;
	cout << " GMT+7";
}
