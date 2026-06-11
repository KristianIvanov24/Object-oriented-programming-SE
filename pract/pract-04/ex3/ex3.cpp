#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning(disable : 4996)

namespace constants{
	const size_t MAX_SIZE_NAME = 64;
	const size_t MAX_BITES_CONTENT = 256;
	const char* DEFAULT_NAME = "Unknown";
	const size_t GENRES_AMOUNT = 5;

	const size_t MAX_SONGS_IN_PLAYLIST = 30;
}

namespace validation{
	bool isValidName(const char* name) {
		return name && strlen(name) > 0 && strlen(name) <= constants::MAX_SIZE_NAME;
	}
}

enum class Genre {
	ROCK = 1 << 0,
	POP = 1 << 1,
	JAZZ = 1 << 2,
	ELECTRONIC = 1 << 3,
	HIP_HOP = 1 << 4
};

const char* genreToString(unsigned char c) {
	switch (c) {
	case 1 << 0:
		return "Rock";
	case 1 << 1:
		return "Pop";
	case 1 << 2:
		return "Jazz";
	case 1 << 3:
		return "Electronic";
	case 1 << 4:
		return "Hip-hop";
	default:
		return "Unknown";
	}
}

size_t getFileSize(std::ifstream& file) {
	size_t res = 0;

	size_t currPos = file.tellg();
	file.seekg(0, std::ios::end);
	res = file.tellg();
	file.seekg(currPos);
	
	return res;
}

unsigned char charToGenreBit(char c) {
	switch (c) {
	case 'r':
		return (unsigned char)Genre::ROCK;
	case 'p':
		return (unsigned char)Genre::POP;
	case 'j':
		return (unsigned char)Genre::JAZZ;
	case 'e':
		return (unsigned char)Genre::ELECTRONIC;
	case 'h':
		return (unsigned char)Genre::HIP_HOP;
	default:
		return 0;
	}
}

class Song {
private:

	char content[constants::MAX_BITES_CONTENT + 1]{};
	char name[constants::MAX_SIZE_NAME + 1];
	unsigned duration;
	unsigned contentSize;
	unsigned char genre;

	void setName(const char* name) {
		if (validation::isValidName(name)) {
			strncpy(this->name, name, constants::MAX_SIZE_NAME);
		} else {
			strncpy(this->name, constants::DEFAULT_NAME, constants::MAX_SIZE_NAME);
		}
	}

	void setDuration(unsigned duration) {
		this->duration = duration;
	}

	void setGenre(const char* genre) {
		this->genre = 0;
		for (int i = 0; genre[i] != '\0'; i++) {
			this->genre |= charToGenreBit(genre[i]);
		}
	}	

	void setContent(const char* filename) {
		std::ifstream ifs(filename, std::ios::binary);
		if (ifs.is_open()) {
			contentSize = getFileSize(ifs);
			if (contentSize > constants::MAX_BITES_CONTENT) {
				contentSize = constants::MAX_BITES_CONTENT;
			}

			ifs.read(content, contentSize);
		}
		else {
			std::cout << "File cannot be opened" << std::endl;
			contentSize = 0;
		}
		ifs.close();
	}

	void printDuration() const {
		unsigned hours = duration / 3600;
		unsigned minutes = (duration % 3600) / 60;
		unsigned seconds = duration % 60;
		std::cout << ((hours < 10) ? "0" : "") << hours << ":"
			<< ((minutes < 10) ? "0" : "") << minutes << ":"
			<< ((seconds < 10) ? "0" : "") << seconds;
	}

	void printGenre() const {
		bool first = true;

		for (size_t i = 0; i < constants::GENRES_AMOUNT; i++) {
			unsigned char mask = (1 << i);

			if (genre & mask) {
				if (!first)
					std::cout << " & ";

				std::cout << genreToString(mask);
				first = false;
			}
		}
	}

public:

	Song() : duration(0), contentSize(0), genre(0) {
		setName(constants::DEFAULT_NAME);
	}

	Song(const char* filename, const char* songName, unsigned duration, const char* genre) : duration(duration), genre(0) {
		setName(songName);
		setContent(filename);
		setGenre(genre);
	}

	void mix(const Song& other) {
		size_t minSize = contentSize < other.contentSize ? contentSize : other.contentSize;
		for (size_t i = 0; i < minSize; i++) {
			content[i] ^= other.content[i];
		}
	}

	const char* getName() const {
		return name;
	}

	unsigned getDuration() const {
		return duration;
	}

	unsigned char getGenre() const {
		return genre;
	}

	const char* getContent() const {
		return content;
	}

	unsigned getContentSize() const {
		return contentSize;
	}

	void printSong() const {
		std::cout << name << " -> ";
		printDuration();
		std::cout << " -> ";
		printGenre();
		std::cout << std::endl;
	}

};

class Playlist {
private:

	Song songs[constants::MAX_SONGS_IN_PLAYLIST + 1];
	unsigned songsCount;

public:

	Playlist() : songsCount(0) {}

	void addSong(const char* filename, const char* songName, unsigned duration, const char* genre) {
		if (songsCount < constants::MAX_SONGS_IN_PLAYLIST) {
			songs[songsCount++] = Song(filename, songName, duration, genre);
		}
	}

	void printPlaylist() const {
		
		for (size_t i = 0; i < songsCount; i++) {
			songs[i].printSong();
		}
	}

	Song getSongByName(const char* name) {
		for (size_t i = 0; i < songsCount; i++) {
			if (strcmp(songs[i].getName(), name) == 0) {
				return songs[i];
			}
		}

		return Song();
	}

	Song* getSongsByGenre(char genre) {
		unsigned char mask = charToGenreBit(genre);

		size_t arrSize = 0;
		for (size_t i = 0; i < songsCount; i++) {
			if (songs[i].getGenre() & mask) {
				arrSize++;
			}
		}

		if (arrSize == 0) return nullptr;

		Song* res = new Song[arrSize];
		size_t curr = 0; 

		for (size_t i = 0; i < songsCount; i++) {
			if (songs[i].getGenre() & mask) {
				res[curr++] = songs[i];
			}
		}

		return res;
	}

	void sortBySongDuration() {
		for (size_t i = 0; i < songsCount - 1; i++) {
			for (size_t j = 0; j < songsCount - i - 1; j++) {
				if (songs[j].getDuration() > songs[j + 1].getDuration()) {
					std::swap(songs[j], songs[j + 1]);
				}
			}
		}
	}

	void sortBySongName() {
		for (size_t i = 0; i < songsCount - 1; i++) {
			for (size_t j = 0; j < songsCount - i - 1; j++) {
				if (strcmp(songs[j].getName(), songs[j + 1].getName()) > 0) {
					std::swap(songs[j], songs[j + 1]);
				}
			}
		}
	}

	int findByName(const char* name) {
		for (size_t i = 0; i < songsCount; i++) {
			if (strcmp(songs[i].getName(), name) == 0) {
				return i;
			}
		}
		return -1;
	}

	void mix(const char* name1, const char* name2) {
		int index1 = findByName(name1);
		int index2 = findByName(name2);

		if (index1 == -1 || index2 == -1) {
			return;
		}

		songs[index1].mix(songs[index2]);
	}

	void save(const char* songName, const char* filename) {
		int index = findByName(songName);
		if (index == -1) {
			return;
		}

		std::ofstream ofs(filename, std::ios::binary);
		if (!ofs.is_open()) {
			std::cout << "File cannot be opened" << std::endl;
			return;
		}

		Song& song = songs[index];

		size_t nameLen = strlen(song.getName());
		ofs.write((const char*)&nameLen, sizeof(nameLen));
		ofs.write(song.getName(), nameLen);

		unsigned duration = song.getDuration();
		ofs.write((const char*)&duration, sizeof(duration));

		unsigned char genre = song.getGenre();
		ofs.write((const char*)&genre, sizeof(genre));

		unsigned contentSize = song.getContentSize();
		ofs.write((const char*)&contentSize, sizeof(contentSize));

		ofs.write(song.getContent(), contentSize);

		ofs.close();
	}

};

int main()
{

    return 0;
}