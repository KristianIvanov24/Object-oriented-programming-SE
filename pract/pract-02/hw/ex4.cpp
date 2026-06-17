#include <iostream>

/*
5. Създайте структура, която представлява песен, която съдържа следните характеристики:

заглавие (до 100 символа)
изпълнител (до 100 символа)
жанр (може да бъде Rock, Pop, Thrash Metal, K-pop, Chalga)
рейтинг (дробно число от 0 до 10 примерно)
брой слушания (цяло число)

Създайте структура Playlist, която се описва с най-много 64 песни. Реализирайте следните функции:

Добавяне на песен в колекцията (ако капацитетът е запълнен, принтирайте подходящо съобщение).
Връщане на указател към книга по подаден унарен предикат, приемащ като аргумент 1 песен.
Сортиране на песните по подаден бинарен предикат, приемащ като аргументи 2 песни.
*/

const int MAX_TITLE_LEN = 100;
const int MAX_NAME_LEN = 100;
const int MAX_SONGS = 64;
const double MAX_RATING = 10;
const double MIN_RATING = 0;

enum class Genre
{
    ROCK,
    POP,
    TRASH_METAL,
    KPOP,
    CHALGA
};

struct Song
{
    char title[MAX_TITLE_LEN];
    char singer[MAX_NAME_LEN];
    Genre genre;
    double rating;
    int plays;
};

struct Playlist
{
    Song songs[MAX_SONGS];
    int numberOfSongs = 0;
};

bool validateSong(const Song &s)
{
    if (s.rating > MAX_RATING || s.rating < MIN_RATING)
    {
        std::cout << "Rating should be between 0 and 10" << std::endl;
        return false;
    }
    return true;
}

void addSong(Playlist &playlist, const Song &song)
{
    if (playlist.numberOfSongs >= MAX_SONGS)
    {
        std::cout << "Playlist is full!" << std::endl;
        return;
    }
    if (!validateSong(song))
        return;

    Song *s = &playlist.songs[playlist.numberOfSongs];
    playlist.numberOfSongs++;

    strcpy(s->title, song.title);
    strcpy(s->singer, song.singer);
    s->genre = song.genre;
    s->rating = song.rating;
    s->plays = song.plays;
}

const Song *findSong(const Playlist &playlist, bool (*validate)(const Song &s))
{
    for (int i = 0; i < playlist.numberOfSongs; i++)
    {
        if (validate(playlist.songs[i]))
            return &playlist.songs[i];
    }
    return nullptr;
}

bool cmp(const Song &s1, const Song &s2)
{
    return s1.rating < s2.rating;
}

void swap(Song &s1, Song &s2)
{
    Song temp = s1;
    s1 = s2;
    s2 = temp;
}

void sort(Playlist &playlist, bool (*comparator)(const Song &s1, const Song &s2))
{
    for (int i = 0; i < playlist.numberOfSongs - 1; i++)
    {
        for (int j = i + 1; j < playlist.numberOfSongs; j++)
        {
            if (comparator(playlist.songs[j], playlist.songs[i]))
            {
                swap(playlist.songs[i], playlist.songs[j]);
            }
        }
    }
}

int main()
{
    Playlist pl;
    Song s1 = {"abc", "def", Genre::POP, 2.3, 100};
    Song s2 = {"ghi", "jkl", Genre::KPOP, 5.6, 230};
    Song s3 = {"mno", "pqr", Genre::CHALGA, 6.1, 400};
    addSong(pl, s1);
    addSong(pl, s2);
    addSong(pl, s3);

    if (findSong(pl, [](const Song &s)
                 { return strcmp(s.title, "bac") == 0; }) != nullptr)
    {
        std::cout << "Song exists" << std::endl;
    }
    else
    {
        std::cout << "Didn't find song" << std::endl;
    }

    sort(pl, cmp);

    return 0;
}