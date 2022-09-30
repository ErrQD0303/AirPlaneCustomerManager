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

void FlightList::readFlightFile() { // ok
	char* input = new char[100];
	string acnumber, flightcode, airport, time;
	std::ifstream ifs;
	int flightstatus;
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
		Flight::Ticket* ticket = new Flight::Ticket();
		ifs >> flightstatus >> ticket->n >> ticket->ticketSold
			>> ticket->ticketLeft;
		ticket->IDNumber = new string[ticket->n];
		std::fill_n(ticket->IDNumber, ticket->n, "");
		int temp;
		for (int i = 0; i < ticket->ticketSold; i++) {
			ifs >> temp;
			ifs >> ticket->IDNumber[temp - 1];
		}
		insertFlight(flightcode, acnumber, airport, time, (FlightStatus)flightstatus, ticket);
		ifs.ignore();
	}
	ifs.close();
	delete[] input;
}

void FlightList::writeFlightFile(Flight* subroot) {
	std::ofstream ofs;
	ofs.open("Flight.txt");
	if (subroot == nullptr)
		return;
	if (subroot != root)
		ofs << '\n';
	ofs << subroot->FlightCode << '\n'
		<< subroot->ACNumber << '\n'
		<< subroot->AirPort << '\n'
		<< subroot->time->_hour << ':'
		<< subroot->time->_minute << '-';
	if (subroot->time->_day < 10)
		ofs << '0' << subroot->time->_day << '/';
	else
		ofs << subroot->time->_day << '/';
	if (subroot->time->_month < 10)
		ofs << '0' << subroot->time->_month << '/';
	else
		ofs << subroot->time->_month << '/';
	ofs << subroot->time->_year << '\n'
		<< subroot->Flight_Status << '\n'
		<< subroot->ticketList->n << '\n'
		<< subroot->ticketList->ticketSold << '\n'
		<< subroot->ticketList->ticketLeft;
	for (int i = 0; i < subroot->ticketList->n; i++) {
		if (subroot->ticketList->IDNumber[i].compare("") != 0) {
			ofs << '\n' << i + 1 << '\n' 
				<< subroot->ticketList->IDNumber[i];
		}
	}
	writeFlightFile(subroot->left);
	writeFlightFile(subroot->right);
	ofs.close();
}