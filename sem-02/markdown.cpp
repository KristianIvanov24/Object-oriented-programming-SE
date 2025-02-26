#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr int NAME_MAX_SIZE = 50;
	constexpr int FN_MAX_SIZE = 10;
	constexpr int ROWS_MAX_SIZE = 300;
	constexpr int BUFFER_SIZE = 1024;
	constexpr int FILE_NAME_MAX_SIZE = 128;
	constexpr int COMMAND_MAX_SIZE = 100;
}

struct Name
{
	char firstName[CONSTANTS::NAME_MAX_SIZE + 1]{};
	char lastName[CONSTANTS::NAME_MAX_SIZE + 1]{};
};

struct MarkdownRow
{
	Name name;
	char fn[CONSTANTS::FN_MAX_SIZE + 1]{};
	double grade = 0.0;
};

struct MarkdownTable
{
	MarkdownRow rows[CONSTANTS::ROWS_MAX_SIZE]{};
	size_t rowsSize = 0;
};

int getRowIdx(const MarkdownTable& table, const char* targetFn)
{
	for (size_t i = 0; i < table.rowsSize; i++)
	{
		if (strcmp(table.rows[i].fn, targetFn) == 0)
		{
			return i;
		}
	}

	return -1;
}

void getInfoOf(const MarkdownTable& table, const char* targetFn)
{
	int rowIdx = getRowIdx(table, targetFn);

	if (rowIdx == -1)
	{
		std::cerr << "[ERROR] Student not found." << std::endl;
		return;
	}

	std::cout << "Name: " << table.rows[rowIdx].name.firstName << " " <<table.rows[rowIdx].name.lastName << ", "
			  << "Faculty Number: " << table.rows[rowIdx].fn << ", "
			  << "Grade: " << table.rows[rowIdx].grade << std::endl;
}

void changeGrade(MarkdownTable& table, const char* targetFn, double grade)
{
	int rowIdx = getRowIdx(table, targetFn);

	if (rowIdx == -1)
	{
		std::cerr << "[ERROR] Student not found." << std::endl;
		return;
	}

	table.rows[rowIdx].grade = grade;
}

void saveRow(const MarkdownRow& row, std::ofstream& outFile)
{
	outFile << "| " << row.name.firstName
		<< " " << row.name.lastName
		<< " | " << row.fn
		<< " | " << row.grade
		<< " |";
}

void saveTable(const MarkdownTable& table, std::ofstream& outFile)
{
	outFile << "| Name | Faculty Number | Grade |" << std::endl;
	outFile << "| ------ | ---------------- | ------- |" << std::endl;

	for (size_t i = 0; i < table.rowsSize; i++)
	{
		saveRow(table.rows[i], outFile);
		
		if (i != table.rowsSize - 1)
		{
			outFile<< std::endl;
		}
	}
}
void saveTable(const MarkdownTable& table, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	saveTable(table, outFile);
	outFile.close();
}

MarkdownRow readRow(std::ifstream& inFile)
{
	MarkdownRow row;

	inFile.ignore(); // '|'
	inFile.ignore(); // ' '

	inFile >> row.name.firstName;
	
	inFile.ignore();
	inFile >> row.name.lastName;
	
	inFile.ignore(); // ' '
	inFile.ignore(); // '|'
	inFile.ignore(); // ' '

	inFile >> row.fn;

	inFile.ignore(); // ' '
	inFile.ignore(); // '|'
	inFile.ignore(); // ' '

	inFile >> row.grade;
	
	inFile.ignore(); // ' '
	inFile.ignore(); // '|'

	return row;
}

MarkdownTable readTable(std::ifstream& inFile)
{
	char buff[CONSTANTS::BUFFER_SIZE]{};
	inFile.getline(buff, CONSTANTS::BUFFER_SIZE);
	inFile.getline(buff, CONSTANTS::BUFFER_SIZE);
		
	MarkdownTable table;
	while (!inFile.eof())
	{
		table.rows[table.rowsSize++] = readRow(inFile);
		inFile.ignore();
	}

	std::cout << table.rowsSize << std::endl;

	return table;
}

MarkdownTable readTable(const char* fileName)
{
	if (!fileName)
	{
		std::cerr << "[ERROR] File cannot be opened!" << std::endl;
		return {};
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		std::cerr << "[ERROR] File cannot be opened!" << std::endl;
		return {};
	}

	std::cout << "File successfully opened!" << std::endl;
	
	MarkdownTable table = readTable(inFile);
	inFile.close();

	return table;
}

int main()
{	
	std::cout << "Open file: " << std::endl;
	
	char fileName[CONSTANTS::FILE_NAME_MAX_SIZE]{};
	std::cin.getline(fileName, CONSTANTS::FILE_NAME_MAX_SIZE);
	
	MarkdownTable table = readTable(fileName);
	if (table.rowsSize == 0)
	{
		std::cerr << "[ERROR] Table is empty." << std::endl;
		return -1;
	}

	while (true)
	{
		char command[CONSTANTS::COMMAND_MAX_SIZE]{};
		std::cin >> command;

		if (strcmp(command, "print") == 0)
		{
			char fn[CONSTANTS::FN_MAX_SIZE]{};
			std::cin >> fn;

			getInfoOf(table, fn);
		}

		else if (strcmp(command, "add_grade") == 0)
		{
			char fn[CONSTANTS::FN_MAX_SIZE]{};
			std::cin >> fn;

			double grade = 0.0;
			std::cin >> grade;

			changeGrade(table, fn, grade);
		}

		else
		{
			saveTable(table, fileName);
			std::cout << "File " << fileName <<" was saved successfully!" << std::endl;
			return 0;
		}
	}

	return 0;
}