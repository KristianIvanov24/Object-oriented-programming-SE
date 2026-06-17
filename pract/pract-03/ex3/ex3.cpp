#include <iostream>
#include <fstream>

namespace constants
{
	const size_t FILE_NAME_MAX_SIZE = 100;
	const size_t FILE_MAX_SIZE_CONTENT = 10000;
}

size_t getFileSize(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		std::cout << "File cannot be openned" << std::endl;
		return 0;
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.close();

	return fileSize;
}

int main()
{
	char fileName[constants::FILE_NAME_MAX_SIZE];
	std::cin >> fileName;

	size_t halfSize = getFileSize(fileName) / 2;

	std::ifstream fileIn(fileName);

	char fileContent[constants::FILE_MAX_SIZE_CONTENT];
	size_t size = 0;

	while (size < halfSize && fileIn.get(fileContent[size])) 
	{
		size++;
	}
	fileIn.close();


	std::ofstream fileOut(fileName, std::ios::trunc);
	for (int i = 0; i < size; i++) 
	{
		fileOut << fileContent[i];
	}
	fileOut.close();

    return 0;
}