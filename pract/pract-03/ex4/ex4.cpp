#include <iostream>
#include <fstream>

namespace constants
{
	const size_t FILE_NAME_MAX_SIZE = 100;
	const size_t LINE_MAX_SIZE = 1024;
	const char SPACE = ' ';
}

int getNewRowsCountInFile(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		std::cout << "File cannot be openned" << std::endl;
		return -1;
	}

	int count = 0;
	char line[constants::LINE_MAX_SIZE];

	while (file.getline(line, constants::LINE_MAX_SIZE)) 
	{
		count++;
	}

	file.close();
	return count;
}

int getWordsCountInLine(const char* line)
{
	if(!line) 
	{
		std::cout << "Line cannot be nullptr" << std::endl;
		return -1;
	}

	int count = 0;
	while(*line) 
	{
		while (*line && *line == constants::SPACE) 
		{
			line++;
		}
		if (*line) 
		{
			count++;
			while (*line && *line != constants::SPACE) 
			{
				line++;
			}
		}
	}

	return count;
}

int getWordsCountInFile(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		std::cout << "File cannot be openned" << std::endl;
		return -1;
	}

	int count = 0;
	char line[constants::LINE_MAX_SIZE];

	while (file.getline(line, constants::LINE_MAX_SIZE)) 
	{
		count += getWordsCountInLine(line);
	}

	file.close();
	return count;
}

int getBytesCountInFile(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) 
	{
		std::cout << "File cannot be openned" << std::endl;
		return -1;
	}

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();

	file.close();
	return fileSize;
}

int main()
{
	char fileName[constants::FILE_NAME_MAX_SIZE];
	std::cin >> fileName;

	std::cout << "Lines: " << getNewRowsCountInFile(fileName) << std::endl;
	std::cout << "Words: " << getWordsCountInFile(fileName) << std::endl;
	std::cout << "Bytes: " << getBytesCountInFile(fileName) << std::endl;

    return 0;
}
