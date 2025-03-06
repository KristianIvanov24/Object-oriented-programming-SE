#include <fstream>
#include <iostream>

struct A
{
	int x[3]{ 1,2,3 };
	int y = 17;
	char z = 'z';
};

int main()
{
	{
		// пример за писане на масив от структури във файл
		A a[3];

		std::ofstream file("data.bin", std::ios::binary);
		if (!file)
		{
			std::cerr << "Error opening file\n";
			return 1;
		}

		file.write((const char*)a, sizeof(a));
		file.close();
	}

	{
		// пример за четене на масив от структури от файл
		A b[3];

		std::ifstream file2("data.bin", std::ios::binary);
		if (!file2)
		{
			std::cerr << "Error opening file\n";
			return 1;
		}

		file2.read((char*)b, sizeof(b));
		file2.close();
	}
}
