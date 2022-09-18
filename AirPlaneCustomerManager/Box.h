#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <stdio.h>

void boxnho(int, int, int, int);
void PMboxtong();

void PMMainBox() {
	PMboxtong();
	boxnho(5, 18, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: EXIT";
	boxnho(20, 31, 27, 29);
	gotoxy(22, 28); std::cout << "<F1>: ADD";
	boxnho(33, 45, 27, 29);
	gotoxy(35, 28); std::cout << "<F3>: EDIT";
	boxnho(47, 65, 27, 29);
	gotoxy(49, 28); std::cout << "<DELETE>: DELETE";
}

void PMSearchBox() {
	PMboxtong();
	gotoxy(50, 3);
	std::cout << std::setw(25) << std::setfill(' ') << " ";
	boxnho(5, 21, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: GO BACK";
	boxnho(23, 40, 27, 29);
	gotoxy(25, 28); std::cout << "<ENTER>: CHOOSE";
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
	gotoxy(97, 3); std::cout << "AIRCRAFT TYPE LIST";
	gotoxy(14, 3); std::cout << "Search Aircraft By Number: ";
}

void boxnho(int x1, int x2, int y1, int y2) {
	gotoxy(x1, y1);
	std::cout << char(218) << std::setw(x2 - x1) << std::setfill(char(196))
		<< char(196) << char(191);
	for (int i = y1 + 1; i < y2; i++) {
		gotoxy(x1, i); std::cout << char(179);
		gotoxy(x2 + 1, i); std::cout << char(179);
	}
	gotoxy(x1, y2);
	std::cout << char(192) << std::setw(x2 - x1) << std::setfill(char(196))
		<< char(196) << char(217);
}

void boxnoi0(int x, int y) { // ┬
	gotoxy(x, y);
	std::cout << char(194);
}

void boxnoi1(int x, int y) { //┴
	gotoxy(x, y);
	std::cout << char(193);
}

void boxnoi2(int x, int y) { //├
	gotoxy(x, y);
	std::cout << char(195);
}

void boxnoi3(int x, int y) { //┤
	gotoxy(x, y);
	std::cout << char(180);
}

void boxnoi4(int x, int y) { //┼
	gotoxy(x, y);
	std::cout << char(197);
}

void PMboxtong() {
	boxnho(5, 117, 1, 26);
	boxnho(5, 11, 4, 26);
	boxnho(12, 60, 4, 26);
	boxnho(61, 95, 4, 26);
	boxnho(96, 117, 4, 26);
	boxnho(5, 117, 1, 4);
	boxnho(5, 117, 4, 6);
	boxnoi0(12, 4);
	boxnoi0(61, 4);
	boxnoi0(96, 4);
	boxnoi1(12, 26);
	boxnoi1(61, 26);
	boxnoi1(96, 26);
	boxnoi2(5, 4);
	boxnoi2(5, 6);
	boxnoi3(118, 4);
	boxnoi3(118, 6);
	boxnoi4(12, 6);
	boxnoi4(61, 6);
	boxnoi4(96, 6);
	gotoxy(50, 3);
	std::cout << "AIRCRAFT TYPE MANAGEMENT";
	gotoxy(6, 5); std::cout << "INDEX";
	gotoxy(30, 5); std::cout << "Aircraft Type";
	gotoxy(72, 5); std::cout << "Aircraft Number";
	gotoxy(102, 5); std::cout << "Total Seats";
}