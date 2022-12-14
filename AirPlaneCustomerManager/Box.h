#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <conio.h>

void boxnho(int, int, int, int);
void PMboxtong();
void FMboxtong();
void PaMboxtong();

// Plane Manager Box
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
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
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

void PMAddBox() {
	boxnho(5, 29, 4, 6); 
	gotoxy(7, 5); std::cout << "Press <ESC> to go back";
	gotoxy(55, 4); std::cout << "ADD PLANE";
	boxnho(86, 117, 4, 6);
	boxnho(34, 85, 8, 14);
	gotoxy(40, 11); std::cout << "Plane Number:";
	gotoxy(40, 12); std::cout << "Plane Total Seats:";
	gotoxy(40, 10); std::cout << "Plane Type: ";
}

void PMEditBox() {
	boxnho(5, 36, 4, 6);
	gotoxy(7, 5); std::cout << "Press <ESC> exit without save";
	gotoxy(55, 4); std::cout << "EDIT PLANE";
	boxnho(86, 117, 4, 6);
	boxnho(34, 85, 8, 15);
	gotoxy(40, 11); std::cout << "Plane Number:";
	gotoxy(40, 12); std::cout << "Plane Total Seats:";
	gotoxy(40, 13); std::cout << "Save and Exit";
	gotoxy(40, 10); std::cout << "Plane Type: ";
}

void PMSaveBox() {
	boxnho(40, 80, 10, 15);
	gotoxy(50, 11); std::cout << "DO YOU WANT TO SAVE?";
	gotoxy(60, 12); std::cout << "YES";
	gotoxy(60, 13); std::cout << "NO";
	gotoxy(56, 12); std::cout << "==>";
}

void PMDeleteBox() {
	boxnho(40, 80, 10, 15);
	gotoxy(49, 11); std::cout << "DO YOU WANT TO DELETE?";
	gotoxy(60, 12); std::cout << "YES";
	gotoxy(60, 13); std::cout << "NO";
	gotoxy(56, 12); std::cout << "==>";
}

// Flight manager box
void FMMainBox() {
	FMboxtong();
	boxnho(5, 18, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: EXIT";
	boxnho(20, 31, 27, 29);
	gotoxy(22, 28); std::cout << "<F1>: ADD";
	boxnho(33, 45, 27, 29);
	gotoxy(35, 28); std::cout << "<F3>: EDIT";
	boxnho(47, 65, 27, 29);
	gotoxy(49, 28); std::cout << "<DELETE>: DELETE";
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
}

void FMAddBox() { // fix
	boxnho(5, 29, 4, 6);
	gotoxy(7, 5); std::cout << "Press <ESC> to go back";
	gotoxy(55, 4); std::cout << "ADD FLIGHT";
	boxnho(86, 117, 4, 6);
	boxnho(34, 85, 8, 23);
	gotoxy(40, 10); std::cout << "Plane Number: ";
	gotoxy(40, 11); std::cout << "Flight Code: ";
	gotoxy(40, 12); std::cout << "Airport Come: ";
	gotoxy(40, 13); std::cout << "Day: ";
	gotoxy(47, 13); std::cout << '/';
	gotoxy(50, 13); std::cout << '/';
	gotoxy(40, 14); std::cout << "Time: ";
	gotoxy(49, 14); std::cout << ':';
	gotoxy(40, 15); std::cout << "Total Tickets: ";
}

void FMEditBox() {
	FMboxtong();
	gotoxy(55, 3);
	std::cout << std::setw(18) << std::setfill(' ') << ' ';
	gotoxy(6, 4); std::cout << "Search Flight: "; // 32 - 4
	boxnho(5, 18, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: EXIT";
	boxnho(20, 36, 27, 29);
	gotoxy(22, 28); std::cout << "<ENTER>: CHOOSE";
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
}

void FMEditBox1() { // fix
	boxnho(5, 29, 4, 6);
	gotoxy(7, 5); std::cout << "Press <ESC> to go back";
	gotoxy(55, 4); std::cout << "EDIT FLIGHT";
	boxnho(86, 117, 4, 6);
	boxnho(34, 85, 8, 23);
	gotoxy(40, 10); std::cout << "Flight Code: ";
	gotoxy(40, 11); std::cout << "Airport Come: ";
	gotoxy(40, 12); std::cout << "Day: ";
	gotoxy(47, 12); std::cout << '/';
	gotoxy(50, 12); std::cout << '/';
	gotoxy(40, 13); std::cout << "Time: ";
	gotoxy(49, 13); std::cout << ':';
	gotoxy(40, 14); std::cout << "Save and Exit!";
}

// Passenger Manager Box
void PaMMainBox() {
	PaMboxtong();
	gotoxy(54, 3);
	std::cout << "MANAGE PASSENGER";
	boxnho(5, 18, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: EXIT";
	boxnho(20, 31, 27, 29);
	gotoxy(22, 28); std::cout << "<F1>: ADD";
	boxnho(33, 45, 27, 29);
	gotoxy(35, 28); std::cout << "<F3>: EDIT";
	boxnho(47, 65, 27, 29);
	gotoxy(49, 28); std::cout << "<DELETE>: DELETE";
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
}

void PaMAddBox() {
	boxnho(5, 29, 3, 5);
	gotoxy(7, 4); std::cout << "Press <ESC> to go back";
	gotoxy(52, 2); std::cout << "EDIT PASSENGER";
	boxnho(86, 117, 3, 6);
	boxnho(34, 85, 8, 12);
}

void PaMEditBox() {
	boxnho(5, 29, 3, 5);
	gotoxy(7, 4); std::cout << "Press <ESC> to go back";
	gotoxy(52, 2); std::cout << "EDIT PASSENGER";
	boxnho(86, 117, 3, 6);
	boxnho(30, 85, 8, 15);
	gotoxy(36, 10); std::cout << "SSID: "; 
	gotoxy(36, 11); std::cout << "Name: ";
	gotoxy(36, 12); std::cout << "Sex: ";
	gotoxy(36, 13); std::cout << "Save and Exit!";
}

void PaMSearchBox() {
	PaMboxtong();
	gotoxy(54, 2); std::cout << "SEARCH PASSENGER";
	boxnho(5, 18, 27, 29);
	gotoxy(7, 28); std::cout << "<ESC>: EXIT";
	boxnho(20, 31, 27, 29);
	gotoxy(22, 28); std::cout << "<F1>: ADD";
	boxnho(33, 45, 27, 29);
	gotoxy(35, 28); std::cout << "<F3>: EDIT";
	boxnho(47, 65, 27, 29);
	gotoxy(49, 28); std::cout << "<DELETE>: DELETE";
	boxnho(95, 117, 27, 29);
	gotoxy(97, 28); std::cout << "PAGE: ";
	gotoxy(15, 3); std::cout << "Search Passengers By ID:";
}

void SexBox() {
	boxnho(50, 62, 13, 16);
	gotoxy(51, 14); 
	std::cout << std::setw(12) << std::setfill(' ') << "";
	gotoxy(52, 14); std::cout << "==>";
	gotoxy(56, 14);
	std::cout << "MALE";
	gotoxy(56, 15); 
	std::cout << "FEMALE";
}

void deleteSexBox() {
	for (int i = 0; i < 4; i++) {
		gotoxy(50, 13 + i);
		std::cout << std::setw(14) << std::setfill(' ') << "";
	}
	gotoxy(50, 15);
	std::cout << std::setw(14) << std::setfill(char(196)) << "";
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

void FMboxtong() {
	boxnho(5, 117, 1, 26);
	boxnho(5, 117, 5, 7);
	boxnho(5, 10, 5, 26);
	boxnho(30, 40, 5, 26);
	boxnho(50, 73, 5, 26);
	boxnho(78, 83, 5, 26);
	boxnho(89, 93, 5, 26);
	boxnho(98, 105, 5, 26);
	boxnoi0(11, 5);
	boxnoi0(30, 5);
	boxnoi0(41, 5);
	boxnoi0(50, 5);
	boxnoi0(74, 5);
	boxnoi0(78, 5);
	boxnoi0(84, 5);
	boxnoi0(89, 5);
	boxnoi0(94, 5);
	boxnoi0(98, 5);
	boxnoi0(106, 5);
	boxnoi1(11, 26);
	boxnoi1(30, 26);
	boxnoi1(41, 26);
	boxnoi1(50, 26);
	boxnoi1(74, 26);
	boxnoi1(78, 26);
	boxnoi1(84, 26);
	boxnoi1(89, 26);
	boxnoi1(94, 26);
	boxnoi1(98, 26);
	boxnoi1(106, 26);
	boxnoi2(5, 5);
	boxnoi2(5, 7);
	boxnoi3(118, 5);
	boxnoi3(118, 7);
	boxnoi4(11, 7);
	boxnoi4(30, 7);
	boxnoi4(41, 7);
	boxnoi4(50, 7);
	boxnoi4(74, 7);
	boxnoi4(78, 7);
	boxnoi4(84, 7);
	boxnoi4(89, 7);
	boxnoi4(94, 7);
	boxnoi4(98, 7);
	boxnoi4(106, 7);
	gotoxy(55, 3);
	std::cout << "FLIGHT MANAGEMENT";
	gotoxy(6, 6); std::cout << "INDEX";
	gotoxy(16, 6); std::cout << "PLANE TYPE";
	gotoxy(31, 6); std::cout << "FLIGHTCODE";
	gotoxy(42, 6); std::cout << "PLANENUM";
	gotoxy(57, 6); std::cout << "AIRPORT COME";
	gotoxy(75, 6); std::cout << "DAY";
	gotoxy(79, 6); std::cout << "MONTH";
	gotoxy(85, 6); std::cout << "YEAR";
	gotoxy(90, 6); std::cout << "HOUR";
	gotoxy(95, 6); std::cout << "MIN";
	gotoxy(99, 6); std::cout << "TICKETS";
	gotoxy(107, 6); std::cout << "FLIGHT COND";
}

void PaMboxtong() {
	boxnho(5, 117, 1, 26);
	boxnho(5, 12, 4, 26);
	boxnho(13, 40, 4, 26);
	boxnho(41, 103, 4, 26);
	boxnho(104, 117, 4, 26);
	boxnho(5, 117, 1, 4);
	boxnho(5, 117, 4, 6);
	boxnoi0(13, 4);
	boxnoi0(41, 4);
	boxnoi0(104, 4);
	boxnoi1(13, 26);
	boxnoi1(41, 26);
	boxnoi1(104, 26);
	boxnoi2(5, 4);
	boxnoi2(5, 6);
	boxnoi3(118, 4);
	boxnoi3(118, 6);
	boxnoi4(13, 6);
	boxnoi4(41, 6);
	boxnoi4(104, 6);
	gotoxy(7, 5); std::cout << "INDEX";
	gotoxy(18, 5); std::cout << "Social Security ID";
	gotoxy(66, 5); std::cout << "Passenger Name";
	gotoxy(110, 5); std::cout << "Sex";
}