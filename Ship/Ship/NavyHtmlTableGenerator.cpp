#include "NavyHtmlTableGenerator.h"
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

using std::endl;

void NavyHtmlTableGenerator::saveShip(std::ofstream& ofs, int i) const {
	ofs << "<tr>" << endl;
	ofs << "<td>" << navy.getShip(i)->getShipName() << "</td>" << endl;
	ofs << "<td>" << navy.getShip(i)->getAge() << "</td>" << endl;
	ofs << "<td>" << navy.getShip(i)->getCountWeapons() << "</td>" << endl;
	ofs << "</tr>" << endl;
}

void NavyHtmlTableGenerator::saveToFile()const{
	std::ofstream ofs(this->fileName);

	ofs << "<table>";
	ofs << endl;
	ofs << "<tr>" << endl;
	ofs << "<th>" << navy.getNavyName() << "</th>" << endl;
	ofs << "</tr>" << endl;

	for (int i = 0; i < this->navy.getShipsSize(); i++) {
		saveShip(ofs, i);
	}
	ofs << "</table>";
	ofs.close();

}

NavyHtmlTableGenerator::NavyHtmlTableGenerator(const Navy& navy, const char* fileName) {
	this->navy = navy;
	if (!fileName) {
		strcpy(this->fileName, "No name.txt");
		return;
	}
	strcpy(this->fileName, fileName);

	this->saveToFile();
}