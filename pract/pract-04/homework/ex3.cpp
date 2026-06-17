#include <iostream>
#include <cstring>
#include <fstream>

enum class Genre;

namespace constants
{
    const size_t MAX_NAME_LEN = 64;
    const size_t GENRE_COUNT = 5;
    const size_t MAX_BYTES = 256;
    const size_t MAX_SONGS = 30;
    const unsigned MAX_SECONDS = 60;
    const unsigned MAX_MINUTES = 60;
    const char *DEFAULT_NAME = "Unknown";
    const Genre DEFAULT_GENRE = Genre::POP;
}

enum class Genre
{
    ROCK = 1 << 0,
    POP = 1 << 1,
    HIP_HOP = 1 << 2,
    ELECTRONIC_MUSIC = 1 << 3,
    JAZZ = 1 << 4,
};

unsigned char genreToMask(Genre genre)
{
    return (unsigned char)genre;
}

const char *maskToString(unsigned char mask)
{
    switch (mask)
    {
    case 1 << 0:
        return "ROCK";
    case 1 << 1:
        return "POP";
    case 1 << 2:
        return "HIP_HOP";
    case 1 << 3:
        return "ELECTRONIC_MUSIC";
    case 1 << 4:
        return "JAZZ";
    default:
        return constants::DEFAULT_NAME;
    }
}

unsigned char charToMask(const char *s)
{
    unsigned char genre = 0;
    for (size_t i = 0; s[i]; i++)
    {
        switch (s[i])
        {
        case 'r':
            genre |= genreToMask(Genre::ROCK);
            break;
        case 'p':
            genre |= genreToMask(Genre::POP);
            break;
        case 'h':
            genre |= genreToMask(Genre::HIP_HOP);
            break;
        case 'e':
            genre |= genreToMask(Genre::ELECTRONIC_MUSIC);
            break;
        case 'j':
            genre |= genreToMask(Genre::JAZZ);
            break;
        default:
            std::cout << "Unknown genre!" << std::endl;
        }
    }
}

size_t getFileSize(std::ifstream &file)
{
    size_t currentPos = file.tellg();
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(currentPos);
    return size;
}

class Duration;

namespace validation
{
    bool isValidName(const char *name)
    {
        return strnlen(name, constants::MAX_NAME_LEN + 1) <= constants::MAX_NAME_LEN + 1;
    }

    bool isValidHours(unsigned hours)
    {
        return hours >= 0;
    }

    bool isValidMinutes(unsigned minutes)
    {
        return minutes >= 0 && minutes <= constants::MAX_MINUTES;
    }

    bool isValidSeconds(unsigned seconds)
    {
        return seconds >= 0 && seconds <= constants::MAX_SECONDS;
    }

    bool isValidDuration(Duration duration)
    {
        return isValidHours(duration.getHours()) && isValidMinutes(duration.getMinutes()) && isValidSeconds(duration.getSeconds());
    }

    bool isValidContentLen(size_t contentLen)
    {
        return contentLen <= constants::MAX_BYTES;
    }
}

class Duration
{
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

public:
    Duration() : hours(0), minutes(0), seconds(0) {}

    Duration(unsigned hours, unsigned minutes, unsigned seconds)
    {
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
    }

    void setHours(unsigned hours)
    {
        if (!validation::isValidHours(hours))
        {
            this->hours = 0;
            return;
        }
        this->hours = hours;
    }

    void setMinutes(unsigned minutes)
    {
        if (!validation::isValidMinutes(minutes))
        {
            this->minutes = 0;
            return;
        }
        this->minutes = minutes;
    }

    void setSeconds(unsigned seconds)
    {
        if (!validation::isValidSeconds(seconds))
        {
            this->seconds = 0;
            return;
        }
        this->seconds = seconds;
    }

    unsigned getHours() const
    {
        return hours;
    }

    unsigned getMinutes() const
    {
        return minutes;
    }

    unsigned getSeconds() const
    {
        return seconds;
    }

    void print() const
    {
        std::cout << (hours < 10 ? "0" : "") << hours << ":"
                  << (minutes < 10 ? "0" : "") << minutes << ":"
                  << (seconds < 10 ? "0" : "") << seconds;
    }

    unsigned toSeconds() const
    {
        return hours * constants::MAX_MINUTES * constants::MAX_SECONDS + minutes * constants::MAX_SECONDS + seconds;
    }
};

class Song
{
    char name[constants::MAX_NAME_LEN + 1];
    Duration duration;
    unsigned char genre;
    unsigned char content[constants::MAX_BYTES]{};
    size_t contentLen;

    void printGenre() const
    {
        bool moreThanOne = false;
        for (size_t i = 0; i < constants::GENRE_COUNT; i++)
        {
            if ((1 << i) & genre)
            {
                if (moreThanOne)
                    std::cout << "&";
                std::cout << maskToString(i);
                moreThanOne = true;
            }
        }
    }

public:
    Song() : duration(), genre(0), contentLen(0)
    {
        setName(constants::DEFAULT_NAME);
    }

    Song(const char *name, Duration duration, const char *genre, const char *contentFileName)
    {
        setName(name);
        setDuration(duration);
        setGenre(genre);

        std::ifstream contentFile(contentFileName, std::ios::binary);
        if (!contentFile.is_open())
        {
            setContentLen(0);
        }
        else
        {
            setContentLen(getFileSize(contentFile));
            contentFile.read((char *)content, contentLen);
            contentFile.close();
        }
    }

    void setName(const char *name)
    {
        if (!validation::isValidName(name))
        {
            strncpy(this->name, constants::DEFAULT_NAME, constants::MAX_NAME_LEN + 1);
            return;
        }
        strncpy(this->name, name, constants::MAX_NAME_LEN + 1);
        this->name[constants::MAX_NAME_LEN] = '\0';
    }

    void setDuration(Duration duration)
    {
        if (!validation::isValidDuration(duration))
        {
            this->duration = Duration();
            return;
        }
        this->duration = duration;
    }

    void setGenre(const char *genre)
    {
        if (!genre)
        {
            this->genre = constants::DEFAULT_GENRE;
            return;
        }
        this->genre = charToMask(genre);
    }

    void setContentLen(size_t contentLen)
    {
        if (!validation::isValidContentLen(contentLen))
        {
            this->contentLen = 0;
            return;
        }
        this->contentLen = contentLen;
    }

    const char *getName() const
    {
        return name;
    }

    unsigned char getGenre() const
    {
        return genre;
    }

    Duration getDuration() const
    {
        return duration;
    }

    size_t getContentLen() const
    {
        return contentLen;
    }

    void flipEveryKth(unsigned k)
    {
        if (k == 0)
            return;
        for (size_t i = contentLen - 1; i >= 0; i -= k)
        {
            content[i] |= 1;
        }
    }

    void mix(const Song &other)
    {
        for (size_t i = 0; i < std::min(contentLen, other.contentLen); i++)
        {
            content[i] ^= other.content[i];
        }
    }

    void print() const
    {
        std::cout << name << ", ";
        duration.print();
        std::cout << ", ";
        printGenre();
        std::cout << std::endl;
    }
};

class Playlist
{
    Song songs[constants::MAX_SONGS];
    size_t songCount;

    void sort(bool (*cmp)(const Song &, const Song &))
    {
        for (size_t i = 0; i < songCount - 1; i++)
        {
            for (size_t j = 0; j < songCount - i - 1; j++)
            {
                if (cmp(songs[j], songs[j + 1]))
                {
                    std::swap(songs[j], songs[j + 1]);
                }
            }
        }
    }

public:
    Playlist() : songCount(0) {}

    bool addSong(const char *name, Duration duration, const char *genre, const char *contentFileName)
    {
        if (songCount >= constants::MAX_SONGS)
        {
            return false;
        }

        Song song = Song(name, duration, genre, contentFileName);
        songs[songCount++] = song;
        return true;
    }

    void print() const
    {
        for (size_t i = 0; i < songCount; i++)
        {
            songs[i].print();
        }
    }

    Song *find(const char *name)
    {

        for (size_t i = 0; i < songCount; i++)
        {
            if (strncmp(name, songs[i].getName(), constants::MAX_NAME_LEN) == 0)
            {
                return &songs[i];
            }
        }
        return nullptr;
    }

    void findGenre(unsigned char genre) const
    {
        for (size_t i = 0; i < songCount; i++)
        {
            bool hasGenre = true;
            for (size_t j = 0; j < constants::GENRE_COUNT; i++)
            {
                if (genre & (1 << j))
                {
                    hasGenre *= (this->songs[i].getGenre() & (1 << j));
                }
            }
            if (hasGenre)
            {
                songs[i].print();
            }
        }
    }

    void sortByDuration()
    {
        sort([](const Song &s1, const Song &s2)
             { return s1.getDuration().toSeconds() > s1.getDuration().toSeconds(); });
    }

    void sortByName()
    {
        sort([](const Song &s1, const Song &s2)
             { return s1.getName() > s2.getName(); });
    }

    void mix(const char *name1, const char *name2)
    {
        Song *s1 = find(name1);
        Song *s2 = find(name2);
        if (s1 && s2)
            s1->mix(*s2);
    }

    void flipEveryKth(const char *name, unsigned k)
    {
        Song *s = find(name);
        if (s)
            s->flipEveryKth(k);
    }

    bool save(const char *name, const char *fileName)
    {
        Song *s = find(name);
        if (!s)
            return false;

        std::ofstream file(fileName, std::ios::binary);
        if (!file.is_open())
        {
            std::cout << "Couldn't open file!" << std::endl;
            return false;
        }

        file.write((char *)&s, sizeof(Song));
        file.close();

        return true;
    }
};