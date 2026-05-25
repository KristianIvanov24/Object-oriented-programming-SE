#pragma once

namespace GenreFlags {
    const unsigned char ROCK = 0b00000001;
    const unsigned char POP = 0b00000010;
    const unsigned char HIPHOP = 0b00000100;
    const unsigned char ELECTRONIC = 0b00001000;
    const unsigned char JAZZ = 0b00010000;
}

unsigned char parseGenre(const char* genreStr);
bool hasGenre(unsigned char genre, unsigned char flag);
void printGenre(unsigned char genre);