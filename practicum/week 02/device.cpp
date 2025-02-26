#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

namespace CONSTANTS
{
	constexpr int NAME_MAX_SIZE = 32;
	constexpr int SUPPLIER_MAX_SIZE = 32;
	constexpr int DEVICES_MAX_SIZE = 100;
	constexpr int OWNER_NAME_MAX_SIZE = 32;
}

enum class DeviceType
{
	TV,
	SMARTPHONE,
	LAPTOP,
	PC,
	CAMERA,
	OTHER,
};

struct Device
{
	char name[CONSTANTS::NAME_MAX_SIZE]{};
	int quantity = 0;
	double price = 0.0;
	DeviceType type = DeviceType::OTHER;
	char supplier[CONSTANTS::SUPPLIER_MAX_SIZE]{};
};

struct Warehouse
{
	Device devices[CONSTANTS::DEVICES_MAX_SIZE]{};
	size_t devicesSize = 0;
	char ownerName[CONSTANTS::OWNER_NAME_MAX_SIZE]{};
};

Device createDevice(const char* name, int quantity, double price, DeviceType type, const char* supplier)
{
	if (!name || !supplier || price < 0 || quantity < 0)
	{
		return {};
	}

	Device device;

	strncpy(device.name, name, strlen(name));
	device.quantity = quantity;
	device.price = price;
	device.type = type;
	strncpy(device.supplier, supplier, strlen(supplier));
	
	return device;
}

Warehouse createWarehouse(const char* ownerName)
{
	if (!ownerName)
	{
		return {};
	}

	Warehouse wh;
	strncpy(wh.ownerName, ownerName, strlen(ownerName));
	return wh;
}

void addDeviceToWarehouse(const Device& device, Warehouse& wh)
{
	if (wh.devicesSize >= CONSTANTS::DEVICES_MAX_SIZE)
	{
		return;
	}

	wh.devices[wh.devicesSize++] = device;
}

void saveDeviceInFile(const Device& device, std::ofstream& outFile)
{
	outFile << device.name << std::endl
			<< device.quantity << std::endl
			<< device.price << std::endl
			<< int(device.type) << std::endl
			<< device.supplier << std::endl;
}

void saveDeviceInFile(const Device& device, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	saveDeviceInFile(device, outFile);
}

void saveWarehouseInFile(const Warehouse& wh, std::ofstream& outFile)
{
	outFile << wh.ownerName << std::endl;
	outFile << wh.devicesSize << std::endl;
	for (size_t i = 0; i < wh.devicesSize; i++)
	{
		saveDeviceInFile(wh.devices[i], outFile);
	}
}

void saveWarehouseInFile(const Warehouse& wh, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	saveWarehouseInFile(wh, outFile);
	outFile.close();
}

Device readDeviceFromFile(std::ifstream& inFile)
{
	Device device;

	inFile.getline(device.name, CONSTANTS::NAME_MAX_SIZE);
	inFile >> device.quantity;
	inFile >> device.price;
	
	int temp;
	inFile >> temp;
	device.type = DeviceType(temp);

	inFile.ignore();
	inFile.getline(device.supplier, CONSTANTS::SUPPLIER_MAX_SIZE);

	return device;
}

Device readDeviceFromFile(const char* fileName)
{
	if (!fileName)
	{
		return {};
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		return {};
	}

	Device device = readDeviceFromFile(inFile);
	inFile.close();
	return device;
}

Warehouse readWarehouseFromFile(std::ifstream& inFile)
{
	Warehouse wh;
	inFile >> wh.ownerName;
	inFile >> wh.devicesSize;
	inFile.ignore();

	size_t at = 0;
	for (size_t i = 0; i < wh.devicesSize; i++)
	{
		wh.devices[at++] = readDeviceFromFile(inFile);
		inFile.ignore();
	}

	return wh;
}

Warehouse readWarehouseFromFile(const char* fileName)
{
	if (!fileName)
	{
		return {};
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		return {};
	}

	Warehouse wh = readWarehouseFromFile(inFile);
	inFile.close();
	return wh;
}

void saveSpecificTypeInFile(const Warehouse& wh, DeviceType type, std::ofstream& outFile)
{
	outFile << wh.devicesSize << std::endl;
	for (size_t i = 0; i < wh.devicesSize; i++)
	{
		if ((int)wh.devices[i].type == (int)type)
		{
			saveDeviceInFile(wh.devices[i], outFile);
		}
	}
}

void saveSpecificTypeInFile(const Warehouse& wh, DeviceType type, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	saveSpecificTypeInFile(wh, type, outFile);
	outFile.close();
}

void sortDevicesByCriteria(Warehouse& wh, bool(*criteria)(const Device& lhs, const Device& rhs))
{
	for (size_t i = 0; i < wh.devicesSize - 1; i++)
	{
		size_t minIdx = i;
		for (size_t j = i + 1; j < wh.devicesSize; j++)
		{
			if (criteria(wh.devices[minIdx], wh.devices[j]))
			{
				minIdx = j;
			}
		}

		if (minIdx != i)
		{
			std::swap(wh.devices[minIdx], wh.devices[i]);
		}
	}
}

void sortDevicesByPrice(Warehouse& wh)
{
	sortDevicesByCriteria(wh, [](const Device& lhs, const Device& rhs) -> bool {return lhs.price > rhs.price; });
}

void sortDevicesByQuantity(Warehouse& wh)
{
	sortDevicesByCriteria(wh, [](const Device& lhs, const Device& rhs) -> bool {return lhs.quantity > rhs.quantity; });
}

Device getDeviceByCriteria(const Warehouse& wh, bool(*criteria)(const Device& lhs, const Device& rhs))
{
	Device device = wh.devices[0];
	for (size_t i = 1; i < wh.devicesSize; i++)
	{
		if (criteria(device, wh.devices[i]))
		{
			device = wh.devices[i];
		}
	}

	return device;
}

Device getMostExpensiveDevice(const Warehouse& wh)
{
	return getDeviceByCriteria(wh, [](const Device& lhs, const Device& rhs) -> bool {return lhs.price < rhs.price; });
}

Device getCheapestDevice(const Warehouse& wh)
{
	return getDeviceByCriteria(wh, [](const Device& lhs, const Device& rhs) -> bool {return lhs.price > rhs.price; });
}

const char* convertTypeToStr(DeviceType type)
{
	switch (type)
	{
		case DeviceType::TV:
			return "TV";
			break;
		case DeviceType::SMARTPHONE:
			return "Smartphone";
			break;
		case DeviceType::LAPTOP:
			return "Laptop";
			break;
		case DeviceType::PC:
			return "PC";
			break;
		case DeviceType::CAMERA:
			return "Camera";
			break;
		case DeviceType::OTHER:
			return "Other";
			break;
	}
}

void printDevice(const Device& device)
{
	std::cout << "----[Device] " << std::endl;
	std::cout << "        [Name] " << device.name << std::endl;
	std::cout << "        [Quantity] " << device.quantity << std::endl;
	std::cout << "        [Price] " << device.price << std::endl;
	std::cout << "        [Type] " << convertTypeToStr(device.type) << std::endl;
	std::cout << "        [Supplier] " << device.supplier << std::endl;
}

void printWarehouse(const Warehouse& wh)
{
	std::cout << "Warehouse of " << wh.ownerName << std::endl;
	for (size_t i = 0; i < wh.devicesSize; i++)
	{
		printDevice(wh.devices[i]);
	}
	std::cout << "--------------------------------" << std::endl;
}

int main()
{
	Device d1 = createDevice("ime1", 2.50, 3, DeviceType::CAMERA, "supplier1");
	Device d2 = createDevice("ime2", 10.50, 1, DeviceType::CAMERA, "supplier2");

	Warehouse wh1 = createWarehouse("wh1");
	addDeviceToWarehouse(d1, wh1);
	addDeviceToWarehouse(d2, wh1);

	saveWarehouseInFile(wh1, "wh1.txt");

	printWarehouse(wh1);

	Warehouse wh2 = readWarehouseFromFile("wh1.txt");
	printWarehouse(wh2);

	Warehouse wh3 = wh2;
	sortDevicesByQuantity(wh3);
	printWarehouse(wh3);
	sortDevicesByPrice(wh3);
	printWarehouse(wh3);

	Device dCheapest = getCheapestDevice(wh3);
	Device dMostExpensive = getMostExpensiveDevice(wh3);

	printDevice(dCheapest);
	printDevice(dMostExpensive);

	return 0;
}