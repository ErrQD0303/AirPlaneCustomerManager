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
	Flight* newflight = new Flight(flightcode, acnumber, airport, time, 
		flightstatus, ticket);
	bool check = true;
	root = recursiveInsert(root, newflight, check);
	if (check == true)
		fCount++;
	return check;
}

Flight* FlightList::recursiveInsert(Flight* subroot, Flight* newflight, 
	bool& check) {
	if (subroot == nullptr) {
		subroot = newflight;
		return subroot;
	}
	if (newflight->FlightCode.compare(subroot->FlightCode) < 0)
		subroot->left = recursiveInsert(subroot->left, newflight, check);
	else if (newflight->FlightCode.compare(subroot->FlightCode) > 0)
		subroot->right = recursiveInsert(subroot->right, newflight, check);
	else {
		check = false;
		return subroot;
	}
	int bf = getBalanceFactor(subroot);
	// left-left case -> right rotate
	if (bf > 1 &&
		newflight->FlightCode.compare(subroot->left->FlightCode) < 0)
		return rotateRight(subroot);
	// right right case -> left rotate
	if (bf < -1 &&
		newflight->FlightCode.compare(subroot->right->FlightCode) > 0)
		return rotateLeft(subroot);
	// left right case -> double rotate left then right
	if (bf > 1 &&
		newflight->FlightCode.compare(subroot->left->FlightCode) > 0) {
		subroot->left = rotateLeft(subroot->left);
		return rotateRight(subroot);
	}
	// right left case -> double rotate right then left
	if (bf < -1 &&
		newflight->FlightCode.compare(subroot->right->FlightCode) < 0) {
		subroot->right = rotateRight(subroot->right);
		return rotateLeft(subroot);
	}
	return subroot;
}

Flight* FlightList::rotateLeft(Flight* subroot) {
	Flight* rightTree = subroot->right;
	subroot->right = rightTree->left;
	rightTree->left = subroot;
	return rightTree;
}

Flight* FlightList::rotateRight(Flight* subroot) {
	Flight* leftTree = subroot->left;
	subroot->left = leftTree->right;
	leftTree->right = subroot;
	return leftTree;
}

bool FlightList::deleteFlight(const string& flightcode) {
	bool check = true;
	root = recursiveDelete(root, flightcode, check);
	if (check == true)
		fCount--;
	return check;
}

Flight* FlightList::recursiveDelete(Flight* subroot, const string& flightcode, 
	bool& check) {
	if (subroot == nullptr) {
		check = false;
		return subroot;
	}
	else if (flightcode.compare(subroot->FlightCode) < 0)
		subroot->left = recursiveDelete(subroot->left, flightcode, check);
	else if (flightcode.compare(subroot->FlightCode) > 0)
		subroot->right = recursiveDelete(subroot->right, flightcode, check);
	else {
		Flight* temp = nullptr;
		if (subroot->left == nullptr) {
			temp = subroot->right;
			delete subroot;
			return temp;
		}
		else if (subroot->right == nullptr) {
			temp = subroot->left;
			delete subroot;
			return temp;
		}
		else {
			temp = minValueFlight(subroot->right);
			copyFlightData(subroot, temp);
			subroot->right = recursiveDelete(subroot->right, flightcode, check);
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
}

int FlightList::height(Flight* flight) {
	if (flight == nullptr)
		return -1;
	else {
		int lheight = height(flight->left);
		int rheight = height(flight->right);
		if (lheight > rheight)
			return (lheight + 1);
		return rheight + 1;
	}
}

Flight* FlightList::minValueFlight(Flight* parent) {
	Flight* p = parent->right;
	while (p->left != nullptr) {
		parent = p;
		p = p->left;
	}
	return p;
}

int FlightList::getBalanceFactor(Flight* flight) {
	if (flight == nullptr)
		return -1;
	return (height(flight->left) - height(flight->right));
}

void FlightList::copyFlightData(Flight* lhs, Flight* rhs) {
	lhs->FlightCode = rhs->FlightCode;
	lhs->ACNumber = rhs->ACNumber;
	lhs->AirPort = rhs->AirPort;
	lhs->BF = rhs->BF;
	lhs->Flight_Status = rhs->Flight_Status;
	lhs->time = rhs->time;
	lhs->ticketList->IDNumber = rhs->ticketList->IDNumber;
	lhs->ticketList->n = rhs->ticketList->n;
	lhs->ticketList->ticketLeft = rhs->ticketList->ticketLeft;
	lhs->ticketList->ticketSold = rhs->ticketList->ticketSold;
	std::copy(rhs->ticketList->IDNumber,
		rhs->ticketList->IDNumber + rhs->ticketList->n, 
		lhs->ticketList->IDNumber);
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
{
	IDNumber = new string[100];
}

Flight::TICKET::Ticket(string* idnumber, int totalticket, int ticketsold, int ticketleft) 
	: IDNumber(idnumber), n(totalticket), ticketSold(ticketsold), ticketLeft(ticketleft)
{}

Flight::TIME::Time(int hour, int minute, int day, int month, int year)
	: _hour(hour), _minute(minute), _day(day), _month(month), _year(year)
{}

Flight::Flight(string acnumber, string flightcode, string airport, string exactdaytime, 
	FlightStatus flightstatus, Ticket* ticketlist) 
	: ACNumber(acnumber), FlightCode(flightcode), AirPort(airport),
	Flight_Status(flightstatus), ticketList(ticketlist) {
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
	NumberOfFlight = 0;
	left = right = nullptr;
	BF = 0;
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