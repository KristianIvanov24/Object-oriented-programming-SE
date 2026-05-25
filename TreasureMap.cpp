#include "TreasureMap.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#pragma warning(disable : 4996)

TreasureMap::TreasureMap() : m_count(0) {}

double TreasureMap::distanceFromOrigin(const Treasure& t) const {
    return sqrt((double)(t.x * t.x + t.y * t.y));
}

bool TreasureMap::addTreasure(const char* name, int x, int y, int value) {
    if (m_count >= Constants::MAX_TREASURES) {
        std::cout << "Map is full!" << std::endl;
        return false;
    }
    if (!Validations::isValidName(name)) {
        std::cout << "Invalid name!" << std::endl;
        return false;
    }
    if (!Validations::isValidCoordinates(x, y)) {
        std::cout << "Invalid coordinates!" << std::endl;
        return false;
    }
    if (!Validations::isValidValue(value)) {
        std::cout << "Invalid value!" << std::endl;
        return false;
    }
    strncpy(m_treasures[m_count].name, name, Constants::MAX_NAME_LEN);
    m_treasures[m_count].name[Constants::MAX_NAME_LEN] = '\0';
    m_treasures[m_count].x = x;
    m_treasures[m_count].y = y;
    m_treasures[m_count].value = value;
    m_count++;
    return true;
}

bool TreasureMap::removeByName(const char* name) {
    for (int i = 0; i < m_count; i++) {
        if (strcmp(m_treasures[i].name, name) == 0) {
            for (int j = i; j < m_count - 1; j++)
                m_treasures[j] = m_treasures[j + 1];
            m_count--;
            return true;
        }
    }
    std::cout << "Treasure not found!" << std::endl;
    return false;
}

Treasure* TreasureMap::findByCoordinates(int x, int y) {
    for (int i = 0; i < m_count; i++) {
        if (m_treasures[i].x == x && m_treasures[i].y == y)
            return &m_treasures[i];
    }
    return nullptr;
}

void TreasureMap::sortByValue() {
    for (int i = 0; i < m_count - 1; i++) {
        for (int j = 0; j < m_count - i - 1; j++) {
            if (m_treasures[j].value < m_treasures[j + 1].value) {
                Treasure temp = m_treasures[j];
                m_treasures[j] = m_treasures[j + 1];
                m_treasures[j + 1] = temp;
            }
        }
    }
}

void TreasureMap::sortByDistance() {
    for (int i = 0; i < m_count - 1; i++) {
        for (int j = 0; j < m_count - i - 1; j++) {
            if (distanceFromOrigin(m_treasures[j]) > distanceFromOrigin(m_treasures[j + 1])) {
                Treasure temp = m_treasures[j];
                m_treasures[j] = m_treasures[j + 1];
                m_treasures[j + 1] = temp;
            }
        }
    }
}

void TreasureMap::print() const {
    for (int i = 0; i < m_count; i++) {
        std::cout << m_treasures[i].name
            << " (" << m_treasures[i].x << "," << m_treasures[i].y << ")"
            << " value:" << m_treasures[i].value
            << std::endl;
    }
}

Treasure TreasureMap::getMostValuable() const {
    int maxIdx = 0;
    for (int i = 1; i < m_count; i++) {
        if (m_treasures[i].value > m_treasures[maxIdx].value)
            maxIdx = i;
    }
    return m_treasures[maxIdx];
}

void TreasureMap::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing" << std::endl;
        return;
    }
    file << m_count << "\n";
    for (int i = 0; i < m_count; i++) {
        file << m_treasures[i].name << "\n";
        file << m_treasures[i].x << "\n";
        file << m_treasures[i].y << "\n";
        file << m_treasures[i].value << "\n";
    }
}

void TreasureMap::readFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading" << std::endl;
        return;
    }
    m_count = 0;
    int count;
    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++) {
        file.getline(m_treasures[i].name, 33);
        file >> m_treasures[i].x;
        file >> m_treasures[i].y;
        file >> m_treasures[i].value;
        file.ignore();
        m_count++;
    }
}