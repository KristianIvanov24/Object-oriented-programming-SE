#pragma once
#include "Constants.h"
#include "Navy.h"
#include <fstream>

class NavyHtmlTableGenerator
{
private:
	char fileName[Constants::MAX_TABLE_FILE_NAME_SIZE + 1]{};
	Navy navy;

	void printTableHeader(std::ofstream&) const;
	void printTableRow(std::ofstream&, const Ship&) const;
public:
	NavyHtmlTableGenerator(const char*, const Navy&);
	void saveToHtmlTable() const;
};

