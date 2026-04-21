#pragma once
#include <iostream>

class MulString {
private:
    char* data;
    int   length;

    void copyFrom(const MulString& other);
    void free();

public:
    MulString();
    MulString(const char* str);
    MulString(const MulString& other);
    MulString& operator=(const MulString& other);
    ~MulString();

    int  weight()    const;
    int  getLength() const;
    const char* getData() const;

    MulString& operator*=(int k);
    MulString& operator%=(const MulString& other);

    bool operator!=(const MulString& other) const;

    friend MulString  operator*(const MulString& s, int k);
    friend MulString  operator%(const MulString& a, const MulString& b);
    friend std::ostream& operator<<(std::ostream& os, const MulString& s);
};