#pragma once
#include <iostream>
#include <vector>
#include <mutex>
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

class Flight {
	//friend class FlightList;
public:
	class ticket {
public:
	int n = 1;
	string* IDNumber;
	int ticketLeft = n;
	int ticketSold = 0;
};
	typedef class ticket TICKET;
	Flight() {
		ticketList = new ticket();
	}
	~Flight() {
		delete ticketList;
	}
	char ACNumber[20];
	char AirPort[100];
	int NumberOfFlight;
	char FlightCode[20];
	int hour = 0;
	int minute = 0;
	int day = 1;
	int month = 1;
	int year = 2022;
	int FlightCondition;
	ticket* ticketList;
	Flight* next;
	Flight* prev;
};
typedef class Flight FLIGHT;

// using mutex to synchronize multithreads to create just 1 objects of
// this class (using linked list)

class FlightList : public Flight {
public:
	Flight* head;
	int fCount = 0;
	static FlightList* flightList;
	static mutex mLocker;
	static FlightList* getInstance() {
		mLocker.lock();
		if (flightList == nullptr)
			flightList = new FlightList();
		mLocker.unlock();
		return flightList;
	}
	void get() {
		FlightList* a = FlightList::getInstance();
		a->month = 0;
	}
};
typedef class FlightList FLIGHTLIST;

FlightList* FlightList::flightList = nullptr;
mutex FlightList::mLocker;