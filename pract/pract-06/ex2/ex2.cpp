#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Navy.h"
#pragma warning(disable : 4996)

int main()
{

    std::srand(static_cast<unsigned int>(std::time(0)));
    Ship s1(1941, 9, ShipClass::bb); 
    Ship s2(1943, 40, ShipClass::bc); 
    Ship s3(2020, 2, ShipClass::bb);  

    Navy myNavy; 
    myNavy.addShip(s1);
    myNavy.addShip(s2);


    Navy allyNavy = myNavy;
    allyNavy.addShip(s3);

    Navy enemyNavy;
    enemyNavy = myNavy;

    std::cout << "ORIGINAL NAVY:" << std::endl;
    myNavy.printNavyInfo();

    std::cout << "\nALLY NAVY (Should have 1 extra ship):" << std::endl;
    allyNavy.printNavyInfo();

    std::cout << "\nComparing Ally Navy vs Original Navy power:" << std::endl;
    int result = allyNavy.compareGunsAmount(myNavy);
    if (result > 0) {
        std::cout << "Ally Navy is stronger!" << std::endl;
    }
    else if (result < 0) {
        std::cout << "Original Navy is stronger!" << std::endl;
    }
    else {
        std::cout << "It's a tie!" << std::endl;
    }

    return 0;
}
