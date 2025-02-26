//#include <iostream>
//#include <fstream>
//
//void saveDataToFile(std::ofstream& outFile, int a, int b, int (*pred) (int, int))
//{
//	outFile << pred(a, b) << " ";
//}
//
//void saveResultsTo(std::ifstream& inFile, std::ofstream& outFile)
//{
//	int a = 0, b = 0;
//	inFile >> a >> b;
//
//	saveDataToFile(outFile, a, b, [](int a, int b) -> int {return a + b; });
//	saveDataToFile(outFile, a, b, [](int a, int b) -> int {return a * b; });
//}
//
//void saveResultsTo(const char* from, const char* to)
//{
//	if (!from || !to)
//	{
//		return;
//	}
//
//	std::ifstream inFile(from);
//	std::ofstream outFile(to);
//
//	if (!inFile.is_open() || !outFile.is_open())
//	{
//		return;
//	}
//
//	saveResultsTo(inFile, outFile);
//	
//	inFile.close();
//	outFile.close();
//}
//
//int main()
//{
//	std::ofstream outFile("read.txt");
//	outFile << 1 << " " << 3 << std::endl;
//	outFile.close();
//
//	saveResultsTo("read.txt", "write.txt");
//
//	return 0;
//}