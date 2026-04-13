#include "Playlist.h"
#include "Genre.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

Playlist::Playlist() : songsCount(0) {}

void Playlist::add(const char* name, unsigned hours, unsigned minutes,
    unsigned seconds, const char* genreStr, const char* filename) {
    if (songsCount >= PlaylistConstants::MAX_SONGS) {
        std::cout << "Playlist is full!\n";
        return;
    }
    songs[songsCount++] = Song(name, hours, minutes, seconds, genreStr, filename);
}

void Playlist::print() const {
    for (unsigned i = 0; i < songsCount; i++)
        songs[i].print();
}

int Playlist::findIndex(const char* name) const {
    for (unsigned i = 0; i < songsCount; i++)
        if (strcmp(songs[i].getName(), name) == 0)
            return i;
    return -1;
}

void Playlist::find(const char* name) const {
    int idx = findIndex(name);
    if (idx == -1) {
        std::cout << "Song not found: " << name << "\n";
        return;
    }
    songs[idx].print();
}

void Playlist::findGenre(char genreChar) const {
    char genreStr[2] = { genreChar, '\0' };
    unsigned char flag = parseGenre(genreStr);

    for (unsigned i = 0; i < songsCount; i++)
        if (hasGenre(songs[i].getGenre(), flag))
            songs[i].print();
}

void Playlist::sortByDuration() {
    for (unsigned i = 0; i < songsCount - 1; i++)
        for (unsigned j = 0; j < songsCount - i - 1; j++)
            if (songs[j].getTotalSeconds() > songs[j + 1].getTotalSeconds()) {
                Song temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
}

void Playlist::sortByName() {
    for (unsigned i = 0; i < songsCount - 1; i++)
        for (unsigned j = 0; j < songsCount - i - 1; j++)
            if (strcmp(songs[j].getName(), songs[j + 1].getName()) > 0) {
                Song temp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = temp;
            }
}

void Playlist::applyKthBit(const char* name, unsigned k) {
    int idx = findIndex(name);
    if (idx == -1) {
        std::cout << "Song not found: " << name << "\n";
        return;
    }
    songs[idx].applyKthBit(k);
}

void Playlist::mix(const char* name1, const char* name2) {
    int idx1 = findIndex(name1);
    int idx2 = findIndex(name2);
    if (idx1 == -1 || idx2 == -1) {
        std::cout << "Song not found!\n";
        return;
    }
    songs[idx1].mix(songs[idx2]);
}

void Playlist::save(const char* name, const char* filename) const {
    int idx = findIndex(name);
    if (idx == -1) {
        std::cout << "Song not found: " << name << "\n";
        return;
    }
    songs[idx].save(filename);
}