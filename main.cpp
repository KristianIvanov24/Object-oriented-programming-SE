#include <iostream>
#include "MultiSet.h"

int timesTwo(int x) { return x * 2; }
int plusOne(int x) { return x + 1; }

void demoMultiSet() {
    std::cout << "=== MultiSet ===\n";

    MultiSet ms(5, 2);
    ms.add(1); ms.add(1); ms.add(1);
    ms.add(3); ms.add(3);
    ms.add(5);

    ms.print();
    ms.printMemory();

    std::cout << "count(1) = " << ms.count(1) << "\n";
    std::cout << "count(2) = " << ms.count(2) << "\n";

    MultiSet ms2(5, 2);
    ms2.add(1); ms2.add(3); ms2.add(3); ms2.add(4);

    MultiSet inter = ms.intersection(ms2);
    std::cout << "Intersection: "; inter.print();

    MultiSet diff = ms.difference(ms2);
    std::cout << "Difference:   "; diff.print();

    MultiSet comp = ms.complement();
    std::cout << "Complement:   "; comp.print();

    ms.serialize("multiset.bin");
    MultiSet loaded = MultiSet::deserialize("multiset.bin");
    std::cout << "Deserialized: "; loaded.print();
}

int main() {
    demoMultiSet();
    return 0;
}
