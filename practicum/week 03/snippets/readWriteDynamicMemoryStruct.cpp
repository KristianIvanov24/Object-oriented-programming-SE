#include <fstream>
#include <iostream>

struct A
{
	int* arr = nullptr;
	int size = 0;
};

int main()
{
	// пример за писане на структура с динамична памет в двоичен файл
	{
		A a;
		a.arr = new int[10];
		a.size = 10;

		for (int i = 0; i < a.size; i++)
		{
			a.arr[i] = i;
		}

		std::ofstream out("file.bin", std::ios::binary);
		if (!out.is_open())
		{
			std::cout << "Error opening file" << std::endl;
			return 1;
		}

		out.write((const char*)(&a.size), sizeof(a.size));
		out.write((const char*)(a.arr), sizeof(int) * a.size);

		delete[] a.arr;
		out.close();
	}

	// пример за четене на структура с динамична памет от двоичен файл
	{
		A b;
		std::ifstream in("file.bin", std::ios::binary);
		if (!in.is_open())
		{
			std::cout << "Error opening file" << std::endl;
			return 1;
		}

		in.read((char*)(&b.size), sizeof(b.size));
		b.arr = new int[b.size];
		in.read((char*)(b.arr), sizeof(int) * b.size);

		for (int i = 0; i < b.size; i++)
		{
			std::cout << b.arr[i] << std::endl;
		}

		delete[] b.arr;
		in.close();
	}
}
