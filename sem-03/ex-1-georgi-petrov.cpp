#pragma warning (disable : 4996)

#include <cstring>
#include <fstream>
#include <iostream>

namespace constants
{
	const size_t INPUT_BUFFER_SIZE = 512;

	const char* const LOGS_FILENAME = "log.bin";
	const char* const LAST_ERROR_FILENAME = "last_read_position.bin";

	const char* const ERROR_PREFIX = "[ERROR]";
	const char* const INFO_PREFIX = "[INFO]";

	const char* const LIST_ERRORS_COMMAND = "show_errors";
	const char* const WRITE_LOGS_COMMAND = "input";
}

namespace logger
{
	bool isErrorPerfix(const char* const prefix)
	{
		if (!prefix)
		{
			return false;
		}

		return !strcmp(prefix, constants::ERROR_PREFIX);
	}

	bool isInfoPrefix(const char* const prefix)
	{
		if (!prefix)
		{
			return false;
		}

		return !strcmp(prefix, constants::INFO_PREFIX);
	}

	void truncateFile(const char* const filename)
	{
		if (!filename)
		{
			return;
		}

		std::ofstream file(filename, std::ios::binary | std::ofstream::trunc);
		if (!file.is_open())
		{
			return;
		}

		file.close();
	}

	size_t getFileSize(std::ifstream& file)
	{
		size_t startPos = file.tellg();

		file.seekg(0, std::ios::end);
		size_t fileSize = file.tellg();

		file.clear();
		file.seekg(startPos);
		return fileSize;
	}

	size_t getFileSize(const char* const filename)
	{
		if (!filename)
		{
			return 0;
		}

		std::ifstream file(filename);
		if (!file.is_open())
		{
			return 0;
		}

		return getFileSize(file);
	}

	size_t getLenToSymb(std::ifstream& file, char symb)
	{
		size_t startPos = file.tellg();

		size_t len = 0;
		while (true)
		{
			char currSymb = file.get();

			if (currSymb == symb || file.eof())
			{
				break;
			}

			len++;
		}

		file.clear();
		file.seekg(startPos);
		return len;
	}

	void saveErrorInfo(
		size_t errPos,
		const char* const logsFilename = constants::LOGS_FILENAME,
		const char* const infoFilename = constants::LAST_ERROR_FILENAME)
	{
		if (!logsFilename || !infoFilename)
		{
			return;
		}

		std::ofstream file(infoFilename, std::ios::binary);
		if (!file.is_open())
		{
			return;
		}

		size_t logsFilenameLen = strlen(logsFilename);
		file.write((const char*)&errPos, sizeof(size_t));
		file.write((const char*)&logsFilenameLen, sizeof(size_t));
		file.write(logsFilename, logsFilenameLen);

		file.close();
	}

	void saveLog(std::ofstream& file, const char* const prefix, const char* const message)
	{
		file.write(prefix, strlen(prefix));
		file.write(message, strlen(message));
		file.write("\n", 1);
	}

	bool saveLog(const char* const prefix, const char* const message, const char* const filename = constants::LOGS_FILENAME)
	{
		if (!prefix || !message || !filename)
		{
			return false;
		}

		size_t errStartPos = getFileSize(filename);

		std::ofstream file(filename, std::ios::binary | std::ios::app);
		if (!file.is_open())
		{
			return false;
		}

		saveLog(file, prefix, message);

		file.close();

		if (isErrorPerfix(prefix))
		{
			saveErrorInfo(errStartPos, filename);
		}

		return true;
	}

	char* readErrorInfo(std::ifstream& file, size_t& pos)
	{
		file.read((char*)&pos, sizeof(size_t));
		
		size_t logsFilenameLen = 0;
		file.read((char*)&logsFilenameLen, sizeof(size_t));

		char* logsFilename = new char[logsFilenameLen + 1] {};
		file.read(logsFilename, logsFilenameLen);

		return logsFilename;
	}

	char* readErrorInfo(size_t& pos, const char* const infoFilename = constants::LAST_ERROR_FILENAME)
	{
		if (!infoFilename)
		{
			return nullptr;
		}

		std::ifstream file(infoFilename, std::ios::binary);
		if (!file.is_open())
		{
			return nullptr;
		}

		char* logsFilename = readErrorInfo(file, pos);

		file.close();

		return logsFilename;
	}

	char* readErrorByInfo(const char* const infoFilename = constants::LAST_ERROR_FILENAME)
	{
		if (getFileSize(infoFilename) == 0 || !infoFilename)
		{
			return nullptr;
		}

		size_t pos = 0;
		char* logsFilename = readErrorInfo(pos, infoFilename);

		std::ifstream file(logsFilename, std::ios::binary);
		
		delete[] logsFilename;
		logsFilename = nullptr;
		
		if (!file.is_open())
		{
			return nullptr;
		}

		file.seekg(pos);
		size_t errLen = getLenToSymb(file, '\n');
		char* err = new char[errLen + 1] {};
		file.getline(err, errLen + 1);

		return err;
	}
}

int main()
{
	using namespace logger;

	bool logMode = false;

	while (true)
	{
		std::cout << ">" << (logMode ? "> " : " ");
		char command[constants::INPUT_BUFFER_SIZE] = {};
		char message[constants::INPUT_BUFFER_SIZE] = {};

		std::cin >> command;
		std::cin.getline(message, constants::INPUT_BUFFER_SIZE);

		if (!strcmp(command, constants::LIST_ERRORS_COMMAND))
		{
			logMode = false;

			char* lastError = readErrorByInfo();

			std::cout << (lastError ? lastError : "Nothing new to be shown.") << std::endl;

			delete[] lastError;
			lastError = nullptr;

			truncateFile(constants::LAST_ERROR_FILENAME);
		}
		else if (logMode)
		{
			if (!isInfoPrefix(command) && !isErrorPerfix(command))
			{
				std::cout << "Invalid log message! A log message needs to start with ";
				std::cout << constants::ERROR_PREFIX << " or " << constants::INFO_PREFIX << "!" << std::endl;
				std::cout << "Please try again!" << std::endl;

				continue;
			}

			bool isSaved = logger::saveLog(command, message);
			if (!isSaved)
			{
				std::cout << "There was an unexpected error when trying to write to the logs." << std::endl;
				std::cout << "Message has not been written! Please try again!" << std::endl;

				continue;
			}
		}
		else if (!strcmp(command, constants::WRITE_LOGS_COMMAND))
		{
			logMode = true;
		}
		else
		{
			std::cout << "Invalid command! Available commands are: ";
			std::cout << constants::LIST_ERRORS_COMMAND << " and ";
			std::cout << constants::WRITE_LOGS_COMMAND << std::endl;
		}
	}
}
