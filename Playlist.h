#pragma once
#include "Song.h"

class Playlist {
    Song songs[PlaylistConstants::MAX_SONGS];
    unsigned songsCount;

public:
    Playlist();

    void add(const char* name, unsigned hours, unsigned minutes,
        unsigned seconds, const char* genreStr, const char* filename);

    void print() const;

    void find(const char* name) const;
    void findGenre(char genreChar) const;

    void sortByDuration();
    void sortByName();

    void applyKthBit(const char* name, unsigned k);
    void mix(const char* name1, const char* name2);

    void save(const char* name, const char* filename) const;

private:
    int findIndex(const char* name) const;
};