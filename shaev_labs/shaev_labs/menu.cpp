#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <vector>
#include <sstream>

#include "structurs.h"

using std::cout;
using std::cin;
using std::string;

short int start_menu(Pipeline& my_pipeline, CS& my_cs);
void Clear();
void add_pipeline(Pipeline &my_pipline);
void add_cs(CS &my_cs);
void out_to_file(Pipeline &new_pipeline, CS& new_cs);
void view_objects(Pipeline& my_pipeline, CS& my_cs);
void get_values(const string& filename, Pipeline& my_pipeline, CS& my_cs);
void edit_pipeline(Pipeline& my_pipeline);
void edit_cs(CS& my_cs);
void menu();

void menu()
{
	Pipeline my_pipeline;
	CS my_cs;

	start_menu(my_pipeline, my_cs);
};

short int start_menu(Pipeline& my_pipeline, CS& my_cs)
{
	while (true) {

		cout << "Menu\n" << "Select menu item\n";
		cout << "1 - add pipeline\n";
		cout << "2 - add CS\n";
		cout << "3 - view all objects\n";
		cout << "4 - edit pipe\n";
		cout << "5 - edit CS\n";
		cout << "6 - save in file\n";
		cout << "7 - download from file\n";
		cout << "0 - exit\n";
		cout << "--------------------------------------------------------------------\n";

		unsigned short int menu_choice;

		while (!(cin >> menu_choice) || (menu_choice < 0 || menu_choice > 7)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item from menu:\n";
		};

		switch (menu_choice)
		{
		case 1: add_pipeline(my_pipeline); break;
		case 2: add_cs(my_cs); break;
		case 3: view_objects(my_pipeline, my_cs); break;
		case 4: edit_pipeline(my_pipeline); break;
		case 5: edit_cs(my_cs); break;
		case 6: out_to_file(my_pipeline, my_cs); break;
		case 7: get_values("save.txt", my_pipeline, my_cs); break;
		case 0: return 0;
		}
	}

	return 0;
};


void add_pipeline(Pipeline &my_pipeline) 
{
	Clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the kilometer sign of your pipeline: ";
	std::getline(cin, my_pipeline.kilometer_sign);

	cout << "Enter the length of pipeline (meters): ";
	while (!(cin >> my_pipeline.length_of_pipe) || my_pipeline.length_of_pipe < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid length: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the diameter of pipeline (millimeters): ";
	while (!(cin >> my_pipeline.diameter) || my_pipeline.diameter < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid diameter: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
	while (!(cin >> my_pipeline.repair_indicator)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter '1' for working or '0' for under repair: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "ok!"<<std::endl;
};

void add_cs(CS &my_cs) 
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Clear();

	cout << "Enter the name of your cs: ";
	std::getline(cin, my_cs.name);

	cout << "Enter the number of workshops of cs: ";
	while (!(cin >> my_cs.number_of_workshops) || my_cs.number_of_workshops < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid number of workshops: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the workshops in work: ";
	while (!(cin >> my_cs.workshops_in_work) || my_cs.workshops_in_work > my_cs.number_of_workshops || my_cs.workshops_in_work < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid number: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the efficiency (0-100): ";
	while (!(cin >> my_cs.efficiency) || my_cs.efficiency > 100 || my_cs.efficiency < 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter efficiency (1-100): ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "ok!" << std::endl;
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

void out_to_file(Pipeline &my_pipeline, CS &my_cs)
{
	Clear();
	std::ofstream out("save.txt"/*, std::ios::app*/);// для добавления в конец
	if (!(out.is_open())) { cout << "error file"; return; }
	else { out.close(); }
	if (my_pipeline.kilometer_sign != "default" && my_cs.name != "default")
	{
		std::ofstream out("save.txt");
		out << "@pipeline@" << "%%" << my_pipeline.kilometer_sign << "%%" << my_pipeline.length_of_pipe << "%%" << my_pipeline.diameter << "%%" << my_pipeline.repair_indicator << std::endl;
		out << "@cs@" << "%%" << my_cs.name << "%%" << my_cs.number_of_workshops << "%%" << my_cs.workshops_in_work << "%%" << my_cs.efficiency << std::endl;
		out.close();
	}
	else if (my_pipeline.kilometer_sign != "default")
	{
		std::ofstream out("save.txt");
		out << "@pipeline@" << "%%" << my_pipeline.kilometer_sign << "%%" << my_pipeline.length_of_pipe << "%%" << my_pipeline.diameter << "%%" << my_pipeline.repair_indicator << std::endl;
		out.close();
	}
	else if (my_cs.name != "default")
	{
		std::ofstream out("save.txt");
		out << "@cs@" << "%%" << my_cs.name << "%%" << my_cs.number_of_workshops << "%%" << my_cs.workshops_in_work << "%%" << my_cs.efficiency << std::endl; 
		out.close();
	}
	else 
	{
		cout << "add cs or pipeline\n";
	}
};

void view_objects(Pipeline &my_pipeline, CS &my_cs) 
{
	Clear();
	if (my_pipeline.kilometer_sign != "default")
	{
		cout << "pipeline:\n";
		cout << "kilometer sign: " << my_pipeline.kilometer_sign << "\nlength of pipe: " << my_pipeline.length_of_pipe << "\ndiameter: " << my_pipeline.diameter << "\nrepair indicator: " << my_pipeline.repair_indicator<< std::endl;
	}
	else { cout << "add pipeline or download from file\n"; };

	if (my_cs.name != "default")
	{
		cout << "cs:\n";
		cout << "name: " << my_cs.name << "\nnumber of workshops: " << my_cs.number_of_workshops << "\nworkshops in work: " << my_cs.workshops_in_work<< "\nefficiency: " << my_cs.efficiency << std::endl;
	}
	else { cout << "add cs or download from file\n"; };
};

void get_values(const std::string& filename, Pipeline& my_pipeline, CS& my_cs)
{
	std::ifstream file(filename);

	if (file.is_open()) {
		std::string line;
		std::string delimiter = "%%";

		while (std::getline(file, line)) {
			std::vector<std::string> values;
			size_t pos = 0;
			std::string token;

			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				values.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			values.push_back(line);
			if (values[0] == "@pipeline@") 
			{
				my_pipeline.kilometer_sign = values[1];
				my_pipeline.length_of_pipe = std::stoi(values[2]);
				my_pipeline.diameter = std::stoi(values[3]);
				my_pipeline.repair_indicator = std::stoi(values[4]);
			}
			else if (values[0] == "@cs@")
			{
				my_cs.name = values[1];
				my_cs.number_of_workshops = std::stoi(values[2]);
				my_cs.workshops_in_work = std::stoi(values[3]);
				my_cs.efficiency = std::stoi(values[4]);
			}
		}
		file.close();
		Clear();
	}
}

void edit_pipeline(Pipeline& my_pipeline)
{
	if (my_pipeline.kilometer_sign != "default")
	{
		cout << "pipeline:\n";
		cout << "kilometer sign: " << my_pipeline.kilometer_sign << "\nlength of pipe: " << my_pipeline.length_of_pipe << "\ndiameter: " << my_pipeline.diameter << "\nrepair indicator: " << my_pipeline.repair_indicator << std::endl;
		cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
		while (!(cin >> my_pipeline.repair_indicator)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Error. Please enter '1' for working or '0' for under repair: ";
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "ok!" << std::endl;
	}
	else { cout << "add pipeline or download from file\n"; };

	Clear();
}

void edit_cs(CS& my_cs)
{
	if (my_cs.name != "default")
	{
		cout << "cs:\n";
		cout << "name: " << my_cs.name << "\nnumber of workshops: " << my_cs.number_of_workshops << "\nworkshops in work: " << my_cs.workshops_in_work << "\nefficiency: " << my_cs.efficiency << std::endl;
		cout << "Enter the workshops in work: ";
		while (!(cin >> my_cs.workshops_in_work) || my_cs.workshops_in_work > my_cs.number_of_workshops || my_cs.workshops_in_work < 0) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Error. Please enter a valid number: ";
		};
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "ok!" << std::endl;
	}
	else { cout << "add cs or download from file\n"; };

	Clear();
}
