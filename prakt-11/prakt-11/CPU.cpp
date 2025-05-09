#include "CPU.h"

CPU::CPU(const char* lable, unsigned short cores, unsigned short speed) : Component(lable)
{
    setCores(cores);
    clockSpeed = speed;
}

void CPU::setCores(unsigned short cores)
{
    if (cores < constants::MAXCoresCnt && cores > constants::MINCoresCnt)
        this->cores = cores;

    else
    {
        throw std::invalid_argument("invalid cores");
    }
}

Component* CPU::clone() const
{
    return new CPU(*this);
}

double CPU::price() const
{
    return cores * constants::coresPrice;
}

void CPU::output(std::ostream& os) const
{
}

void CPU::output(std::ostream& os) const
{
    std::cout << lable << ' ' << cores << ' ' << clockSpeed << '\n';
}


