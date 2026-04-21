#pragma warning(disable : 4996)
#include "MulString.h"
#include <cstring>
#include <cstdlib>


void MulString::copyFrom(const MulString& other) {
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}
void MulString::free() {
    delete[] data;
    data = nullptr;
    length = 0;
}


MulString::MulString() : length(0) {
    data = new char[1];
    data[0] = '\0';
}
MulString::MulString(const char* str) {
    length = (int)strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}
MulString::MulString(const MulString& other) { copyFrom(other); }
MulString& MulString::operator=(const MulString& other) {
    if (this != &other) { free(); copyFrom(other); }
    return *this;
}
MulString::~MulString() { free(); }


int MulString::weight() const {
    int w = 0;
    for (int i = 0; i < length; i++) w += (unsigned char)data[i];
    return w;
}
int MulString::getLength() const { return length; }
const char* MulString::getData() const { return data; }


MulString& MulString::operator*=(int k) {
    if (k <= 0) { free(); data = new char[1]; data[0] = '\0'; return *this; }
    int    newLen = length * k;
    char* buf = new char[newLen + 1];
    buf[0] = '\0';
    for (int i = 0; i < k; i++) strcpy(buf + i * length, data);
    delete[] data;
    data = buf;
    length = newLen;
    return *this;
}


MulString& MulString::operator%=(const MulString& other) {
    *this = *this % other;
    return *this;
}


bool MulString::operator!=(const MulString& other) const {
    return weight() != other.weight();
}


MulString operator*(const MulString& s, int k) {
    MulString result = s;
    result *= k;
    return result;
}

MulString operator%(const MulString& a, const MulString& b) {

    bool seen[256] = {};
    int  resLen = 0;


    for (int i = 0; i < a.length; i++)
        if (!seen[(unsigned char)a.data[i]]) { seen[(unsigned char)a.data[i]] = true; resLen++; }
    for (int i = 0; i < b.length; i++)
        if (!seen[(unsigned char)b.data[i]]) { seen[(unsigned char)b.data[i]] = true; resLen++; }

    char* buf = new char[resLen + 1];
    int   idx = 0;


    bool added[256] = {};
    for (int i = 0; i < a.length; i++) {
        unsigned char c = (unsigned char)a.data[i];
        if (!added[c]) { buf[idx++] = a.data[i]; added[c] = true; }
    }
    for (int i = 0; i < b.length; i++) {
        unsigned char c = (unsigned char)b.data[i];
        if (!added[c]) { buf[idx++] = b.data[i]; added[c] = true; }
    }
    buf[idx] = '\0';

    MulString result(buf);
    delete[] buf;
    return result;
}

std::ostream& operator<<(std::ostream& os, const MulString& s) {
    return os << s.data;
}