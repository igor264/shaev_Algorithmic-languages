#include <iostream>
#include <fstream>
#include <string>
#include <limits> 

#include "structurs.h"

using std::cout;
using std::cin;

void Clear();
void add_pipeline();
void add_cs();
void out_to_file(Pipeline new_pipeline);
void out_to_file(CS new_cs);
void view_objects();

unsigned short int start_menu()
{
	unsigned short int menu_choice;
	while (true) {
		cout << "Menu\n" << "Select menu item\n";
		cout << "1 - add pipeline\n";
		cout << "2 - add CS\n";
		cout << "3 - view all objects\n";
		cout << "4 - edit pipe\n";
		cout << "5 - edit CS\n";
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
		case 2: add_cs();
		case 3: view_objects();
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
	char kilometer_sign[30];
	unsigned int length_of_pipe;
	unsigned short int diameter;
	bool repair_indicator;
	cout << "Enter the kilometer sign of your pipeline: ";
	while (!(cin >> kilometer_sign)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid kilometer sign: ";
	}

	cout << "Enter the length of pipeline (meters): ";
	while (!(cin >> length_of_pipe)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid length: ";
	}

	cout << "Enter the diameter of pipeline (millimeters): ";
	while (!(cin >> diameter)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid diameter: ";
	}

	cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
	while (!(cin >> repair_indicator)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter '1' for working or '0' for under repair: ";
	}
	Pipeline new_pipeline{ kilometer_sign, length_of_pipe, diameter, repair_indicator };
	cout << "ok!"<<std::endl;
	out_to_file(new_pipeline);
};

void add_cs() {
	Clear();

	char name[30];
	unsigned int number_of_workshops;
	unsigned int workshops_in_work;
	unsigned short int efficiency;

	cout << "Enter the name of your cs: ";
	while (!(cin >> name)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid name: ";
	};

	cout << "Enter the number of workshops of cs: ";
	while (!(cin >> number_of_workshops)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid number of workshops: ";
	};

	cout << "Enter the workshops in work: ";
	while (!(cin >> workshops_in_work)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid number: ";
	};

	cout << "Enter the efficiency (1-100): ";
	while (!(cin >> efficiency)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input. Please enter efficiency (1-100): ";
	};

	CS new_cs{ name, number_of_workshops, workshops_in_work, efficiency };
	cout << "ok!" << std::endl;
	out_to_file(new_cs);
};

void Clear()
{
	// взято с https://stackoverflow.com/questions/6486289/how-can-i-clear-console
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || (__APPLE__)
	system("clear");
#endif
}

void out_to_file(Pipeline new_pipeline)
{
	std::ofstream out("pipelines.txt"/*, std::ios::app*/);// для добавления в конец
	if (out.is_open())
	{
		out << new_pipeline.kilometer_sign << "\t\t" << new_pipeline.length_of_pipe << "\t\t" << new_pipeline.diameter << "\t\t" << new_pipeline.repair_indicator << std::endl;
		out.close();
	}
};

void out_to_file(CS new_cs)
{
	std::ofstream out("cs.txt"/*, std::ios::app*/);// для добавления в конец
	if (out.is_open())
	{
		out << new_cs.name << "\t\t" << new_cs.number_of_workshops << "\t\t" << new_cs.workshops_in_work << "\t\t" << new_cs.efficiency << std::endl;
		out.close();
	}
};

void view_objects() {
	std::string line;
	std::ifstream file_pipeline("pipelines.txt");
	if (file_pipeline.is_open()) {
		cout << "pipeline:\n";
		cout << "kilometer sign\t" << "length of pipe\t" << "diameter\t" << "repair indicator\t" << std::endl;
		while (std::getline(file_pipeline, line)) {
			cout << line << "\n";
		}
		file_pipeline.close();
	}

	std::ifstream file_cs("cs.txt");
	if (file_cs.is_open()) {
		cout << "cs:\n";
		cout << "name  " << "number of workshops  " << "workshops in work  " << "efficiency" << std::endl;
		while (std::getline(file_cs, line)) {
			cout << line << "\n";
		}
		file_cs.close();
	}
};
