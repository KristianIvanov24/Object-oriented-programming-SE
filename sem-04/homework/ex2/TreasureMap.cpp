#include "TreasureMap.h"

size_t TreasureMap::findBy(const char *name) const {
    for (size_t i = 0; i < treasureCount; i++) {
        if (strcmp(treasures[i].getName(), name) == 0) {
            return i;
        }
    }
    return treasureCount;
}

void TreasureMap::sort(bool(*cmp)(const Treasure &, const Treasure &)) {
    for (size_t i = 0; i < treasureCount - 1; i++) {
        for (size_t j = 0; j < treasureCount - i - 1; j++) {
            if (cmp(treasures[j], treasures[j + 1])) {
                std::swap(treasures[j], treasures[j + 1]);
            }
        }
    }
}

bool TreasureMap::add(const Treasure &treasure) {
    if (treasureCount >= constants::MAX_TREASURES) {
        return false;
    }

    treasures[treasureCount++] = treasure;
    return true;
}

bool TreasureMap::addTreasure(const char *name, int x, int y, int value) {
    Treasure t = Treasure(name, x, y, value);
    return add(t);
}

bool TreasureMap::remove(const char *name) {
    size_t i = findBy(name);
    if (i == treasureCount) {
        return false;
    }

    treasures[i] = treasures[treasureCount - 1];
    treasureCount--;
    return true;
}

size_t TreasureMap::findBy(int x, int y) const {
    for (size_t i = 0; i < treasureCount; i++) {
        if (treasures[i].getX() == x && treasures[i].getY() == y) {
            return i;
        }
    }
    return treasureCount;
}

void TreasureMap::sortByValue() {
    sort([](const Treasure &t1, const Treasure &t2) { return t1.getValue() < t2.getValue(); });
}

void TreasureMap::sortByDistanceFromOrigin() {
    sort([](const Treasure &t1, const Treasure &t2) { return t1.distanceFromOrigin() < t2.distanceFromOrigin(); });
}

void TreasureMap::print() const {
    for (size_t i = 0; i < treasureCount; i++) {
        treasures[i].print();
    }
}

Treasure TreasureMap::getMostValuable() const {
    Treasure t = Treasure();
    if (treasureCount == 0)
        return t;

    for (size_t i = 0; i < treasureCount; i++) {
        if (treasures[i].getValue() > t.getValue()) {
            t = treasures[i];
        }
    }
    return t;
}

bool TreasureMap::saveToFile(const char *fileName) const {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    file << treasureCount << std::endl;
    for (size_t i = 0; i < treasureCount; i++) {
        treasures[i].saveToFile(file);
    }
    return true;
}

bool TreasureMap::readFromFile(const char *fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    file >> treasureCount;
    if (treasureCount > constants::MAX_TREASURES)
        treasureCount = constants::MAX_TREASURES;
    for (size_t i = 0; i < treasureCount; i++) {
        treasures[i].readFromFile(file);
    }
    return true;
}