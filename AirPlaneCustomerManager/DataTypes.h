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
	char* getACType(const char* acType) const;
	char* getACTypeByNumber(const char* acNumber) const;
	int getTotalSeats(const char* acNumber) const; 
	char* getACNumber(const int& pos) const;
	char* getACType(const int& pos) const;
	int getTotalSeats(const int& pos) const;
	int getTotalSeatsByNumber(const char* acNumber) const;
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
	Flight* recursiveInsert(Flight*, Flight*, bool&);
	Flight* rotateLeft(Flight*);
	Flight* rotateRight(Flight*);
	Flight* recursiveDelete(Flight*, const string&);
	void postOrderDeleteTree(Flight*);
	Flight* minValueFlight(Flight*);
	void writeFlightFile(Flight*, airCraftList*, std::ofstream&);
	Flight::Time* timeParse(const string&);
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
	bool insertFlight(const string&, const string&, const string&,
		const string&, const airCraftList*);
	void deleteFlight(const string&);
	int height(Flight*);
	int getBalanceFactor(Flight*);
	void copyFlightData(Flight*, Flight*);
	void clear();
	const Flight* searchFlight(const string&) const;
	void readFlightFile();
	void writeFile(airCraftList*);
	bool operator!() const;
	void FMEditInterface(Flight*, airCraftList*);
	void FMPrintFlightInforMainInterface(const airCraftList*, int) const;
	void FMPrintFlightInforSearchInterface(const airCraftList*, int) const;
	void FMPrintFlightInforSearchInterface(airCraftList*, char*, 
		int&, vector<Flight*>&, vector<Flight*>&) const;
	void FMPrintFlightInforSearchInterface(const airCraftList*, const char*,
		int, const vector<Flight*>&, int) const;
	void addFlightToVector(vector<Flight*>&) const;
	void inOrderDFT(Flight*, vector<Flight*>&) const;
	int getTotalFlight() const;
	void block_char_edit_FM(char* b, int a, int x, int y,
		FlightList* FL, airCraftList* AC, vector<Flight*>& flight);
	void block_char_delete_FM(char* b, int a, int x, int y,
		FlightList* FL, airCraftList* AC, vector<Flight*>& flight);
};
typedef class FlightList FLIGHTLIST;

FlightList* FlightList::flightlist = nullptr;
mutex FlightList::mLocker;

enum SEX {
	NOINFOR = 0, MALE, FEMALE
};

class Passenger {
	friend class PassengerList;
private:
	string sSID;
	string lastName;
	string firstName;
	SEX sex;
	Passenger* left;
	Passenger* right;
	int BF;
	// private method
	Passenger(string = "000000000", string = "", string = "",
		SEX = NOINFOR);
};
typedef class Passenger PASSENGER;

class PassengerList {
private:
	Passenger* root;
	int pCount;
	static PassengerList* passengerlist;
	static mutex mLocker1;
	PassengerList();
	~PassengerList();
	Passenger* recursiveInsert(Passenger*, Passenger*, bool&);
	Passenger* rotateLeft(Passenger*);
	Passenger* rotateRight(Passenger*);
	Passenger* recursiveDelete(Passenger*, const string&);
	void postOrderDeleteTree(Passenger*);
	Passenger* minValuePassenger(Passenger*);
	void writePassengerFile(Passenger*, std::ofstream&);
public:
	static PassengerList* getInstance() {
		mLocker1.lock();
		if (passengerlist == nullptr) {
			passengerlist = new PassengerList();
		}
		mLocker1.unlock();
		return passengerlist;
	}
	void readPassengerFile();
	void writeFile();
	bool insertPassenger(const std::string&, const std::string&, const std::string&,
		const SEX&);
	void deletePassenger(const string&);
	int height(Passenger*);
	int getBalanceFactor(Passenger*);
	void copyPassengerData(Passenger*, Passenger*);
	void clear();
	const Passenger* searchPassenger(const string&) const;	
	void addPassengerToVector(vector<Passenger*>&) const;
	void inOrderDFT(Passenger*, vector<Passenger*>&) const;
	int getTotalPassenger() const;
	char* getSSID(const Passenger*) const;
	string getName(const Passenger*) const;
	SEX getSex(const Passenger*) const;
	void setSSID(const string&, Passenger*);
	void setName(const string&, Passenger*);
	void setSex(const SEX&, Passenger*);
	void PaMPrintPassengerInforMainInterface(int, vector<Passenger*>&) const;
	void PaMPrintPassengerInforSearchInterface(char*, int&, vector<Passenger*>&, vector<Passenger*>&);
	void PaMPrintPassengerInforSearchInterface(const char*, int, const vector<Passenger*>&, int) const;
	void block_char_search_PaM(char*, int, int, int, vector<Passenger*>&, int);
};
typedef class PassengerList PASSENGERLIST;

PassengerList* PassengerList::passengerlist = nullptr;
mutex PassengerList::mLocker1;

#endif