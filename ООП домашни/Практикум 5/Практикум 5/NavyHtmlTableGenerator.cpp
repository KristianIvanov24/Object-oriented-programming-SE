#include "NavyHtmlTableGenerator.h"
#include <cstring>
#include <iostream>
#pragma warning (disable:4996)

NavyHtmlTableGenerator::NavyHtmlTableGenerator(const char* fileName, const Navy& navy)
{
	if (!fileName)
		return;

	strcpy(this->fileName, fileName);
	this->navy = navy;
}

/*
<table>
  <tr>
    <th>Name</th>
    <th>Launch Year</th>
    <th>Class</th>
    <th>NumGuns</th>
  </tr>
  <tr>
    <td>Ship 1 Name</td>
    <td>Ship 1 Launch Year</td>
    <td>Ship 1 Class</td>
    <td>Ship 1 NumGuns</td>
  </tr>
  ...
    <td>Ship N Name</td>
    <td>Ship N Launch Year</td>
    <td>Ship N Class</td>
    <td>Ship N NumGuns</td>
</table>
*/

void NavyHtmlTableGenerator::printTableHeader(std::ofstream& ofs) const
{
    if (!ofs.is_open())
        return;

    ofs << "<tr>" << '\n';

    ofs << '\t' << "<th>Name</th>" << '\n';
    ofs << '\t' << "<th>Launch Year</th>" << '\n';
    ofs << '\t' << "<th>Class</th>" << '\n';
    ofs << '\t' << "<th>NumGuns</th>" << '\n';

    ofs << "</tr>" << '\n';

}

void NavyHtmlTableGenerator::printTableRow(std::ofstream& ofs, const Ship& ship) const
{
    if (!ofs.is_open())
        return;

    ofs << "<tr>" << '\n';

    ofs << '\t' << "<td>" << ship.getName() << "</td>" << '\n';
    ofs << '\t' << "<td>" << ship.getLaunchYear() << "</td>" << '\n';
    ofs << '\t' << "<td>" << ship.getCaliberAsString() << "</td>" << '\n';
    ofs << '\t' << "<td>" << ship.getGunCount() << "</td>" << '\n';

    ofs << "</tr>" << '\n';
}

void NavyHtmlTableGenerator::saveToHtmlTable() const
{
    std::ofstream ofs(fileName);
    if (!ofs.is_open())
    {
        std::cout << "Error opening the file\n";
        return;
    }

    ofs << "<table>" << '\n';
    printTableHeader(ofs);

    size_t shipCount = navy.getShipCount();
    for (size_t current = 0; current < shipCount; current++)
    {
        printTableRow(ofs, navy.getShips()[current]);
    }

    ofs << "</table>";

    ofs.close();
}