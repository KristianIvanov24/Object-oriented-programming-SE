#include "Genre.h"
#include <iostream>
#include <cstring>

unsigned char parseGenre(const char* genreStr) {
    unsigned char result = 0;
    for (int i = 0; genreStr[i] != '\0'; i++) {
        switch (genreStr[i]) {
        case 'r': result |= GenreFlags::ROCK;       break;
        case 'p': result |= GenreFlags::POP;        break;
        case 'h': result |= GenreFlags::HIPHOP;     break;
        case 'e': result |= GenreFlags::ELECTRONIC; break;
        case 'j': result |= GenreFlags::JAZZ;       break;
        }
    }
    return result;
}

bool hasGenre(unsigned char genre, unsigned char flag) {
    return (genre & flag) != 0;
}

void printGenre(unsigned char genre) {
    bool first = true;
    auto printSep = [&first]() {
        if (!first) std::cout << "&";
        first = false;
        };

    if (hasGenre(genre, GenreFlags::ROCK)) { printSep(); std::cout << "Rock"; }
    if (hasGenre(genre, GenreFlags::POP)) { printSep(); std::cout << "Pop"; }
    if (hasGenre(genre, GenreFlags::HIPHOP)) { printSep(); std::cout << "HipHop"; }
    if (hasGenre(genre, GenreFlags::ELECTRONIC)) { printSep(); std::cout << "Electronic"; }
    if (hasGenre(genre, GenreFlags::JAZZ)) { printSep(); std::cout << "Jazz"; }
}