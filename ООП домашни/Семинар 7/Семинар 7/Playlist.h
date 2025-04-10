#pragma once
#include "Song.h"
#include <iostream>

class Playlist
{
private:
	Song* songs = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const Playlist&);
	void resize();
	size_t calculateNewCapacity() const;

public:
	Playlist();
	Playlist(const Playlist&);
	Playlist& operator=(const Playlist&);
	~Playlist();

	void addSong(const Song&);
	friend std::ostream& operator<<(std::ostream&, const Playlist&);

	void saveToBinary(const char* fileName) const;
	void loadFromBinary(const char* fileName);

	friend void mergePlaylists(const char*, const char*, const char*);

	unsigned calculateTotalDuration() const;
};