#include <iostream>
#include "GradeReport.h"
#include "Validation.h"

int main() {
    int g1[] = { 85, 90, 57, 92, 88 };
    int g2[] = { 70, 65, 80, 95 };
    int bad[] = { 85, 150, -5 };

    GradeReport a(g1, 5, "Grade A");
    GradeReport b(g2, 4, "Grade B");
    GradeReport invalid(bad, 3, "Bad");

    if (!a.isValid()) {
        std::cout << "A is not valid!\n";
        return -1;
    }

    if (!b.isValid()) {
        std::cout << "B is not valid!\n";
        return -1;
    }

    if (!invalid.isValid())
        std::cout << "Invalid has not been created!\n";

    std::cout << a.getName() << "\n";
    std::cout << a.getAverage() << "\n";

    GradeReport combined = GradeReport::merge(a, b);
    if (combined.isValid())
        std::cout << combined.getName() << "\n";
        std::cout << combined.getAverage() << "\n";
}