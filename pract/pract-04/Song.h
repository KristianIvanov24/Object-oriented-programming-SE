#pragma once
#include "Constants.h"

class Song {
    char name[PlaylistConstants::MAX_NAME_LEN + 1];
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
    unsigned char genre;
    unsigned char content[PlaylistConstants::MAX_CONTENT_LEN];
    unsigned contentSize;

public:
    Song();
    Song(const char* name, unsigned hours, unsigned minutes,
        unsigned seconds, const char* genreStr, const char* filename);

    const char* getName() const;
    unsigned char getGenre() const;
    unsigned getTotalSeconds() const;

    void print() const;

    void applyKthBit(unsigned k);
    void mix(const Song& other);

    void save(const char* filename) const;

private:
    void loadFromFile(const char* filename);
};