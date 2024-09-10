#include <iostream>
#include <fstream>
#include <string>

#include "structurs.h"

using std::cout;
using std::cin;

void Clear();
void add_pipeline();
void out_to_file(Pipeline new_pipeline);
void view_pipelines();

unsigned short int start_menu()
{
	unsigned short int menu_choice;
	while (true) {
		cout << "Menu\n" << "Select menu item\n";
		cout << "1 - add pipeline\n";
		cout << "2 - add CS\n";
		cout << "3 - view all pipelines\n";
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
		case 2: 2;
		case 3: view_pipelines();
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
	cout << "enter the kilometer sign of your pipeline: ";
	cin >> kilometer_sign;
	cout << "enter the length of pipeline (metrs): ";
	cin >> length_of_pipe;
	cout << "enter the diameter of pipeline (millimetrs): ";
	cin >> diameter;
	cout << "Is it working or on repairing?\ntrue if it is in work, false if it is on repairing: ";
	cin >> repair_indicator;
	Pipeline new_pipeline{ kilometer_sign, length_of_pipe, diameter, repair_indicator };
	cout << "ok!"<<std::endl;
	out_to_file(new_pipeline);
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
	std::ofstream out("pipelines.txt", std::ios::app);
	if (out.is_open())
	{
		out << new_pipeline.kilometer_sign << "\t\t" << new_pipeline.length_of_pipe << "\t\t" << new_pipeline.diameter << "\t\t" << new_pipeline.repair_indicator << std::endl;
		out.close();
	}
};

void view_pipelines() {
	std::string line;
	std::ifstream file("pipelines.txt");
	if (file.is_open()) {
		unsigned short int number_of_line = 1;
		cout << "number\tkilometer sign\t" << "length of pipe\t" << "diameter\t" << "repair indicator\t" << std::endl;
		while (std::getline(file, line)) {
			cout << number_of_line << "\t" << line << "\n";
			number_of_line++;
		}
		file.close();
	}
};
