//#include <iostream>
//#include <fstream>
//
//namespace CONSTANTS
//{
//	constexpr int NUMS_MAX_SIZE = 20;
//}
//
//void readNums(std::ifstream& inFile, int* arr, size_t& size)
//{
//	while (!inFile.eof())
//	{
//		inFile >> arr[size++];
//	}
//}
//
//void readNums(const char* fileName, int* arr, size_t& size)
//{
//	if (!fileName)
//	{
//		return;
//	}
//
//	std::ifstream inFile(fileName);
//	if (!inFile.is_open())
//	{
//		return;
//	}
//
//	readNums(inFile, arr, size);
//}
//
//void saveDataToFile(std::ofstream& outFile, int* arr, size_t size, bool (*criteria) (int))
//{
//	for (int i = 0; i < size; i++)
//	{
//		if (criteria(arr[i]))
//		{
//			outFile << arr[i];
//
//			if (i != size - 1)
//			{
//				outFile << " ";
//			}
//		}
//	}
//}
//
//void saveDataToFile(const char* fileName, int* arr, size_t size, bool (*criteria) (int))
//{
//	if (!fileName)
//	{
//		return;
//	}
//
//	std::ofstream outFile(fileName);
//	if (!outFile.is_open())
//	{
//		return;
//	}
//
//	saveDataToFile(outFile, arr, size, criteria);
//	outFile.close();
//}
//
//int main()
//{
//	std::ofstream outFile("nums.txt");
//	outFile << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5;
//	outFile.close();
//
//	int arr[CONSTANTS::NUMS_MAX_SIZE]{};
//	size_t size = 0;
//	const char* fileName = "nums.txt";
//	readNums(fileName, arr, size);
//
//	const char* odd = "odd.txt";
//	saveDataToFile(odd, arr, size, [](int x) -> bool {return x % 2 != 0; });
//
//	const char* even = "even.txt";
//	saveDataToFile(even, arr, size, [](int x) -> bool {return x % 2 == 0; });
//
//	return 0;
//}