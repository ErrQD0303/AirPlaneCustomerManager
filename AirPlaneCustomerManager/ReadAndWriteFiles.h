#pragma once
#include <iostream>
#include <fstream>
#include "DataTypes.h"

void readAirCraftFile(airCraftList* AC) {
	char* planeType = new char[100];
	char* planeNumber = new char[100];
	int totalSeats;
	std::ifstream ifs;
	ifs.open("AirCraft.txt");
	while (!ifs.eof()) {
		ifs.getline(planeType, 100, '\n');
		ifs.getline(planeNumber, 100,  '\n');
		ifs >> totalSeats;
		ifs.ignore();
		AC->insertAirCraft(planeType, planeNumber, totalSeats);
	}
	ifs.close();
}

void airCraftList::writeAirCraftFile() {
	std::ofstream ofs;
	ofs.open("AirCraft.txt");
	for (int i = 0; i < TotalAC; i++) {
		if (TotalAC != 0 && i > 0)
			ofs << "\n";
		ofs << ACList[i]->ACType << "\n"
			<< ACList[i]->ACNumber << "\n"
			<< ACList[i]->TotalSeats;
	}
	ofs.close();
}

int FlightList::readFlightFile() { // ok
	char* input = new char[100];
	string acnumber, flightcode, airport, time;
	int flightstatus, totalticket, ticketsold, ticketleft;
	std::ifstream ifs;
	ifs.open("Flight.txt");
	while (!ifs.eof()) {
		ifs.getline(input, 100, '\n');
		flightcode.assign(input);
		ifs.getline(input, 100, '\n');
		acnumber.assign(input);
		ifs.getline(input, 100, '\n');
		airport.assign(input);
		ifs.getline(input, 100, '\n');
		time.assign(input);
		ifs >> flightstatus >> totalticket >> ticketsold >> ticketleft;
		std::string* IDNumber = new string[totalticket];
		int temp;
		for (int i = 0; i < ticketsold; i++) {
			ifs >> temp;
			ifs >> IDNumber[temp - 1];
		}
		ifs.ignore();
	}
	ifs.close();
}