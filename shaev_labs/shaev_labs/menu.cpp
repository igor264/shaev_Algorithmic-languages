#include <iostream>

#include "structurs.h"

using std::cout;
using std::cin;

void Clear();
void add_pipeline();


unsigned short int start_menu()
{
	unsigned short int menu_choice;
	while (true) {
		cout << "Menu\n" << "Select menu item\n";
		cout << "1 - add pipe\n";
		cout << "2 - add CS\n";
		cout << "3 - view all objects\n";
		cout << "4 - edit pipe\n";
		cout << "5 - edit CS\n";
		cout << "6 - save\n";
		cout << "0 - exit\n";
		cout << "--------------------------------------------------------------------\n";

		unsigned short int menu_choice;
		cin >> menu_choice;

		while (menu_choice < 0 && menu_choice > 6) {
			cout << "" << "Select correct item from menu:\n";
			cin >> menu_choice;
		};

		switch (menu_choice)
		{
		case 1: add_pipeline();
		case 2: 2;
		case 3: 3;
		case 4: 4;
		case 5: 5;
		case 6: 6;
		case 0: return 0;
		}
	}
	return menu_choice;

};


void add_pipeline() {
	Clear();
	Pipeline mypipline;
	unsigned int kilometer_sign;
	unsigned int length_of_pipe;
	unsigned short int diameter;
	bool repair_indicator;
	cout << "enter the kilometer sign of your pipeline: ";
	cin >> kilometer_sign;
	cout << "enter the length of pipeline (metrs): ";
	cin >> length_of_pipe;
	cout << "enter the diameter of pipeline (millimetrs): ";
	cin >> diameter;
	cout << "Is it working or on repairing?\ntrue if it is in work, false if it is on repairing: ";
	cin >> repair_indicator;
	cout << "ok!";
};

void Clear()
{
	// взято с https://stackoverflow.com/questions/6486289/how-can-i-clear-console
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

