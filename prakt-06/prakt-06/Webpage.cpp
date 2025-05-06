#include "Webpage.h"
#pragma warning (disable:4996)

void Webpage::free()
{
    delete[] adress;
    delete[] ip;
}

void Webpage::moveFrom(Webpage&& other)
{
    ip = other.ip;
    adress = other.adress;

    other.ip = nullptr;
    other.adress = nullptr;
}

void Webpage::copyFrom(const Webpage& other)
{
    ip = new char[strlen(other.ip) + 1];
    strcpy(ip, other.ip);

    adress = new char[strlen(other.adress) + 1];
    strcpy(adress, other.adress);
}

Webpage::Webpage()
{
    ip = adress = nullptr;
}

Webpage::Webpage(const Webpage& other)
{
    copyFrom(other);
}

Webpage::Webpage(Webpage&& other)
{
    moveFrom(std::move(other));
}

Webpage& Webpage::operator=(const Webpage& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Webpage& Webpage::operator=(Webpage&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Webpage::~Webpage()
{
    free();
}

const char* Webpage::getIp() const
{
    return ip;
}

const char* Webpage::getAdress() const
{
    return adress;
}

void Webpage::setIp(const char* str)
{
    if (str)
    {
        ip = new char[strlen(str) + 1];
        strcpy(ip, str);
    }
    else
    {
        ip = nullptr;
    }
}

void Webpage::setAdress(const char* str)
{
    if (str)
    {
        adress = new char[strlen(str) + 1];
        strcpy(adress, str);
    }
    else
    {
        adress = nullptr;
    }
}

std::ostream& operator<<(std::ostream& os, const Webpage& other)
{
    os << other.adress << '\n' << other.ip;

    return os;
}

std::istream& operator>>(std::istream& is, Webpage& other) 
{
    char buff[1024];
    is >> buff;
    other.setAdress(buff);
    is >> buff;
    other.setIp(buff);

    return is;
}


