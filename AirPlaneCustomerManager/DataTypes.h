#pragma once
#include <iostream>
#include <vector>
#define MAX 300
class airCraftList {
private:
	class airCraft {
	public:
		char ACNumber[100];
		char ACType[100];
		int TotalSeats;
	};
	airCraft* ACList[MAX];
	int TotalAC;
public:
	airCraftList();
	~airCraftList();
	int insertAirCraft(char* acNumber, char* acType, int totalSeats);
	char* getACNumber(const char* acNumber) const;
	char* getACType(const char* acNumber) const;
	int getTotalSeats(const char* acNumber) const;
	void writeAirCraftFile();
	void PMPrintPlaneTypeInforMainInterface(int j) const;
	void PMPrintPlaneTypeInforSearchInterface(int j) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c, int& count, vector<int>& pos) const;
	void PMPrintPlaneTypeInforSearchInterface(char* c, int count, vector<int> pos, int page) const;
	int getTotalAC() const;
};