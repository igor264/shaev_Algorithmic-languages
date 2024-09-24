#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <sstream>

#include "structurs.h"

using std::cout;
using std::cin;
using std::string;

short int start_menu(Pipeline& my_pipeline, CS& my_cs);
void Clear();
void add_pipeline(Pipeline& my_pipline);
void add_cs(CS& my_cs);
void out_to_file(const Pipeline& new_pipeline, const CS& new_cs);
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


void add_pipeline(Pipeline& my_pipeline) 
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

void add_cs(CS& my_cs) 
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

void out_to_file(const Pipeline& my_pipeline, const CS& my_cs)
{
	Clear();
	if (my_pipeline.kilometer_sign != "default" || my_cs.name != "default")
	{
		std::ofstream out("save.txt");
		if (!(out.is_open())) {
			cout << "Error: Could not open file" << std::endl;
			return;
		}

		if (my_pipeline.kilometer_sign != "default") {
			out << "@pipeline@" << '\n'
				<< my_pipeline.kilometer_sign << '\n'
				<< my_pipeline.length_of_pipe << '\n'
				<< my_pipeline.diameter << '\n'
				<< my_pipeline.repair_indicator << '\n';
		}

		if (my_cs.name != "default") {
			out << "@cs@" << '\n'
				<< my_cs.name << '\n'
				<< my_cs.number_of_workshops << '\n'
				<< my_cs.workshops_in_work << '\n'
				<< my_cs.efficiency << '\n';
		}

		out.close();
	}
	else { cout << "add cs or pipeline\n"; }
}

void view_objects(Pipeline& my_pipeline, CS& my_cs) 
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

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;

		return;
	}

	if (file.peek() == std::ifstream::traits_type::eof()) {
		std::cerr << "Error: File " << filename << " is empty." << std::endl;
		file.close();
		return;
	}

	std::string line;
	bool pipeline_loaded = false;
	bool cs_loaded = false;

	while (std::getline(file, line)) {
		if (line == "@pipeline@") {
			std::getline(file, my_pipeline.kilometer_sign);
			if (my_pipeline.kilometer_sign.empty()) {
				std::cerr << "Error: Invalid pipeline kilometer sign in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.length_of_pipe) || my_pipeline.length_of_pipe <= 0) {
				std::cerr << "Error: Invalid pipeline length in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.diameter) || my_pipeline.diameter <= 0) {
				std::cerr << "Error: Invalid pipeline diameter in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.repair_indicator) || (my_pipeline.repair_indicator != 0 && my_pipeline.repair_indicator != 1)) {
				std::cerr << "Error: Invalid repair indicator in file. Must be 0 or 1." << std::endl;
				continue;
			}

			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			pipeline_loaded = true;
		}
		

		else if (line == "@cs@") {
			std::getline(file, my_cs.name);
			if (my_cs.name.empty()) {
				std::cerr << "Error: Invalid CS name in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.number_of_workshops) || my_cs.number_of_workshops <= 0) {
				std::cerr << "Error: Invalid number of workshops in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.workshops_in_work) || my_cs.workshops_in_work < 0 || my_cs.workshops_in_work > my_cs.number_of_workshops) {
				std::cerr << "Error: Invalid number of workshops in work in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.efficiency) || my_cs.efficiency < 0 || my_cs.efficiency > 100) {
				std::cerr << "Error: Invalid CS efficiency in file. Must be between 0 and 100." << std::endl;
				continue;
			}

			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cs_loaded = true;
		}

	}

	file.close();

	if (!pipeline_loaded)
	{
		my_pipeline.kilometer_sign = "default";
		my_pipeline.length_of_pipe = 1;
		my_pipeline.diameter = 1;
		my_pipeline.repair_indicator = 0;
	}
	if (!cs_loaded)
	{
		my_cs.name = "default";
		my_cs.number_of_workshops = -1;
		my_cs.workshops_in_work = -1;
		my_cs.efficiency = -1;
	}

	if (!pipeline_loaded && !cs_loaded) {
		std::cerr << "Error: No valid pipeline or CS data found in the file." << std::endl;
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
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
