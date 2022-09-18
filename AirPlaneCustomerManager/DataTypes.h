#pragma once
#include <iostream>
#define MAX 300
class airCraftList {
private:
	class airCraft {
	public:
		char ACNumber[6];
		char* ACType;
		int TotalSeats;
	};
	airCraft* ACList[MAX];
	int TotalAC = 0;
};