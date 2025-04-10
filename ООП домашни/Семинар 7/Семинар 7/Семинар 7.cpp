#include <iostream>
#include "MulString.h"

int main()
{
	MyString str1("ABCDEFABJ");
	MyString str2("BCDGHJ");

	MulString multi1(str1);
	MulString multi2(str2);

	std::cout << multi1 % multi2;

}