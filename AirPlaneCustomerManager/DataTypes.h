#pragma once
#ifndef DATATYPE_H
#define DATATYPE_H

#include <iostream>
#include <vector>
#include <mutex>
#include <string>

#define MAX 300
class airCraftList {
private:
	class airCraft {
	public:
		char ACNumber[20];
		char ACType[100];
		int TotalSeats;
	};
	airCraft* ACList[MAX];
	int TotalAC;
public:
	airCraftList();
	~airCraftList();
	int insertAirCraft(char* acNumber, char* acType, int totalSeats);
	void editAirCraft(char* acNumber, char* acType, int totalSeats, const int& pos);
	void deleteAirCraft(const int& pos);
	char* getACNumber(const char* acNumber) const;
	char* getACType(const char* acNumber) const;
	int getTotalSeats(const char* acNumber) const; 
	char* getACNumber(const int& pos) const;
	char* getACType(const int& pos) const;
	int getTotalSeats(const int& pos) const;
	void writeAirCraftFile();
	void PMPrintPlaneTypeInforMainInterface(int j) const;
	void PMPrintPlaneTypeInforSearchInterface(int j) const;
	void PMPrintPlaneTypeInforSearchInterface(int j, vector<int>& pos) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c, int& count, vector<int>& pos) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c, int count, vector<int>& pos, int page) const;
	int getTotalAC() const;
};

enum FlightStatus {
	ONTIME = 0, DELAY, FLYING, COMPLETE
};

class Flight {
	friend class FlightList;
private:
	class Ticket {
	public:
		int n;
		string* IDNumber;
		int ticketLeft;
		int ticketSold;
		Ticket(int = 1, int = 1, int = 0);
		Ticket(string*, int = 1, int = 1, int = 0);
		~Ticket() {
			delete[] IDNumber;
		}
	};
	typedef class Ticket TICKET;

	class Time {
		friend class FlightList;
	public:
		int _hour, _minute, _day, _month, _year;
		Time(int = 0, int = 0, int = 1, int = 1, int = 2022);
	};
	typedef class Time TIME;

	string ACNumber;
	int NumberOfFlight;
	string FlightCode;
	string AirPort;
	Time* time;
	FlightStatus Flight_Status;
	Ticket* ticketList;
	Flight* left;
	Flight* right;
	int BF;

	Flight(string = "", string = "", string = "", string = "00:00-01/01/2022",
		FlightStatus = ONTIME, Ticket* = new Ticket);

	~Flight() {
		delete ticketList, time;
	}

	bool operator==(const Flight& rhs) const;
	bool operator<(const Flight& rhs) const;
	bool operator>(const Flight& rhs) const;
	bool operator>=(const Flight& rhs) const {
		return !(*this < rhs);
	}
};
typedef class Flight FLIGHT;

// using mutex to synchronize multithreads to create just 1 objects of
// this class (using linked list)

class FlightList {
private:
	Flight* root;
	int fCount;
	static FlightList* flightlist;
	static mutex mLocker;
	FlightList();
	~FlightList();
public:
	static FlightList *getInstance() {
		mLocker.lock();
		if (flightlist == nullptr) {
			flightlist = new FlightList();
		}
		mLocker.unlock();
		return flightlist;
	}
	bool insertFlight(const string&, const string&, const string&, 
		const string&, const FlightStatus&, Flight::Ticket*);
	Flight* recursiveInsert(Flight*, Flight*, bool&);
	Flight* rotateLeft(Flight*);
	Flight* rotateRight(Flight*);
	bool deleteFlight(const string&);
	Flight* recursiveDelete(Flight*, const string&, bool&);
	int height(Flight*);
	Flight* minValueFlight(Flight*);
	int getBalanceFactor(Flight*);
	void copyFlightData(Flight*, Flight*);
	void clear();
	Flight::Time* timeParse(const string&);
	void readFlightFile();
	void writeFlightFile(Flight*);
	bool operator!() const;
};
typedef class FlightList FLIGHTLIST;

FlightList* FlightList::flightlist = nullptr;
mutex FlightList::mLocker;
#endif