#include <iostream>

namespace constants
{
    const int MAX_HEADER_LENGTH = 101;
    const int MAX_SINGER_LENGTH = 101;
    const double MIN_RATING = 0.0;
    const double MAX_RATING = 10.0;
    const int MAX_PLAYLIST_CAPACITY = 64;
}

enum class Genre
{
    Rock,
    Pop,
    ThrashMetal,
    KPop,
    Chalga
};

struct Song
{
    char header[constants::MAX_HEADER_LENGTH];
    char singer[constants::MAX_SINGER_LENGTH];
    Genre genre;
    double rating;
    int listeningsNum;
};

struct Playlist
{
    Song songs[constants::MAX_PLAYLIST_CAPACITY];
    int count = 0;
};

void addSong(Playlist& playlist, const Song& newSong)
{
    if (playlist.count > constants::MAX_PLAYLIST_CAPACITY)
    {
        std::cout << "The limit of the songs is exceeded!";
        return;
    }

    if (newSong.rating<constants::MIN_RATING || newSong.rating>constants::MAX_RATING)
    {
        std::cout << "Invalid rating for the song" << newSong.header;
        return;
    }

    playlist.songs[playlist.count] = newSong;
    playlist.count++;
}

Song* findSong(Playlist& playlist, bool(*predicate)(const Song&))
{
    for (int i = 0; i < playlist.count; i++)
    {
        if (predicate(playlist.songs[i]) == true)
            return &playlist.songs[i];
    }
    return nullptr;
}

void sortPlaylist(Playlist& playlist, bool(*compare)(const Song&, const Song&))
{
    for (int i = 0; i < playlist.count - 1; i++)
    {
        for (int j = i; j < playlist.count; j++)
        {
            if (compare(playlist.songs[j + 1], playlist.songs[j]) == true)
            {
                Song temp = playlist.songs[j];
                playlist.songs[j] = playlist.songs[j + 1];
                playlist.songs[j + 1] = temp;
            }
        }
    }
}

int main()
{
    std::cout << "Hello World!\n";
}