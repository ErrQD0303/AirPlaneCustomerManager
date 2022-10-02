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

string flightConditionPrint(const FlightStatus&);

void FMMainInterface(FlightList* FL, airCraftList* AC) {
	int page = 0;
	char inputChar;
	do {
	FMStartingPage:
		showCur(0);
		FL->FMPrintFlightInforMainInterface(AC, page);
		inputChar = _getch();
		if (inputChar == 59)
			//PMAddInterface(AC);
			if (inputChar == 61)
				//PMEditInterface(AC);
				if (inputChar == 83) {
					//PMDeleteInterface(AC);
				}
		if (inputChar == 80 && FL->getTotalFlight() / 18 * (page + 1) > 0 && page < FL->getTotalFlight() / 18) {
			page++;
		}
		if (inputChar == 72 && page > 0)
			page--;
	} while (inputChar != 27);
	FL->writeFile();
}

void FlightList::FMPrintFlightInforMainInterface(airCraftList* AC, int j) const {
	vector<Flight*> v;
	inOrderDFT(root, v);
	system("cls");
	menuCurTime();
	FMMainBox();
	char* input = new char[100];
	gotoxy(103, 28); std::cout << j + 1 << "/" << (v.size() / 19) + 1;
	for (int i = 18 * j; (i < v.size() && i < 18 * (j + 1)) || (i == 0 && v.size() == 1); i++) {
		gotoxy(8, 8 + i % 18); std::cout << i + 1;
		std::strcpy(input, v[i]->ACNumber.c_str());
		gotoxy(16, 8 + i % 18); std::cout << AC->getACTypeByNumber(input);
		gotoxy(32, 8 + i % 18); std::cout << v[i]->FlightCode;
		gotoxy(43, 8 + i % 18); std::cout << v[i]->ACNumber;
		gotoxy(60, 8 + i % 18); std::cout << v[i]->AirPort;
		gotoxy(76, 8 + i % 18);
		if (v[i]->time->_day < 10)
			std::cout << '0' << v[i]->time->_day;
		else
			std::cout << v[i]->time->_day;
		gotoxy(81, 8 + i % 18);
		if (v[i]->time->_month < 10)
			std::cout << '0' << v[i]->time->_month;
		else
			std::cout << v[i]->time->_month;
		gotoxy(85, 8 + i % 18); std::cout << v[i]->time->_year;		
		gotoxy(91, 8 + i % 18);
		if (v[i]->time->_hour < 10)
			std::cout << '0' << v[i]->time->_hour;
		else
			std::cout << v[i]->time->_hour;
		gotoxy(96, 8 + i % 18); 
		if (v[i]->time->_minute < 10)
			std::cout << '0' << v[i]->time->_minute;
		else
			std::cout << v[i]->time->_minute;
		gotoxy(101, 8 + i % 18);
		if (v[i]->ticketList->n < 10)
			std::cout << '0' << v[i]->ticketList->n;
		else
			std::cout << v[i]->ticketList->n;
		gotoxy(109, 8 + i % 18); 
		std::cout << flightConditionPrint(v[i]->Flight_Status);
	}
	delete[] input;
}

string flightConditionPrint(const FlightStatus& flightstatus) {
	switch (flightstatus) {
	case 0:
		return "ONTIME";
	case 1:
		return "DELAY";
	case 2:
		return "FLYING";
	case 3:
		return "COMPLETE";
	default:
		return "NO INFOR";
	};
}

FlightList::FlightList() {
	root = nullptr;
	fCount = 0;
}

FlightList::~FlightList() {
	clear();
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

void FlightList::deleteFlight(const string& flightcode) {
	root = recursiveDelete(root, flightcode);
	fCount--;
}

Flight* FlightList::recursiveDelete(Flight* subroot, const string& flightcode) {
	if (subroot == nullptr) {
		return subroot;
	}
	else if (flightcode.compare(subroot->FlightCode) < 0)
		subroot->left = recursiveDelete(subroot->left, flightcode);
	else if (flightcode.compare(subroot->FlightCode) > 0)
		subroot->right = recursiveDelete(subroot->right, flightcode);
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
			subroot->right = recursiveDelete(subroot->right, flightcode);
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

const Flight* FlightList::searchFlight(const string& flightcode) const {
	Flight* pSearch = root;
	while (pSearch != nullptr &&
		pSearch->FlightCode.compare(flightcode) != 0) {
		if (pSearch->FlightCode.compare(flightcode) > 0)
			pSearch = pSearch->left;
		else
			pSearch = pSearch->right;
	}
	return pSearch;
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

void FlightList::postOrderDeleteTree(Flight* subroot) {
	if (subroot != nullptr) {
		postOrderDeleteTree(subroot->left);
		postOrderDeleteTree(subroot->right);
		delete subroot;
		subroot = nullptr;
	}
}

void FlightList::clear() {
	postOrderDeleteTree(root);
	fCount = 0;
}

bool FlightList::operator!() const {
	return (root == nullptr);
}

void FlightList::inOrderDFT(Flight* subroot, vector<Flight*>& v) const {
	if (subroot != nullptr) {
		inOrderDFT(subroot->left, v);
		v.push_back(subroot);
		inOrderDFT(subroot->right, v);
	}
}

//00:00-01/01/2022
Flight::Time* FlightList::timeParse(const string& exactdaytime) {
	Flight::Time* time = new Flight::Time();
	char c[100];
	char* token;
	std::strcpy(c, exactdaytime.c_str());
	token = strtok(c, " :-/");
	time->_hour = atoi(token);
	token = strtok(NULL, " :-/");
	time->_minute = atoi(token);
	token = strtok(NULL, " :-/");
	time->_day = atoi(token);
	token = strtok(NULL, " :-/");
	time->_month = atoi(token);
	token = strtok(NULL, " :-/");
	time->_year = atoi(token);
	return time;
}

int FlightList::getTotalFlight() const {
	return fCount;
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

Flight::Flight(string flightcode, string acnumber, string airport, string exactdaytime, 
	FlightStatus flightstatus, Ticket* ticketlist) 
	: ACNumber(acnumber), FlightCode(flightcode), AirPort(airport),
	Flight_Status(flightstatus), ticketList(ticketlist) {
	time = new Time();
	char c[100];
	char* token;
	std::strcpy(c, exactdaytime.c_str());
	token = strtok(c, " :-/");
	time->_hour = atoi(token);
	token = strtok(NULL, " :-/");
	time->_minute = atoi(token);
	token = strtok(NULL, " :-/");
	time->_day = atoi(token);
	token = strtok(NULL, " :-/");
	time->_month = atoi(token);
	token = strtok(NULL, " :-/");
	time->_year = atoi(token);
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