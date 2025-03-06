#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr int BUFFER_SIZE = 1024;
	constexpr int MESSAGE_MAX_SIZE = 1024;
	constexpr int TYPE_MAX_SIZE = 7;
	constexpr int COMMAND_MAX_SIZE = 11;
}

namespace FILE_DATA
{
	const char* fileName = "logs.bin";
	const char* positionFile = "last_read_position.bin";
}

void saveLog(std::ofstream& outFile)
{
	char type[CONSTANTS::TYPE_MAX_SIZE + 1]{};
	char message[CONSTANTS::MESSAGE_MAX_SIZE]{};

	std::cin >> type;
	std::cin.ignore();
	std::cin.getline(message, CONSTANTS::MESSAGE_MAX_SIZE);

	size_t typeSize = strlen(type) + 1;
	outFile.write((const char*)&typeSize, sizeof(size_t));
	outFile.write((const char*)type, typeSize);

	size_t messageSize = strlen(message) + 1;
	outFile.write((const char*)&messageSize, sizeof(size_t));
	outFile.write((const char*)message, messageSize);

	outFile.flush();
}

size_t readPos(std::fstream& logFile)
{
	char buff[CONSTANTS::BUFFER_SIZE]{};
	logFile.read(buff, strlen(FILE_DATA::fileName) + 1);

	size_t atLine = 0;
	logFile.read((char*)&atLine, sizeof(size_t));
	logFile.seekg(0, std::ios::beg);

	return atLine;
}

void savePos(std::fstream& logFile, size_t atLine)
{
	logFile.write(FILE_DATA::fileName, strlen(FILE_DATA::fileName) + 1);
	logFile.write((const char*)&atLine, sizeof(size_t));
	logFile.flush();
	logFile.seekg(0, std::ios::beg);
}

void showErrors(std::ifstream& inFile, size_t atLine)
{
	size_t curr = 0;
	while (!inFile.eof())
	{
		char type[CONSTANTS::TYPE_MAX_SIZE + 1]{};
		size_t typeSize = 0;
		inFile.read((char*)&typeSize, sizeof(size_t));
		inFile.read(type, typeSize);

		char message[CONSTANTS::MESSAGE_MAX_SIZE]{};
		size_t messageSize = 0;
		inFile.read((char*)&messageSize, sizeof(size_t));
		inFile.read(message, messageSize);

		if (std::strcmp("[ERROR]", type) == 0 && curr >= atLine)
		{
			std::cout << type << " " << message << std::endl;
		}
		
		curr++;
	}

	inFile.clear();
	inFile.seekg(0, std::ios::beg);
}

int main()
{
	//std::ofstream logFile2(FILE_DATA::positionFile, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
	//logFile2.close();

	std::ofstream outFile(FILE_DATA::fileName, std::ios::binary | std::ios::app | std::ios::out);
	std::ifstream inFile(FILE_DATA::fileName, std::ios::binary | std::ios::in);
	std::fstream logFile(FILE_DATA::positionFile, std::ios::binary | std::ios::in | std::ios::out);

	//savePos(logFile, 0);

	if (!inFile.is_open() || !outFile.is_open() || !logFile.is_open())
	{
		return -1;
	}

	size_t atLine = readPos(logFile);
	size_t newAtLine = atLine;

	while (true)
	{

		char command[CONSTANTS::COMMAND_MAX_SIZE + 1]{};
		std::cin >> command;
		std::cin.ignore();
		

		if (std::strcmp(command, "input") == 0)
		{
			saveLog(outFile);
			newAtLine++;
		}

		else if (std::strcmp(command, "show_errors") == 0)
		{
			showErrors(inFile, atLine);
		}

		else
		{
			savePos(logFile, newAtLine);

			inFile.close();
			outFile.close();
			logFile.close();
			break;
		}

	}
	
	return 0;
}