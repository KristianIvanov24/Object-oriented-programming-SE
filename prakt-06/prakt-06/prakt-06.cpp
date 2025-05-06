#include <iostream>
#include "Browser.h"

int main()
{
    Browser br;
    Webpage page1, page2, page3;
    std::cout << "Type adress and ip for webpage 1: \n";
    std::cin >> page1;
    std::cout << "Type adress and ip for webpage 2: \n";
    std::cin >> page2;
    br.addPage(page1);
    br += page2;
    page3.setAdress("oop-sem"); 
    page3.setIp("12.32.11");
    br += page3;

    br.printOpenPages();

    Browser browser(br);
    browser.removePage(page2);

    browser.printOpenPages();
}
