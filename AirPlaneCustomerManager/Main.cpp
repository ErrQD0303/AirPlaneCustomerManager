#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PlaneTypeManager.h"
#include "MainMenu.h"
#include <cstring>
#include <string>
#include "DataTypes.h"
#include "FlightManager.h"
#include <chrono>

int main() {
	//char c[100];
	//string d = "Hello There My Friend!";
	//std::strcpy(c, d.c_str());
	//char* token = strtok(c, " !");
	//while (token != nullptr) {
	//	std::cout << token << "\n";
	//	token = std::strtok(NULL, " !");
	auto f = []() {
		std::mutex mlock;
		std::lock_guard<std::mutex> lock(mlock);
		int day = 0;
		while (1) {
			menuCurTime();
			Sleep(1000);
		}
	};
	std::thread th1(f);
	std::thread th2(MainMenu);
	if (th1.joinable())
		th1.join();
	if (th2.joinable())
		th2.join();
	return 0;
}