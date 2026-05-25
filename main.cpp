#include <iostream>
#include "NumberSeries.h"

int timesTwo(int x) { return x * 2; }
int plusOne(int x) { return x + 1; }

void demoNumberSeries() {
    std::cout << "=== NumberSeries ===\n";

    NumberSeries ns(1, timesTwo);

    std::cout << "a[0] = " << ns.get(0) << "\n";
    std::cout << "a[3] = " << ns.get(3) << "\n";
    std::cout << "a[5] = " << ns.get(5) << "\n";

    std::cout << "contains(4)?  " << (ns.contains(4) ? "yes" : "no") << "\n";  // yes
    std::cout << "contains(7)?  " << (ns.contains(7) ? "yes" : "no") << "\n";  // no

    ns.setStartValue(3);
    std::cout << "After setStart(3): a[2] = " << ns.get(2) << "\n";

    ns.setTransitionFunc(plusOne);
    std::cout << "After setFunc(+1): a[4] = " << ns.get(4) << "\n";
    std::cout << "\n";
}

int main() {
    demoNumberSeries();
    return 0;
}
