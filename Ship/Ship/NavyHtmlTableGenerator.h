#pragma once
#include "Navy.h"
#define MAX_FILE_NAME 128
#include <fstream>


class NavyHtmlTableGenerator {

	Navy navy;
	char fileName[MAX_FILE_NAME + 1];


	void saveToFile()const;

	void saveShip(std::ofstream&, int)const;

public:

	NavyHtmlTableGenerator(const Navy& , const char*);

};
