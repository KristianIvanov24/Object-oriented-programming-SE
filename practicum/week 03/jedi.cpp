#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

namespace Constansts
{
	constexpr size_t MAX_JEDI_NAME = 50;
	constexpr size_t MAX_JEDI_COUNT = 100;
	constexpr size_t COLORS_COUNT = 5;
	constexpr size_t TYPES_COUNT = 3;
}

enum class Color
{
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE
};

enum class Type
{
	SINGLEBLADED,
	DOUBLE_BLADED,
	CROSSGUARD
};

struct LightSaber
{
	Color color;
	Type type;
};

struct Jedi
{
	char name[Constansts::MAX_JEDI_NAME + 1]{};
	unsigned age = 0;
	unsigned power = 0;
	LightSaber saber;
};

struct JediCollection
{
	Jedi jediArr[Constansts::MAX_JEDI_COUNT]{};
	size_t count = 0;
};

LightSaber createLightSaber(Color color, Type type)
{
	return { color, type };
}

Jedi createJedi(const char* name, unsigned age, unsigned power, const LightSaber& saber)
{
	if (!name)
	{
		return {};
	}

	Jedi jedi;
	strcpy(jedi.name, name);
	jedi.age = age;
	jedi.power = power;
	jedi.saber = saber;

	return jedi;
}

Jedi createJedi(const char* name, unsigned age, unsigned power, Color color, Type type)
{
	if (!name)
	{
		return {};
	}

	return createJedi(name, age, power, createLightSaber(color, type));
}

void addJedi(JediCollection& collection, const Jedi& jedi)
{
	if (collection.count == Constansts::MAX_JEDI_COUNT)
	{
		return;
	}

	collection.jediArr[collection.count++] = jedi;
}

int findJediIdx(const JediCollection& collection, const char* name)
{
	if (!name)
	{
		return -1;
	}

	for (size_t i = 0; i < collection.count; i++)
	{
		if (!strcmp(name, collection.jediArr[i].name))
		{
			return i;
		}
	}

	return -1;
}

void removeJedi(JediCollection& collection, const char* name)
{
	if (!name)
	{
		return;
	}

	int idx = findJediIdx(collection, name);

	if (idx == -1)
	{
		return;
	}

	std::swap(collection.jediArr[idx], collection.jediArr[collection.count - 1]);
	collection.count--;
}

const char* getColorStr(Color color)
{
	switch (color)
	{
	case Color::RED: return "Red";
	case Color::YELLOW: return "Yellow";
	case Color::BLUE: return "Blue";
	case Color::GREEN: return "Green";
	case Color::PURPLE: return "Purple";
	}

	return "Unknown";
}

const char* getTypeStr(Type type)
{
	switch (type)
	{
	case Type::SINGLEBLADED: return "Singlebladed";
	case Type::DOUBLE_BLADED: return "Double-bladed";
	case Type::CROSSGUARD: return "Crossguard";
	}

	return "Unknown";
}

void printLightSaber(const LightSaber& saber)
{
	std::cout << "LightSaber: " << getColorStr(saber.color) << ' ' << getTypeStr(saber.type);
}

void printJedi(const Jedi& jedi)
{
	std::cout << jedi.name << ' ' << jedi.age << ' ' << jedi.power << ' ';
	printLightSaber(jedi.saber);
}

void printJediCollection(const JediCollection& collection)
{
	for (size_t i = 0; i < collection.count; i++)
	{
		printJedi(collection.jediArr[i]);
		std::cout << std::endl;

	}
}

void saveJediToTxt(std::ofstream& ofs, const Jedi& jedi)
{
	ofs << jedi.name << ',' << jedi.age << ',' << jedi.power << ',' << (int)jedi.saber.color << ',' << (int)jedi.saber.type;
}

void saveCollectionToTxt(std::ofstream& ofs, const JediCollection& collection)
{
	ofs << collection.count << std::endl;

	for (size_t i = 0; i < collection.count; i++)
	{
		saveJediToTxt(ofs, collection.jediArr[i]);


		if (i != collection.count - 1)
		{
			ofs << '\n';
		}
	}
}

void saveCollectionToTxt(const char* fileName, const JediCollection& collection)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		return;
	}

	saveCollectionToTxt(ofs, collection);

	ofs.close();
}

Jedi readJediFromTxt(std::ifstream& ifs)
{
	Jedi jedi;

	ifs.getline(jedi.name, Constansts::MAX_JEDI_NAME + 1, ',');
	ifs >> jedi.age;
	ifs.ignore();
	ifs >> jedi.power;
	ifs.ignore();

	int color, type;
	ifs >> color;
	ifs.ignore();
	ifs >> type;

	jedi.saber = createLightSaber((Color)color, (Type)type);

	return jedi;


}

JediCollection readCollectionFromTxt(std::ifstream& ifs)
{
	JediCollection collection;

	ifs >> collection.count;
	ifs.ignore();

	for (int i = 0; i < collection.count; i++)
	{
		collection.jediArr[i] = readJediFromTxt(ifs);
		ifs.ignore();
	}

	return collection;
}

JediCollection readCollectionFromTxt(const char* fileName)
{
	if (!fileName)
	{
		return {};
	}

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		return {};
	}

	JediCollection collection = readCollectionFromTxt(ifs);

	ifs.close();

	return collection;
}

Color mostPopularSaberColor(const JediCollection& collection)
{
	int colorsCounter[Constansts::COLORS_COUNT]{};

	for (size_t i = 0; i < collection.count; i++)
	{
		int currColor = (int)collection.jediArr[i].saber.color;
		colorsCounter[currColor]++;
	}

	int maxColor = 0;

	for (size_t i = 0; i < Constansts::COLORS_COUNT; i++)
	{
		if (colorsCounter[i] > colorsCounter[maxColor])
		{
			maxColor = i;
		}
	}

	return (Color)maxColor;
}

Type mostPopularSaberType(const JediCollection& collection)
{
	int typesCounter[Constansts::TYPES_COUNT]{};

	for (size_t i = 0; i < collection.count; i++)
	{
		int currColor = (int)collection.jediArr[i].saber.type;
		typesCounter[currColor]++;
	}

	int maxType = 0;

	for (size_t i = 0; i < Constansts::TYPES_COUNT; i++)
	{
		if (typesCounter[i] > typesCounter[maxType])
		{
			maxType = i;
		}
	}

	return (Type)maxType;
}

void saveCollectionToBinary(const char* fileName, const JediCollection& collection)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	ofs.write((const char*)&collection, sizeof(collection));

	ofs.close();
}

JediCollection readCollectionFromBinary(const char* fileName)
{
	if (!fileName)
	{
		return {};
	}

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		return {};
	}

	JediCollection collection;

	ifs.read((char*)&collection, sizeof(collection));

	return collection;
}

void sortByCriteria(JediCollection& collection, bool (*criteria)(const Jedi& lhs, const Jedi& rhs))
{
	if (!criteria)
	{
		return;
	}

	for (size_t i = 0; i < collection.count - 1; i++)
	{
		size_t idx = i;

		for (size_t j = i + 1; j < collection.count; j++)
		{
			if (criteria(collection.jediArr[j], collection.jediArr[idx]))
			{
				idx = j;
			}
		}

		if (idx != i)
		{
			std::swap(collection.jediArr[idx], collection.jediArr[i]);
		}
	}
}

void sortByAge(JediCollection& collection)
{
	sortByCriteria(collection, [](const Jedi& lhs, const Jedi& rhs) -> bool {return lhs.age < rhs.age; });
}

void sortByPower(JediCollection& collection)
{
	sortByCriteria(collection, [](const Jedi& lhs, const Jedi& rhs) -> bool {return lhs.power < rhs.power; });
}

int main()
{
	JediCollection collection;
	addJedi(collection, createJedi("Jedi1", 40, 60, createLightSaber(Color::RED, Type::CROSSGUARD)));
	addJedi(collection, createJedi("Jedi2", 25, 45, createLightSaber(Color::BLUE, Type::CROSSGUARD)));
	addJedi(collection, createJedi("Jedi3", 35, 55, createLightSaber(Color::RED, Type::CROSSGUARD)));
	printJediCollection(collection);

	saveCollectionToBinary("jedi.dat", collection);

	JediCollection collection2 = readCollectionFromBinary("jedi.dat");
	printJediCollection(collection2);

	std::cout << std::endl;
	std::cout << (mostPopularSaberColor(collection2) == Color::RED);
	std::cout << (mostPopularSaberType(collection2) == Type::CROSSGUARD);
	return 0;
}
