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

class flight {
	//friend class flightList;
public:
	class ticket {
public:
	int n = 1;
	string* IDNumber;
	int ticketLeft = n;
	int ticketSold = 0;
};
	flight() {
		ticketList = new ticket();
	}
	~flight() {
		delete ticketList;
	}
	typedef class ticket TICKET;
protected:
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
};
typedef class flight FLIGHT;

class flightList : public flight {
private:
	flight _flight;
	flightList* next;
	int count = 0;
public:
	void get() {
		next->ticketList->IDNumber;
	}
};
typedef class flightList FLIGHTLIST;