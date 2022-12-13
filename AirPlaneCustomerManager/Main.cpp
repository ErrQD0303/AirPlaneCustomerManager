#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PlaneTypeManager.h"
#include "MainMenu.h"
#include <cstring>
#include <string>
#include "DataTypes.h"
#include "FlightManager.h"
#include <chrono>
#include <functional>

int main() {
	//char c[100];
	//string d = "Hello There My Friend!";
	//std::strcpy(c, d.c_str());
	//char* token = strtok(c, " !");
	//while (token != nullptr) {
	//	std::cout << token << "\n";
	//	token = std::strtok(NULL, " !");
	auto f = []() {
		int day = 0;
		while (1) {
			menuCurTime();
			Sleep(1000);
		}
	};
	int k;
	std::thread th1(f);
	MainMenu();
	if (th1.joinable())
		th1.join();
	return 0;
}