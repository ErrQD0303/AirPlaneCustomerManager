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
void FMSearchInterface(FlightList*, airCraftList*);
void block_char_search_FM(char*, int, int, int,
	FlightList*, airCraftList*, vector<int>);
bool checkDay(int day, int month, int year);

void FMMainInterface(FlightList* FL, airCraftList* AC) {
	int page = 0;
	char inputChar;
	do {
	FMStartingPage:
		showCur(0);
		FL->FMPrintFlightInforMainInterface(AC, page);
		inputChar = _getch();
		if (inputChar == 59)
			FMSearchInterface(FL, AC);
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
}

void FMSearchInterface(FlightList* FL, airCraftList* AC) {
	vector<int> pos;
	begin:
	int page = 0;
	showCur(1);
	AC->PMPrintPlaneTypeInforSearchInterface(page);
	char* planeType = new char[100];
	do {
		block_char_search_FM(planeType, 100, 41, 3, FL, AC, pos);
	} while (strlen(planeType) == 0);
	if (planeType[0] == '?')
		goto begin;
	if (planeType[0] == '.')
		return;
	delete[] planeType;
}

void FMAddInterface(FlightList* FL, airCraftList* AC, int& key, int pos) {
	showCur(1);
	system("cls");
	menuCurTime();
	FMAddBox();
	flushConsoleInputBuffer();
	int i = 0, _month, _day, _year;
	char* flightcode = new char[21];
	char* airport = new char[21];
	char* day = new char[3];
	char* month = new char[3];
	char* year = new char[5];
	char* hour = new char[3];
	char* min = new char[3];
	char inputChar;
	gotoxy(55, 10); std::cout << AC->getACNumber(pos);
	gotoxy(55, 15); std::cout << AC->getTotalSeats(pos);
	do {
	editI:
		showCur(1);
		do {
			gotoxy(55, 11);
			std::cout << std::setw(31) << std::setfill(' ') << "";
			block_char(flightcode, 20, 55, 11);
			if (flightcode[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(37) << std::setfill(' ') << "";
			if (strlen(flightcode) > 20) {
				gotoxy(88, 5);
				std::cout << "Flight Code has max 20 characters!!!";
			}
		} while (strlen(flightcode) == 0 || strlen(flightcode) > 20);
		do {
			gotoxy(54, 12);
			std::cout << std::setw(31) << std::setfill(' ') << "";
			block_char(airport, 20, 54, 12);
			if (airport[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(33) << std::setfill(' ') << "";
			if (strlen(flightcode) > 20) {
				gotoxy(88, 5);
				std::cout << "Airport has max 20 characters!!!";
			}
			} while (strlen(airport) == 0 || strlen(airport) > 20);
		Rday:
		do{
			gotoxy(45, 13);
			std::cout << std::setw(10) << std::setfill(' ') << "";
			gotoxy(45, 13); std::cout << "  /  /";
			block_char_number(day, 2, 45, 13);
			if (day[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(2) << std::setfill(' ') << "";
			if (strlen(day) > 2) {
				gotoxy(88, 5);
				std::cout << "Day can't have more than two character!!!";
				continue;
			}
			if (atoi(day) <= 0 || atoi(day) > 31) {
				gotoxy(88, 5);
				std::cout << "Day invalid!!! Input again";
				continue;
			}
			if (atoi(day) < 10) {
				if (strlen(day) == 1) {
					day[1] = day[0];
					day[0] = '0';
					day[2] = '\0';
				}
				gotoxy(45, 13); std::cout << day;
			}
			break;
		} while (1);
		do {
			gotoxy(48, 13);
			std::cout << std::setw(2) << std::setfill(' ') << "";
			gotoxy(48, 13); std::cout << "  /";
			block_char_number(month, 2, 48, 13);
			if (month[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(33) << std::setfill(' ') << "";
			if (strlen(month) > 2) {
				gotoxy(88, 5);
				std::cout << "Month can't have more than two character!!!";
				continue;
			}
			if (atoi(month) <= 0 || atoi(month) > 12) {
				gotoxy(88, 5);
				std::cout << "Month invalid!!! Input again";
				continue;
			}
			if (atoi(month) < 10) {
				if (strlen(month) == 1) {
					month[1] = month[0];
					month[0] = '0';
					month[2] = '\0';
				}
				gotoxy(48, 13); std::cout << month;
			}
			break;
		} while (1);
		do {
			gotoxy(51, 13);
			std::cout << std::setw(4) << std::setfill(' ') << "";
			block_char_number(year, 20, 51, 13);
			if (year[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(33) << std::setfill(' ') << "";
			if (strlen(year) > 4) {
				gotoxy(88, 5);
				std::cout << "This isnt 10000 BC!!!";
				continue;
			}
			if (atoi(year) < 1903) {
				gotoxy(88, 5);
				std::cout << "Plane hadn't been invented yet!";
				continue;
			}
			_day = atoi(day);
			_month = atoi(month);
			_year = atoi(year);
			if (checkDay(_day, _month, _year) == 0) {
				gotoxy(88, 5);
				std::cout << "Date invalid!!! Input again";
				goto Rday;
			}
			break;
		} while (1);
		do {
			gotoxy(47, 14);
			std::cout << std::setw(2) << std::setfill(' ') << "";
			gotoxy(47, 14); std::cout << "  :";
			block_char_number(hour, 2, 47, 14);
			if (hour[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(33) << std::setfill(' ') << "";
			if (strlen(hour) > 2) {
				gotoxy(88, 5);
				std::cout << "Hour can't have more than two character!!!";
				continue;
			}
			if (atoi(hour) == 24) {
				hour[0] = '0';
				hour[1] = '0';
				hour[2] = '\0';
				gotoxy(47, 14); std::cout << hour;
				break;
			}
			if (atoi(hour) < 0 || atoi(hour) > 24) {
				gotoxy(88, 5);
				std::cout << "Hour invalid!!! Input again";
				continue;
			}
			if (atoi(hour) < 10) {
				if (strlen(hour) == 1) {
					hour[1] = hour[0];
					hour[0] = '0';
					hour[2] = '\0';
				}
				gotoxy(47, 14); std::cout << hour;
			}
			break;
		} while (1);
		do {
			gotoxy(50, 14);
			std::cout << std::setw(3) << std::setfill(' ') << "";
			block_char_number(min, 2, 50, 14);
			if (min[0] == '.') {
				FMSearchInterface(FL, AC);
				return;
			}
			gotoxy(88, 5);
			std::cout << std::setw(33) << std::setfill(' ') << "";
			if (strlen(min) > 2) {
				gotoxy(88, 5);
				std::cout << "Minute can't have more than two character!!!";
				continue;
			}
			if (atoi(min) == 60) {
				min[0] = min[1] = '0';
				min[2] = '\0';
				gotoxy(50, 14); std::cout << min;
			}
			if (atoi(min) < 0 || atoi(min) > 60) {
				gotoxy(88, 5);
				std::cout << "Minute invalid!!! Input again";
				continue;
			}
			if (atoi(min) < 10) {
				if (strlen(min) == 1) {
					min[1] = min[0];
					min[0] = '0';
					min[2] = '\0';
				}
				gotoxy(50, 14); std::cout << min;
			}
			break;
		} while (1);
		break;
	} while (1);
	string _time(hour); 
	_time += ':';
	for (int i = 0; i < strlen(min); i++) {
		_time += min[i];
	}
	_time += '-';
	for (int i = 0; i < strlen(day); i++) {
		_time += day[i];
	}
	_time += '/';
	for (int i = 0; i < strlen(month); i++) {
		_time += month[i];
	}
	_time += '/';
	for (int i = 0; i < strlen(year); i++) {
		_time += year[i];
	}
	FL->insertFlight(flightcode, AC->getACNumber(pos), airport, _time, AC);
	Sleep(400);
	system("cls");
	gotoxy(55, 13);
	std::cout << "Adding Flight";
	Sleep(400);
	std::cout << ".";
	Sleep(400);
	std::cout << ".";
	Sleep(400);
	std::cout << ".";
	Sleep(400);
	delete[] flightcode, airport, day, month, year, hour, min;
}

void block_char_search_FM(char* b, int a, int x, int y,
	FlightList* FL, airCraftList* AC, vector<int> pos) {
	pos.clear();
	for (int i = 0; i < AC->getTotalAC(); i++)
		pos.push_back(i);
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
			AC->PMPrintPlaneTypeInforSearchInterface(0, pos);
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
							AC->PMPrintPlaneTypeInforSearchInterface(b, count1, pos, page);
							goto choose;
						}
					}
				}
				if (inputChar == 13) {
					int key1 = 0;
					FMAddInterface(FL, AC, key1, pos[count2]);
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

bool checkDay(int day, int month, int year) {
	switch (month) {
	case 1:	case 3:	case 5:	case 7:	case 8:	case 10: case 12: {
		return true;
	}
	case 2: {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (day > 29)
				return false;
		}
		else
			if (day > 28)
				return false;
		return true;
	}
	case 4: case 6: case 9: case 11: {
		if (day > 30)
			return false;
		return true;
	}
	}
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

//void FlightList::FMPrintFlightInforSearchInterface(airCraftList* AC, char* c, 
//	int& count, vector<int> pos) const {
//	for (int i = 0; i < 19; i++) {
//		gotoxy(8, 7 + i); std::cout << std::setw(4) << std::setfill(' ') << " ";
//		gotoxy(31, 7 + i); std::cout << std::setw(30) << std::setfill(' ') << " ";
//		gotoxy(77, 7 + i); std::cout << std::setw(6) << std::setfill(' ') << " ";
//		gotoxy(107, 7 + i); std::cout << std::setw(11) << std::setfill(' ') << " ";
//	}
//	char* input = new char[100];
//	gotoxy(103, 28); std::cout << j + 1 << "/" << (v.size() / 19) + 1;
//	for (int i = 18 * j; (i < v.size() && i < 18 * (j + 1)) || (i == 0 && v.size() == 1); i++) {
//		gotoxy(8, 8 + i % 18); std::cout << i + 1;
//		std::strcpy(input, v[i]->ACNumber.c_str());
//		gotoxy(16, 8 + i % 18); std::cout << AC->getACTypeByNumber(input);
//		gotoxy(32, 8 + i % 18); std::cout << v[i]->FlightCode;
//		gotoxy(43, 8 + i % 18); std::cout << v[i]->ACNumber;
//		gotoxy(60, 8 + i % 18); std::cout << v[i]->AirPort;
//		gotoxy(76, 8 + i % 18);
//		if (v[i]->time->_day < 10)
//			std::cout << '0' << v[i]->time->_day;
//		else
//			std::cout << v[i]->time->_day;
//		gotoxy(81, 8 + i % 18);
//		if (v[i]->time->_month < 10)
//			std::cout << '0' << v[i]->time->_month;
//		else
//			std::cout << v[i]->time->_month;
//		gotoxy(85, 8 + i % 18); std::cout << v[i]->time->_year;
//		gotoxy(91, 8 + i % 18);
//		if (v[i]->time->_hour < 10)
//			std::cout << '0' << v[i]->time->_hour;
//		else
//			std::cout << v[i]->time->_hour;
//		gotoxy(96, 8 + i % 18);
//		if (v[i]->time->_minute < 10)
//			std::cout << '0' << v[i]->time->_minute;
//		else
//			std::cout << v[i]->time->_minute;
//		gotoxy(101, 8 + i % 18);
//		if (v[i]->ticketList->n < 10)
//			std::cout << '0' << v[i]->ticketList->n;
//		else
//			std::cout << v[i]->ticketList->n;
//		gotoxy(109, 8 + i % 18);
//		std::cout << flightConditionPrint(v[i]->Flight_Status);
//	}
//	delete[] input;

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

bool FlightList::insertFlight(const string& flightcode, const string& acnumber,
	const string& airport, const string& time, const airCraftList* AC) {
	Flight::Ticket* ticket = new Flight::Ticket();
	ticket->n = AC->getTotalSeatsByNumber(acnumber.c_str());
	ticket->ticketLeft = ticket->n;
	Flight* newflight = new Flight(flightcode, acnumber, airport, time,
		FlightStatus(0), ticket);
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
	IDNumber[0] = "000000000";
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