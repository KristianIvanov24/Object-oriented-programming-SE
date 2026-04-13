#include "Song.h"
#include "Genre.h"
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)

Song::Song() {
    strcpy(name, "");
    hours = minutes = seconds = 0;
    genre = 0;
    contentSize = 0;
}

Song::Song(const char* name, unsigned hours, unsigned minutes,
    unsigned seconds, const char* genreStr, const char* filename) {
    strncpy(this->name, name, PlaylistConstants::MAX_NAME_LEN);
    this->name[PlaylistConstants::MAX_NAME_LEN] = '\0';
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->genre = parseGenre(genreStr);
    this->contentSize = 0;
    loadFromFile(filename);
}

const char* Song::getName() const { return name; }
unsigned char Song::getGenre() const { return genre; }

unsigned Song::getTotalSeconds() const {
    return hours * 3600 + minutes * 60 + seconds;
}

void Song::print() const {
    std::cout << name << ", "
        << (hours < 10 ? "0" : "") << hours << ":"
        << (minutes < 10 ? "0" : "") << minutes << ":"
        << (seconds < 10 ? "0" : "") << seconds << ", ";
    printGenre(genre);
    std::cout << "\n";
}

void Song::applyKthBit(unsigned k) {
    unsigned totalBits = contentSize * 8;
    for (unsigned i = k - 1; i < totalBits; i += k) {
        unsigned bitFromEnd = i;
        unsigned byteIndex = contentSize - 1 - (bitFromEnd / 8);
        unsigned bitIndex = bitFromEnd % 8;
        content[byteIndex] |= (1 << bitIndex);
    }
}

void Song::mix(const Song& other) {
    unsigned minSize = contentSize < other.contentSize
        ? contentSize : other.contentSize;
    for (unsigned i = 0; i < minSize; i++)
        content[i] ^= other.content[i];
}

void Song::save(const char* filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file: " << filename << "\n";
        return;
    }
    file.write((const char*)content, contentSize);
}

void Song::loadFromFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file: " << filename << "\n";
        return;
    }
    file.read((char*)content, PlaylistConstants::MAX_CONTENT_LEN);
    contentSize = file.gcount();
}