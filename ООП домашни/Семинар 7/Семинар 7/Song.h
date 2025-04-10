#pragma once
#include <iostream>
#include <fstream>

class Song
{
private:
	char* name = nullptr;
	char* artist = nullptr;
	unsigned duration = 0;

	void free();
	void copyFrom(const Song&);

public:
	Song();
	Song(const char*, const char*, unsigned);
	Song(const Song&);
	Song& operator=(const Song&);
	~Song();

	void setName(const char*);
	void setArtist(const char*);
	void setDuration(unsigned);

	const char* getName() const;
	const char* getArtist() const;
	unsigned getDuration() const;

	friend std::ostream& operator<<(std::ostream&, const Song&);

	void saveToBinary(std::ofstream&) const;

	void loadFromBinary(std::ifstream&);
};

