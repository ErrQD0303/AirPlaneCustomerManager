#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "MyLib.h"
#include "Time.h"
#include <conio.h>
#include "PlaneTypeManager.h"

using namespace std;

void MainMenu() {
	airCraftList* AC = new airCraftList();
	readAirCraftFile(AC);
main_menu:
	showCur(0);
	flushConsoleInputBuffer();
	system("cls");
	menuCurTime();
	char menu_option[9][100] = {
	"1) Quan ly May bay ",
	"2) Quan ly chuyen bay ",
	"3) Quan ly Hanh khach ",
	"4) Dat Ve va Huy ve ",
	"5) Thong ke danh sach chuyen bay ",
	"6) Danh sach cac ve con trong theo ma ",
	"7) in chuyen bay theo ngay ",
	"8) Thong ke va sap xep cac luot thuc hien cua chuyen bay ",
	"9) Thoat khoi phan mem "
	};
	gotoxy(20, 1); cout << "    \_____  .__      __________.__                           ";
	gotoxy(20, 2); cout << "   \/  _  \\ |__|_____\\______   \\  | _____    ____   ____     ";
	gotoxy(20, 3); cout << "  \/  /_\\  \\|  \\_  __ \\     ___/  | \\__  \\  /    \\_/ __ \\    ";
	gotoxy(20, 4); cout << " \/    |    \\  ||  | \\/    |   |  |__/ __ \\|   |  \\  ___/    ";
	gotoxy(20, 5); cout << " \\____|__  /__||__|  |____|   |____(____  /___|  /\\___  >   ";
	gotoxy(20, 6); cout << "         \\/                             \\/     \\/     \\/    ";
	gotoxy(40, 7); cout << "          \_____                                             ";
	gotoxy(40, 8); cout << "         \/     \\ _____    ____ _____     ____   ___________ ";
	gotoxy(40, 9); cout << "        \/  \\ /  \\\__   \\  /     \\\__  \\   / ___\\_/ __ \\_  __ \\ ";
	gotoxy(40, 10);cout << "       \/    Y    \\/ __ \\|   |  \\/ __ \\_/ /_/  >  ___/|  | \\/";
	gotoxy(40, 11);cout << "       \\____|__  (____  /___|  (____  /\\___  / \\___  >__|   ";
	gotoxy(40, 12);cout << "               \\/     \\/     \\/     \\//_____/      \\/       ";
	gotoxy(90, 1); cout << "_________      _______";
	gotoxy(90, 2); cout << "\\_____   \\     \\   _  \\";
	gotoxy(90, 3); cout << " /   ____/     /  /_\\  \\";
	gotoxy(90, 4); cout << "/        \\     \\  \\_/   \\";
	gotoxy(90, 5); cout << "\\_______  \\ / \\ \\_____  /";
	gotoxy(90, 6); cout << "        \\ / \\ /       \\/";
//	   _____  .__      __________.__                           
//	  /  _  \ |__|_____\______   \  | _____    ____   ____     
//	 /  /_\  \|  \_  __ \     ___/  | \__  \  /    \_/ __ \    
//	/    |    \  ||  | \/    |   |  |__/ __ \|   |  \  ___/    
//	\____|__  /__||__|  |____|   |____(____  /___|  /\___  >   
//			\/                             \/     \/     \/    
//			 _____                                             
//			/     \ _____    ____ _____     ____   ___________ 
//		   /  \ /  \\__  \  /    \\__  \   / ___\_/ __ \_  __ \ 
//		  /    Y    \/ __ \|   |  \/ __ \_/ /_/  >  ___/|  | \/
//		  \____|__  (____  /___|  (____  /\___  / \___  >__|   
//				  \/     \/     \/     \//_____/      \/       
// 
	 //   _________      _______
		//\_____   \     \   _  \
		// /   ____/     /  /_\  \
		///        \     \  \_ /  \
		//\_______  \ / \ \_____  /
		//        \ / \ /       \/
	gotoxy(15, 17); cout << "Chon cac muc duoi: " << endl;
	gotoxy(30, 18); cout << "     ==>" << menu_option[0] << endl;
	gotoxy(30, 19); cout << "        " << menu_option[1] << endl;
	gotoxy(30, 20); cout << "        " << menu_option[2] << endl;
	gotoxy(30, 21); cout << "        " << menu_option[3] << endl;
	gotoxy(30, 22); cout << "        " << menu_option[4] << endl;
	gotoxy(30, 23); cout << "        " << menu_option[5] << endl;
	gotoxy(30, 24); cout << "        " << menu_option[6] << endl;
	gotoxy(30, 25); cout << "        " << menu_option[7] << endl;
	gotoxy(30, 26); cout << "        " << menu_option[8] << endl;
	gotoxy(96, 29);
	cout << right << "Author: Nguyen Quoc Dat";
	int key = 1;
	int i = 18;
	char inputChar;
	do {
		inputChar = _getch();
		if (inputChar == 72) {
			if (key > 1) {
				key--;
				i--;
			}
			else if (key == 1) {
				key = 9;
				i = 26;
			}
		}
		else if (inputChar == 80) {
			if (key < 9) {
				key++;
				i++;
			}
			else if (key == 9) {
				key = 1;
				i = 18;
			}
		}
		if (key != 1) {
			gotoxy(30, i - 1);
			cout << "        ";
			cout << menu_option[key - 2];
		}
		else {
			gotoxy(30, i + 8);
			cout << "        ";
			cout << menu_option[key + 7];
		}
		if (key != 9) {
			gotoxy(30, i + 1);
			cout << "        ";
			cout << menu_option[key];
		}
		else {
			gotoxy(30, i - 8);
			cout << "        ";
			cout << menu_option[key - 9];
		}
		gotoxy(30, i);
		cout << "      ==>";
		cout << menu_option[key - 1];
		cout << "       ";
	} while (inputChar != 13);
	switch (key) {
	case 1: {
		PMMainInterface(AC);
		break;
	}
	case 2: {

		break;
	}
	case 9:
		delete AC;
		AC = nullptr;
		return;
	}
	goto main_menu;
}