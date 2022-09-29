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

//void FMMainInterface(FlightList* FL) {
//	int page = 0;
//	char inputChar;
//	do {
//	FMStartingPage:
//		showCur(0);
//		system("cls");
//		//AC->PMPrintPlaneTypeInforMainInterface(page);
//		menuCurTime();
//		PMMainBox();
//		inputChar = _getch();
//		if (inputChar == 59)
//			//PMAddInterface(AC);
//			if (inputChar == 61)
//				//PMEditInterface(AC);
//				if (inputChar == 83) {
//					//PMDeleteInterface(AC);
//				}
//		if (inputChar == 80 && AC->getTotalAC() / 19 * (page + 1) > 0 && page < AC->getTotalAC() / 19) {
//			page++;
//		}
//		if (inputChar == 72 && page > 0)
//			page--;
//	} while (inputChar != 27);
//	AC->writeAirCraftFile();
//}

FlightList::FlightList() {
	root = nullptr;
	fCount = 0;
}

FlightList::~FlightList() {

}

void FlightList::insertFlight() {
	if (this->root == nullptr)
		flightlist->root = nullptr;

}

void FlightList::clear() {
	
}
//00:00-01/01/2022
Flight::Time* FlightList::timeParse(const string& exactdaytime) {
	Flight::Time* time = new Flight::Time();
	char c[100];
	std::strcpy(c, exactdaytime.c_str());
	time->_hour = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_minute = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_day = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_month = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_year = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	return time;
}

FLIGHT::TIME::Time(int hour, int minute, int day, int month, int year)
	: _hour(hour), _minute(minute), _day(day), _month(month), _year(year)
{}

Flight::Flight(string acnumber, string flightcode, string airport, string exactdaytime, 
	FlightStatus flightstatus, int numberofflight) 
	: ACNumber(acnumber), FlightCode(flightcode), AirPort(airport),
	Flight_Status(flightstatus), NumberOfFlight(numberofflight) {
	time = new Time();
	char c[100];
	std::strcpy(c, exactdaytime.c_str());
	time->_hour = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_minute = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_day = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_month = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	time->_year = atoi(strtok(c, " :-/"));
	strtok(NULL, " :-/");
	ticketList = new Ticket();
	left = right = nullptr;
	BF = equal_height;
}