#include "Browser.h"

void Browser::addPage(const Webpage& toAdd)
{
    *this += toAdd;
}

void Browser::removePage(const Webpage& toRemove)
{
    for (size_t i = 0; i < pagesCnt; i++)
    {
        if (strcmp(web[i].getIp(), toRemove.getIp()) == 0)
            *this-=(i);
    }
}

void Browser::operator+=(const Webpage& toAdd) 
{
    if (pagesCnt < MAX_WEBPAGES_CNT)
    {
        web[pagesCnt++] = toAdd;
    }
}

void Browser::operator-=(size_t index) 
{
    if(index < pagesCnt)
    {
        for (size_t i = index; i < pagesCnt - 1; i++)
            (Webpage)web[i] = web[i + 1];
    }
}

void Browser::printOpenPages() const
{
    for (size_t i = 0; i < pagesCnt; i++)
    {
        std::cout << web[i] << '\n';
    }
}
