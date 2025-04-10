#include "Playlist.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

void Playlist::free()
{
	delete[] songs;

	songs = nullptr;
	size = 0;
	capacity = 0;
}

void Playlist::copyFrom(const Playlist& other)
{
	size = other.size;
	capacity = other.capacity;

	songs = new Song[other.capacity];
	for (size_t i = 0; i < size; i++)
	{
		songs[i] = other.songs[i];
	}
}

void Playlist::resize()
{
	size_t newCapacity = calculateNewCapacity();

	Song* temp = songs;
	delete[] songs;
	songs = new Song[newCapacity];

	for (size_t i = 0; i < size; i++)
	{
		songs[i] = temp[i];
	}

	capacity = newCapacity;
	delete[] temp;
}

size_t Playlist::calculateNewCapacity() const
{
	size_t result = capacity;
	uint32_t mask = Constants::STARTING_SONG_COUNT_IN_PLAYLIST;

	while (result & mask)
	{
		result ^= mask;
		mask <<= 1;
	}

	result ^= mask;

	return result;
}

Playlist::Playlist()
{
	size = 0;
	capacity = Constants::STARTING_SONG_COUNT_IN_PLAYLIST;
	songs = new Song[capacity];
}

Playlist::Playlist(const Playlist& other)
{
	copyFrom(other);
}

Playlist& Playlist::operator=(const Playlist& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Playlist::~Playlist()
{
	free();
}

void Playlist::addSong(const Song& song)
{
	if (size >= capacity)
	{
		resize();
	}

	songs[size++] = song;
	std::cout << "Song added!\n";
}

std::ostream& operator<<(std::ostream& os, const Playlist& obj)
{
	for (size_t i = 0; i < obj.size; i++)
	{
		os << i + 1 << ". " << obj.songs[i] << '\n';
	}

	return os;
}

void Playlist::saveToBinary(const char* fileName) const
{
	if (!fileName)
		return;

	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	ofs.write((const char*)&size, sizeof(size_t));
	ofs.write((const char*)&capacity, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		songs[i].saveToBinary(ofs);
	}

	ofs.close();
}

void Playlist::loadFromBinary(const char* fileName)
{
	if (!fileName)
		return;

	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "Error when opening file\n";
		return;
	}

	ifs.read((char*)&size, sizeof(size_t));
	ifs.read((char*)&capacity, sizeof(size_t));

	delete[] songs;
	songs = new Song[capacity];

	for (size_t i = 0; i < size; i++)
	{
		songs[i].loadFromBinary(ifs);
	}

	ifs.close();
}

void mergePlaylists(const char* firstFile, const char* secondFile,
	const char* resultFile)
{
	if (!firstFile || !secondFile || !resultFile)
		return;

	Playlist first;
	Playlist second;
	Playlist result;

	first.loadFromBinary(firstFile);
	second.loadFromBinary(secondFile);

	for (size_t f = 0; f < first.size; f++)
	{
		result.addSong(first.songs[f]);
	}

	for (size_t s = 0; s < second.size; s++)
	{
		result.addSong(second.songs[s]);
	}

	result.saveToBinary(resultFile);
}

unsigned Playlist::calculateTotalDuration() const
{
	unsigned res = 0;
	for (size_t i = 0; i < size; i++)
	{
		res += songs[i].getDuration();
	}

	return res;
}
