#include "Ship.h"
#include "Navy.h"
#include <iostream>
#include "NavyHtmlTableGenerator.h"

using std::endl;
using std::cout;
using std::cin;

int main() {
	char name[] = "Name1";
	Ship ship(name,10,classShip::bb,10);
	Ship ship2;

	ship.printShip();
	ship2 = ship;

	ship2.printShip();

	Ship ship3(ship2);

	ship3.printShip();

	cout<<endl;

	cout<<ship3.getAge();
	char name1[] = "Name2";

	cout << endl << endl;
	ship3.setCountWeapons(1);
	ship3.setClass(classShip::bc);
	ship3.setAge(1);
	ship3.setShipName(name1);

	ship3.printShip();
	
	cout << endl << endl << endl << endl;

	Navy navy;

	navy.setNavyName("Navy");
	cout << navy.getNavyName();

	navy.addShip(ship);
	navy.addShip(ship3);
	navy.addShip(ship2);
	cout << endl << endl << endl << endl;


	navy.printNavy();

	Navy navy2;
	navy2 = navy;
	navy2.setNavyName("Navy2");
	cout << endl << endl << endl << endl;
	navy2.printNavy();

	Navy navy3(navy2);
	navy3.setNavyName("Navy3");
	cout << endl << endl << endl << endl;
	navy3.printNavy();

	cout << endl << endl << endl << endl;

	navy.printNavy();
	cout << endl << endl << endl << endl;

	navy.removeShip("Name34");
	navy.printNavy();

	//cout << navy.getShipsSize();


	cout << navy.compareGuns(navy3);

	NavyHtmlTableGenerator html(navy3,"Html.txt");

	

	return 0;
}