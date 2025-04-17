#include <iostream>
#include "Browser.h"
#include <iostream>

int main() 
{
	Webpage w1;
	Webpage w2;
	Webpage w3("https://github.com/KristianIvanov24", "12.345.255.0");

	std::cin >> w1;
	std::cin >> w2;

	std::cout << w1 << std::endl << w2 << std::endl << w3 << std::endl;
	
	Webpage pages[3];
	pages[0] = w1;
	pages[1] = w2;
	pages[2] = w3;

	Browser browser(pages, 3);

	Browser browser2;
	browser2 = browser;
	browser -= 1;

	std::cout << browser;

}