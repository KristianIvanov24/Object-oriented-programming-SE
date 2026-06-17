#include <iostream>
#include "MulString.h"

int main() {
    MulString s1("ABC");
    MulString s2("ABCDEFABJ");
    MulString s3("BCDGHJ");


    s1 *= 3;
    std::cout << "s1 *= 3 : " << s1 << "\n";


    MulString s4 = MulString("XY") * 4;
    std::cout << "XY * 4  : " << s4 << "\n";


    MulString a("AB"), b("BA");
    std::cout << "AB != BA : " << (a != b ? "true" : "false") << "\n";
    MulString c("ABC");
    std::cout << "AB != ABC: " << (a != c ? "true" : "false") << "\n";


    MulString uni = s2 % s3;
    std::cout << "ABCDEFABJ % BCDGHJ : " << uni << "\n"; 


    MulString s5("HELLO");
    s5 %= MulString("WORLD");
    std::cout << "HELLO %%= WORLD    : " << s5 << "\n"; 

    return 0;
}