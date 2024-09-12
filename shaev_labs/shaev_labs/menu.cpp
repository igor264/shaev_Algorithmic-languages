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

short int start_menu();
void Clear();
void add_pipeline();
void add_cs();
void out_to_file(Pipeline new_pipeline);
void out_to_file(CS new_cs);
void view_objects();
std::vector<string> get_values(const string& filename);
void edit_pipeline();
void edit_cs();

short int start_menu()
{
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

		while (!(cin >> menu_choice) || (menu_choice < 0 || menu_choice > 5)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item from menu:\n";
		};

		switch (menu_choice)
		{
		case 1: add_pipeline(); break;
		case 2: add_cs(); break;
		case 3: view_objects();
		case 4: edit_pipeline();
		case 5: edit_cs();
		case 0: return 0;
		}
	}

	return 0;
};


void add_pipeline() 
{
	Clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string kilometer_sign;
	int length_of_pipe;
	short int diameter;
	bool repair_indicator;

	cout << "Enter the kilometer sign of your pipeline: ";
	std::getline(cin, kilometer_sign);

	cout << "Enter the length of pipeline (meters): ";
	while (!(cin >> length_of_pipe) || length_of_pipe < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid length: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the diameter of pipeline (millimeters): ";
	while (!(cin >> diameter) || diameter < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid diameter: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
	while (!(cin >> repair_indicator)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter '1' for working or '0' for under repair: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Pipeline new_pipeline{ kilometer_sign, length_of_pipe, diameter, repair_indicator };
	cout << "ok!"<<std::endl;
	out_to_file(new_pipeline);
};

void add_cs() 
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Clear();

	string name;
	int number_of_workshops;
	int workshops_in_work;
	short int efficiency;

	cout << "Enter the name of your cs: ";
	std::getline(cin, name);

	cout << "Enter the number of workshops of cs: ";
	while (!(cin >> number_of_workshops) || number_of_workshops < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid number of workshops: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the workshops in work: ";
	while (!(cin >> workshops_in_work) || workshops_in_work > number_of_workshops || workshops_in_work < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter a valid number: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Enter the efficiency (0-100): ";
	while (!(cin >> efficiency) || efficiency > 100 || efficiency < 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter efficiency (1-100): ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	CS new_cs{ name, number_of_workshops, workshops_in_work, efficiency };
	cout << "ok!" << std::endl;
	out_to_file(new_cs);

	start_menu();
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

void view_objects() 
{
	Clear();

	std::string line;
	std::ifstream file_pipeline("pipelines.txt");
	if (file_pipeline.is_open() && !(file_pipeline.peek() == EOF))
	{
		cout << "pipeline:\n";
		cout << "kilometer sign\t" << "length of pipe\t" << "diameter\t" << "repair indicator\t" << std::endl;
		while (std::getline(file_pipeline, line)) {
			cout << line << "\n";
		}
		file_pipeline.close();
	}
	else { cout << "file pipelines.txt is empty or not find\n"; };


	std::ifstream file_cs("cs.txt");
	if (file_cs.is_open() && !(file_cs.peek() == EOF))
	{
		cout << "cs:\n";
		cout << "name  " << "number of workshops  " << "workshops in work  " << "efficiency" << std::endl;
		while (std::getline(file_cs, line)) {
			cout << line << "\n";
		}
		file_cs.close();
	}
	else { cout << "file cs.txt is empty or not find\n"; };
	start_menu();
};

std::vector<string> get_values(const string& filename) {
	std::vector<string> values;
	std::ifstream file(filename);

	if (file.is_open()) {
		string line;
		if (std::getline(file, line)) {  // Считываем строку из файла
			size_t pos = 0;
			string token;
			string delimiter = "\t\t";

			// Пока есть разделитель в строке
			while ((pos = line.find(delimiter)) != string::npos) {
				token = line.substr(0, pos);  // Извлекаем подстроку до разделителя
				values.push_back(token);  // Добавляем её в вектор
				line.erase(0, pos + delimiter.length());  // Удаляем обработанную часть строки
			}

			// Добавляем оставшуюся часть строки после последнего разделителя
			values.push_back(line);
		}
		file.close();
	}

	return values;
};

void edit_pipeline()
{
	Clear();

	std::vector<std::string> pipeline_values = get_values("pipelines.txt");

	if (pipeline_values.size() != 4) 
	{
		cout << "Invalid data in the file.\n";
		return;
	}

	string kilometer_sign = pipeline_values[0];
	int length_of_pipe = std::stoi(pipeline_values[1]);
	short int diameter = std::stoi(pipeline_values[2]);
	bool repair_indicator = std::stoi(pipeline_values[3]);

	cout << "Current pipeline details:\n";
	cout << "Kilometer sign: " << kilometer_sign << "\n";
	cout << "Length: " << length_of_pipe << "\n";
	cout << "Diameter: " << diameter << "\n";
	cout << "Repair indicator (1 - working, 0 - under repair): " << repair_indicator << "\n";

	bool new_repair_indicator;
	cout << "Enter new repair indicator (1 - working, 0 - under repair): ";
	while (!(cin >> new_repair_indicator)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter '1' for working or '0' for under repair: ";
	}

	Pipeline updated_pipeline{ kilometer_sign, length_of_pipe, diameter, new_repair_indicator };

	out_to_file(updated_pipeline);
	cout << "Pipeline updated successfully!\n";
	start_menu();
}

void edit_cs()
{
	Clear();

	std::vector<std::string> cs_values = get_values("cs.txt");

	if (cs_values.size() != 4)
	{
		cout << "Invalid data in the file.\n";
		return;
	}

	string name = cs_values[0];
	int number_of_workshops = std::stoi(cs_values[1]);
	int workshops_in_work = std::stoi(cs_values[2]);
	short int efficiency = std::stoi(cs_values[3]);

	cout << "cs details:\n";
	cout << "Name: " << name << "\n";
	cout << "number of workshops: " << number_of_workshops << "\n";
	cout << "workshops in work: " << workshops_in_work << "\n";
	cout << "efficiency (from 1 to 100): " << efficiency << "\n";

	int new_workshops_in_work;
	cout << "Enter new workshops in work: ";
	while (!(cin >> new_workshops_in_work) || (new_workshops_in_work < 0) || (new_workshops_in_work > number_of_workshops)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error. Please enter correct valid data: ";
	}

	CS updated_cs{ name, number_of_workshops, new_workshops_in_work, efficiency };

	out_to_file(updated_cs);
	cout << "cs updated successfully!\n";
	start_menu();
}