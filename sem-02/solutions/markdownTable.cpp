#include <iostream>
#include <fstream>
#include <cstring>

namespace Constants
{
	constexpr size_t MAX_NAME_SIZE = 50;
	constexpr size_t MAX_FN_SIZE = 10;
	constexpr size_t MAX_ROWS_COUNT = 50;
	constexpr size_t BUFFER_CAPACITY = 1024;
	constexpr char SEPARATOR = '|';
}

struct MarkdownRow
{
	char name[Constants::MAX_NAME_SIZE + 1]{};
	char fn[Constants::MAX_FN_SIZE + 1]{};
	double grade = 0;
};

struct MarkdownTable
{
	MarkdownRow rows[Constants::MAX_ROWS_COUNT]{};
	size_t size = 0;
};

size_t findRowByFN(const MarkdownTable& table, const char* fn)
{
	if (!fn)
	{
		return table.size;
	}

	for (size_t i = 0; i < table.size; i++)
	{
		if (!strcmp(fn, table.rows[i].fn))
		{
			return i;
		}
	}

	return table.size;
}

void printRow(const MarkdownRow& row)
{
	std::cout << "Name : " << row.name << ", FN : " << row.fn << ", Grade : " << row.grade << std::endl;
}

void printRow(const MarkdownTable& table, const char* fn)
{
	if (!fn)
	{
		std::cout << "Invalid data!" << std::endl;
		return;
	}

	size_t idx = findRowByFN(table, fn);

	if (idx == table.size)
	{
		std::cout << "No such student found!" << std::endl;
		return;
	}

	printRow(table.rows[idx]);
}

void updateGrade(MarkdownTable& table, const char* fn, double grade)
{
	if (!fn)
	{
		std::cout << "Invalid data!" << std::endl;
		return;
	}

	size_t idx = findRowByFN(table, fn);

	if (idx == table.size)
	{
		std::cout << "No such student found!" << std::endl;
		return;
	}

	table.rows[idx].grade = grade;
}

void saveHeadings(std::ofstream& ofs)
{
	ofs << "| Name | Faculty Number | Grade |" << std::endl;
	ofs << "|------|----------------|-------|" << std::endl;
}

void saveRow(std::ofstream& ofs, const MarkdownRow& row)
{
	ofs << "| " << row.name << " | " << row.fn << " | " << row.grade << " |";
}

void saveTable(std::ofstream& ofs, const MarkdownTable& table)
{
	saveHeadings(ofs);

	for (size_t i = 0; i < table.size; i++)
	{
		saveRow(ofs, table.rows[i]);

		if (i != table.size - 1)
		{
			ofs << std::endl;
		}
	}
}

void saveTable(const char* filePath, const MarkdownTable& table)
{
	if (!filePath)
	{
		std::cout << "Invalid data!" << std::endl;
		return;
	}

	std::ofstream ofs(filePath);

	if (!ofs.is_open())
	{
		std::cout << "File cannot open!" << std::endl;
		return;
	}

	saveTable(ofs, table);

	ofs.close();
}

void trimString(const char* src, char* dest)
{
	// Can be improved...

	size_t len = strlen(src);

	size_t from = 0;
	size_t to = len - 1;

	for (size_t i = 0; i < len; i++)
	{
		if (src[i] == ' ')
		{
			from++;
		}
		else
		{
			break;
		}
	}

	for (int i = len - 1; i >= 0; i--)
	{
		if (src[i] == ' ')
		{
			to--;
		}
		else
		{
			break;
		}
	}

	for (size_t i = from; i <= to; i++)
	{
		*dest = src[i];
		dest++;
	}
}

MarkdownRow readRow(std::ifstream& ifs)
{
	MarkdownRow row;

	ifs.ignore();

	char nameBuff[Constants::BUFFER_CAPACITY]{};
	ifs.getline(nameBuff, Constants::BUFFER_CAPACITY, Constants::SEPARATOR);
	trimString(nameBuff, row.name); // In case the string is surrounded by multiple spaces in the cell

	char fnBuff[Constants::BUFFER_CAPACITY]{};
	ifs.getline(fnBuff, Constants::BUFFER_CAPACITY, Constants::SEPARATOR);
	trimString(fnBuff, row.fn);

	ifs >> row.grade;
	ifs.ignore(Constants::BUFFER_CAPACITY, Constants::SEPARATOR);

	return row;
}

MarkdownTable readTable(std::ifstream& ifs)
{
	MarkdownTable table;

	char buff[Constants::BUFFER_CAPACITY];

	// Skip the headings
	ifs.getline(buff, Constants::BUFFER_CAPACITY);
	ifs.getline(buff, Constants::BUFFER_CAPACITY);

	while (!ifs.eof())
	{
		table.rows[table.size++] = readRow(ifs);
		ifs.ignore();
	}

	ifs.clear();

	return table;
}

MarkdownTable readTable(const char* filePath)
{
	if (!filePath)
	{
		std::cout << "Invalid data!" << std::endl;
		return {};
	}

	std::ifstream ifs(filePath);

	if (!ifs.is_open())
	{
		std::cout << "File cannot open!" << std::endl;
		return {};
	}

	MarkdownTable table = readTable(ifs);

	ifs.close();

	return table;
}

void run()
{
	std::cout << "Enter file name: ";
	char fileName[Constants::BUFFER_CAPACITY]{};
	std::cin >> fileName;

	MarkdownTable table = readTable(fileName);

	while (true)
	{
		char option[Constants::BUFFER_CAPACITY]{};
		std::cout << '>';
		std::cin >> option;

		if (!strcmp(option, "print"))
		{
			char fn[Constants::BUFFER_CAPACITY]{};
			std::cin >> fn;

			printRow(table, fn);
			std::cout << std::endl;
		}
		else if (!strcmp(option, "update_grade"))
		{
			char fn[Constants::BUFFER_CAPACITY]{};
			std::cin >> fn;

			double grade = 0;
			std::cin >> grade;

			updateGrade(table, fn, grade);
			std::cout << std::endl;
		}
		else if (!strcmp(option, "save"))
		{
			saveTable(fileName, table);
		}
		else if (!strcmp(option, "quit"))
		{
			break;
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
}

int main()
{
	run();

	return 0;
}
