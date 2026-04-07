#include <iostream>
#include <fstream>

namespace constants
{
	const size_t FILE_NAME_MAX_SIZE = 100;
	const size_t LINE_MAX_SIZE = 1024;
}

int main()
{
	
	char fileName[constants::FILE_NAME_MAX_SIZE];
	std::cin >> fileName;

	std::ifstream file(fileName);

	if (!file.is_open()) 
	{
		std::cout << "File cannot be openned" << std::endl;
		return -1;
	}

	char line[constants::LINE_MAX_SIZE];
	while(file.getline(line, constants::LINE_MAX_SIZE)) 
	{
		std::cout << line << std::endl;
	}

	file.close();

    return 0;
}