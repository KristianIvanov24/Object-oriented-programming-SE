#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning (disable : 4996)

struct DataRecord
{
    uint64_t next = 0;
    char user_data[504]{};
};


void printDataRecord(const DataRecord& record)
{
    std::cout << record.next << ' ' << record.user_data << std::endl;
}


void iterateRecords(std::ifstream& ifs)
{
    uint64_t currIdx = 0;

    while (true)
    {
        ifs.seekg(0, std::ios::beg);
        ifs.seekg(currIdx * sizeof(DataRecord), std::ios::beg);
        
        DataRecord record;

        ifs.read((char*)&record, sizeof(DataRecord));

        printDataRecord(record);

        currIdx = record.next;

        if (currIdx == 0)
        {
            break;
        }
    }
}

void readRecords(const char* filePath)
{
    if (!filePath)
    {
        return;
    }

    std::ifstream ifs(filePath, std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    iterateRecords(ifs);

    ifs.close();
}

int main()
{
    readRecords("maintasks.db");
    return 0;
}
