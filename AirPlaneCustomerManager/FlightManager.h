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

bool FlightList::insertFlight(const string& flightcode, const string& acnumber, 
	const string& airport, const string& time, const FlightStatus& flightstatus, 
	Flight::Ticket* ticket) {
	bool taller;
	return recursiveInsert(root, flightcode, acnumber, airport, time, 
		flightstatus, ticket, taller);
}

bool FlightList::recursiveInsert(Flight* subroot, const string& flightcode,
	const string& acnumber, const string& airport, const string& time,
	const FlightStatus& flightstatus, Flight::Ticket* ticket, bool& taller) {
	bool result = true;
	if (subroot == nullptr) {
		subroot = new Flight();
		subroot->FlightCode = flightcode;
		subroot->ACNumber = acnumber;
		subroot->AirPort = airport;
		subroot->time = timeParse(time);
		subroot->Flight_Status = flightstatus;
		subroot->ticketList = ticket;
		taller = true;
		subroot->height = 1;
	}
	else if (subroot->FlightCode.compare(flightcode) == 0) {
		result = 0;
		taller = false;
	}
	else if (subroot->FlightCode.compare(flightcode) < 0) {
			result = recursiveInsert(subroot->left, flightcode, acnumber, airport, time,
				flightstatus, ticket, taller);
			if (taller == true)
				if (subroot->BF == -1) {
					leftBalance(subroot);
					taller = false;
				}
				else if (subroot->BF == 0) {
					subroot->BF = -1;
				}
				else if (subroot->BF == 1) {
					subroot->BF = 0;
					taller = false;
				}
	}
	else {
		result = recursiveInsert(subroot->right, flightcode, acnumber, airport, time,
			flightstatus, ticket, taller);
		if (taller == true)
			if (subroot->BF == -1) {
				subroot->BF = 0;
				taller = false;
			}
			else if (subroot->BF == 0) {
				subroot->BF = 1;
			}
			else if (subroot->BF == 1) {
				rightBalance(subroot);
				taller = false;
			}
	}
	subroot->height = 1 + (subroot->left->height > subroot->right->height 
		? subroot->left->height : subroot->right->height);
	return result;
}

void FlightList::rotateLeft(Flight* subroot) {
	Flight* rightTree = subroot->right;
	subroot->right = rightTree->left;
	rightTree->left = subroot;
	subroot = rightTree;
	subroot->left->height = 1 +
		(subroot->left->left->height > subroot->left->right->height
			? subroot->left->left->height : subroot->left->right->height);
	subroot->height = 1 + (subroot->left->height > subroot->right->height
		? subroot->left->height : subroot->right->height);
}

void FlightList::rotateRight(Flight* subroot) {
	Flight* leftTree = subroot->left;
	subroot->left = leftTree->right;
	leftTree->right = subroot;
	subroot = leftTree; 
	subroot->right->height = 1 +
		(subroot->right->left->height > subroot->right->right->height
			? subroot->right->left->height : subroot->right->right->height);
	subroot->height = 1 + (subroot->left->height > subroot->right->height
		? subroot->left->height : subroot->right->height);
}

void FlightList::rightBalance(Flight* subroot) {
	Flight* rightTree = subroot->right;
	if (rightTree->BF == 1) {
		subroot->BF = 0;
		rightTree->BF = 0;
		rotateLeft(subroot);
	}
	if (rightTree->BF == -1) {
		Flight* subtree = rightTree->left;
		subtree->BF = 0;
		rotateRight(rightTree);
		rotateLeft(subroot);
		if (subtree->BF == 0) {
			subroot->BF = 0;
			rightTree->BF = 0;
		}
		else if (subtree->BF == -1) {
			subroot->BF = 0;
			rightTree->BF = 1;
		}
		else {
			subroot->BF = -1;
			rightTree->BF = 0;
		}
	}
}

void FlightList::leftBalance(Flight* subroot) {
	Flight* leftTree = subroot->left;
	if (leftTree->BF == -1) {
		subroot->BF = 0;
		leftTree->BF = 0;
		rotateRight(subroot);
	}
	if (leftTree->BF == 1) {
		Flight* subtree = leftTree->right;
		subtree->BF = 0;
		rotateLeft(leftTree);
		rotateRight(subroot);
		if (subtree->BF == 0) {
			subroot->BF = 0;
			leftTree->BF = 0;
		}
		else if (subtree->BF == -1) {
			subroot->BF = 1;
			leftTree->BF = 0;
		}
		else {
			subroot->BF = 0;
			leftTree->BF = -1;
		}
	}
}

bool FlightList::deleteFlight(const string& flightcode) {
	return recursiveDelete(root, flightcode);
}

bool FlightList::recursiveDelete(Flight* subroot, const string& flightcode) {
	if (subroot == nullptr)
		return false;
	else if (flightcode < subroot->FlightCode)
		return recursiveDelete(subroot->left, flightcode);
	else if (flightcode > subroot->FlightCode)
		return recursiveDelete(subroot->right, flightcode);
	else {
		removeNode(subroot);
		return true;
	}
}

void FlightList::removeNode(Flight* subroot) {
	Flight* pDel = subroot;
	if (subroot->left == nullptr)
		subroot = subroot->right;
	else if (subroot->right == nullptr)
		subroot = subroot->left;
	else {
		Flight* parent = subroot;
		pDel = parent->left;
		while (pDel->right != nullptr) {
			parent = pDel;
			pDel = pDel->right;
		}
		copyFlightData(subroot, pDel);
		if (parent == subroot)
			parent->left = pDel->left;
		else
			parent->right = pDel->left;
		delete pDel;
		pDel = nullptr;
	}
}

void FlightList::copyFlightData(Flight* lhs, Flight* rhs) {
	lhs->FlightCode = rhs->FlightCode;
	lhs->ACNumber = rhs->ACNumber;
	lhs->AirPort = rhs->AirPort;
	lhs->BF = rhs->BF;
	lhs->Flight_Status = rhs->Flight_Status;
	lhs->height = rhs->height;
	lhs->ticketList = rhs->ticketList;
	lhs->time = rhs->time;
}

bool FlightList::operator!() const {
	return fCount == 0;
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

Flight::Ticket::Ticket(int totalticket, int ticketsold, int ticketleft) 
	: n(totalticket), ticketSold(ticketsold), ticketLeft(ticketleft)
{}

Flight::TICKET::Ticket(string* idnumber, int totalticket, int ticketsold, int ticketleft) 
	: IDNumber(idnumber), n(totalticket), ticketSold(ticketsold), ticketLeft(ticketleft)
{}

Flight::TIME::Time(int hour, int minute, int day, int month, int year)
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
	ticketList = new Flight::Ticket();
	left = right = nullptr;
	BF = 0;
	height = 0;
}

bool Flight::operator==(const Flight& rhs) const {
	return (this->time->_year == rhs.time->_year &&
		this->time->_month == rhs.time->_month &&
		this->time->_day == rhs.time->_day &&
		this->time->_hour == rhs.time->_hour &&
		this->time->_minute == rhs.time->_minute && 
		this->ACNumber.compare(rhs.ACNumber) == 0 && 
		this->AirPort.compare(rhs.AirPort) == 0);
}

bool Flight::operator<(const Flight& rhs) const {
	if (this->time->_year < rhs.time->_year)
		return true;
	else if (this->time->_year == rhs.time->_year) {
		if (this->time->_month < rhs.time->_month)
			return true;
		else if (this->time->_month == rhs.time->_month) {
			if (this->time->_day < rhs.time->_day)
				return true;
			else if (this->time->_day == rhs.time->_day) {
				if (this->time->_hour < rhs.time->_hour)
					return true;
				else if (this->time->_hour == rhs.time->_hour) {
					if (this->time->_minute < rhs.time->_minute)
						return true;
					else if (this->time->_minute == rhs.time->_minute) {
						if (this->ACNumber.compare(rhs.ACNumber) < 0)
							return true;
						else if (this->ACNumber.compare(rhs.ACNumber) == 0)
							if (this->AirPort.compare(rhs.AirPort) < 0)
								return true;
					}
				}
			}
		}
	}
	return false;
}

bool Flight::operator>(const Flight& rhs) const {
	if (this->time->_year > rhs.time->_year)
		return true;
	else if (this->time->_year == rhs.time->_year) {
		if (this->time->_month > rhs.time->_month)
			return true;
		else if (this->time->_month == rhs.time->_month) {
			if (this->time->_day > rhs.time->_day)
				return true;
			else if (this->time->_day == rhs.time->_day) {
				if (this->time->_hour > rhs.time->_hour)
					return true;
				else if (this->time->_hour == rhs.time->_hour) {
					if (this->time->_minute > rhs.time->_minute)
						return true;
					else if (this->time->_minute == rhs.time->_minute) {
						if (this->ACNumber.compare(rhs.ACNumber) > 0)
							return true;
						else if (this->ACNumber.compare(rhs.ACNumber) == 0)
							if (this->AirPort.compare(rhs.AirPort) > 0)
								return true;
					}
				}
			}
		}
	}
	return false;
}