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
		ifs >> planeType >> planeNumber >> totalSeats;
		AC->insertAirCraft(planeType, planeNumber, totalSeats);
	}
	ifs.close();
}

void airCraftList::writeAirCraftFile() {
	std::ofstream ofs;
	ofs.open("AirCraft.txt");
	for (int i = 0; i < TotalAC; i++) {
		if (TotalAC != 0 && i > 0)
			ofs << std::endl;
		ofs << ACList[i]->ACType << std::endl
			<< ACList[i]->ACNumber << std::endl
			<< ACList[i]->TotalSeats;
	}
	ofs.close();
}