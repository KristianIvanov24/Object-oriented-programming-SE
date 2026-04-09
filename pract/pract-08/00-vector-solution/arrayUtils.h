#pragma once
#include <cstdlib>

namespace arrayUtils
{
    void copy(auto* from, auto* into, size_t count)
    {
        if (!from || !into || from == into || count == 0)
        {
            return;
        }

        for (size_t i = 0; i < count; i++)
        {
            into[i] = from[i];
        }
    }
}