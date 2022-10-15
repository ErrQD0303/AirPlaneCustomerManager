#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PlaneTypeManager.h"
#include "MainMenu.h"
#include <cstring>
#include <string>
#include "DataTypes.h"
#include "FlightManager.h"

int main() {
	//char c[100];
	//string d = "Hello There My Friend!";
	//std::strcpy(c, d.c_str());
	//char* token = strtok(c, " !");
	//while (token != nullptr) {
	//	std::cout << token << "\n";
	//	token = std::strtok(NULL, " !");
	PaMAddBox();
	MainMenu();
	return 0;
}