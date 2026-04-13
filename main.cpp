#include "Playlist.h"

int main() {
    Playlist p;
    p.add("Song 2", 0, 1, 55, "rp", "song2.dat");
    p.add("Song 1", 0, 1, 5, "p", "song1.dat");

    p.print();

    p.sortByName();
    p.print();

    p.find("Song 1");

    p.findGenre('p');

    p.findGenre('r');

    p.mix("Song 1", "Song 2");
    p.save("Song 1", "song3.dat");
}