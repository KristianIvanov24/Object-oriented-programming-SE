#include "Song.h"
#include <cstring>
#pragma warning (disable:4996)

void Song::free()
{
	delete[] name;
	delete[] artist;

	name = nullptr;
	artist = nullptr;
	duration = 0;
}

void Song::copyFrom(const Song& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	artist = new char[strlen(other.artist) + 1];
	strcpy(artist, other.artist);

	duration = other.duration;
}

Song::Song()
{
	name = nullptr;
	artist = nullptr;
	duration = 0;
}

Song::Song(const char* name, const char* artist, unsigned duration)
{
	setName(name);
	setArtist(artist);
	setDuration(duration);
}

Song::Song(const Song& other)
{
	copyFrom(other);
}

Song& Song::operator=(const Song& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Song::~Song()
{
	free();
}

void Song::setName(const char* name)
{
	if (!name)
	{
		this->name = nullptr;
		return;
	}

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Song::setArtist(const char* artist)
{
	if (!artist)
	{
		this->artist = nullptr;
		return;
	}

	delete[] this->artist;
	this->artist = new char[strlen(artist) + 1];
	strcpy(this->artist, artist);
}

void Song::setDuration(unsigned duration)
{
	this->duration = duration;
}

const char* Song::getName() const
{
	return name;
}

const char* Song::getArtist() const
{
	return artist;
}

unsigned Song::getDuration() const
{
	return duration;
}

std::ostream& operator<<(std::ostream& os, const Song& obj)
{
	unsigned minutes = obj.duration / 60;
	unsigned seconds = obj.duration % 60;

	os << obj.name << " by " << obj.artist << " [" << minutes << " min " << seconds << " sec]";
	return os;
}

void Song::saveToBinary(std::ofstream& ofs) const
{
	if (!ofs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	size_t nameLen = strlen(name);
	ofs.write((const char*)&nameLen, sizeof(size_t));
	ofs.write((const char*)name, nameLen);

	size_t artistLen = strlen(artist);
	ofs.write((const char*)&artistLen, sizeof(size_t));
	ofs.write((const char*)artist, artistLen);

	ofs.write((const char*)&duration, sizeof(unsigned));
}

void Song::loadFromBinary(std::ifstream& ifs)
{
	if (!ifs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	size_t nameLen;
	ifs.read((char*)&nameLen, sizeof(size_t));

	delete[] name;
	name = new char[nameLen + 1];
	ifs.read((char*)name, nameLen);
	name[nameLen] = '\0';

	size_t artistLen;
	ifs.read((char*)&artistLen, sizeof(size_t));

	delete[] artist;
	artist = new char[artistLen + 1];
	ifs.read((char*)artist, artistLen);
	artist[artistLen] = '\0';

	ifs.read((char*)&duration, sizeof(unsigned));
}
