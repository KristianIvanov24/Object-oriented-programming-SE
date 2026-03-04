#include <iostream>
#include <print>
//5
namespace constants
{
    const int AMOUNT_OF_COEFFICIENTS = 20;
    const int STUDENT_NAME = 32;
    const int AMOUNT_OF_STUDENTS = 50;
    const int AMOUNT_OF_DIGITS_IN_FN = 6;
}

namespace str
{
    void myStrCopy(const char* str, char* toCopy)
    {
        if (!str)return;
        while (*str)
        {
            *toCopy = *str;
            str++;
            toCopy++;
        }
        *toCopy = '\0';
    }
}

struct Polynomial
{
    double coefficients[constants::AMOUNT_OF_COEFFICIENTS] = { 0 };
    int extent;
};

Polynomial createPolynomial(const double* arr, int extent)
{
    if (extent > constants::AMOUNT_OF_COEFFICIENTS)
        return {};
    Polynomial polinom;
    for (int i = 0; i <= extent; ++i)
    {
        polinom.coefficients[i] = arr[i];
    }
    polinom.extent = extent;
    return polinom;
}

double calcilatePolynomial(const Polynomial& polinom, double x)
{
    double result = 0;
    double multiplayer = 1;
    for (int i = 0; i <= polinom.extent; ++i,multiplayer*=x)
    {
        result += polinom.coefficients[i] * multiplayer;
    }
    return result;
}

void additionOfPolynomials(Polynomial& pol1, const Polynomial& pol2)
{
    if (pol1.extent < pol2.extent)
    {
        pol1.extent = pol2.extent;
    }
    for (int i = 0; i <= pol2.extent; ++i)
    {
        pol1.coefficients[i] += pol2.coefficients[i];
    }
}

Polynomial additionOfPolynomialsWithReturning(const Polynomial& pol1, const Polynomial& pol2)
{
    Polynomial result;
    int biggerExtent = pol1.extent > pol2.extent ? pol1.extent : pol2.extent;
    result.extent = biggerExtent;
    for (int i = 0; i <= biggerExtent; ++i)
    {
        result.coefficients[i] = pol1.coefficients[i] + pol2.coefficients[i];
    }
    return result;
}

void subtractionOfPolynomials(Polynomial& pol1, const Polynomial& pol2)
{
    if (pol1.extent < pol2.extent)
    {
        pol1.extent = pol2.extent;
    }
    for (int i = pol1.extent; i >=0; --i)
    {
        if (i == pol1.extent && pol1.coefficients[i] == pol2.coefficients[i])
        {
            pol1.extent--;
        }
        pol1.coefficients[i] -= pol2.coefficients[i];
    }
}

Polynomial multiplicationOfPolynomials(const Polynomial& pol1, const Polynomial& pol2)
{
    Polynomial result;
    if (pol1.extent + pol2.extent > constants::AMOUNT_OF_COEFFICIENTS)
    {
        std::cout << "The multiplication of these two polynomials has surpassed the limits ";
        return {};
    }
    result.extent = pol1.extent + pol2.extent;
    for (int i = 0; i <= pol1.extent; ++i)
    {
        for (int j = 0; j <= pol2.extent; ++j)
        {
            result.coefficients[i + j] += pol1.coefficients[i] * pol2.coefficients[j];
        }
    }
    return result;
}

double absD(double n) 
{
    return (n < 0) ? -n : n;
}

void printPolynom(const Polynomial& pol)
{
    for (int i = pol.extent; i >= 0; --i)
    {
        double current = pol.coefficients[i];

        if (i == pol.extent)
        {
            if (current < 0) std::print("- {:.2f}", absD(current));
            else std::print("{:.2f}", current);
        }
        else
        {
            if (current > 0) std::print(" + {:.2f}", current);
            else if (current < 0) std::print(" - {:.2f}", absD(current));
        }

        if (i > 0)
        {
            std::print("x^{}", i);
        }
    }
    std::println("");
}

//6

int digitsInNum(size_t n)
{
    int digits = 0;
    while (n > 0)
    {
        digits++;
        n /= 10;
    }
    return digits;
}

enum class Specialty
{
    ComputerScience,
    SoftwareEngineering,
    Informatics,
    InformationSystems,
    AppliedMathematics,
    Statistics
};

struct Student
{
    char name[constants::STUDENT_NAME];
    size_t fn;
    double gpa;
    Specialty speciality;
};

struct Course
{
    Student students[constants::AMOUNT_OF_STUDENTS];
    size_t amountOfStudents = 0;
};

Student createStudent(const char* name, size_t fn, Specialty specialty)
{
    if (digitsInNum(fn) != constants::AMOUNT_OF_DIGITS_IN_FN)
        return{};
    Student s1;
    str::myStrCopy(name, s1.name);
    s1.fn = fn;
    s1.speciality = specialty;
    return s1;
}

void printSpecialty(const Specialty sp)
{
    switch (sp)
    {
    case Specialty::ComputerScience: std::cout << "Computer Science"; break;
    case Specialty::SoftwareEngineering: std::cout << "Software Engineering"; break;
    case Specialty::Informatics: std::cout << "Informatics"; break;
    case Specialty::InformationSystems: std::cout << "Information Systems"; break;
    case Specialty::AppliedMathematics: std::cout << "Applied Mathematics"; break;
    case Specialty::Statistics: std::cout << "Statistics"; break;
    default: std::cout << "Unknown"; break;
    }
}

void printStudent(const Student& s)
{
    std::cout << "Name: " << s.name;
    std::cout << "  FN: " << s.fn;
    std::cout << "  GPA = " << s.gpa;
    std::cout << "  Specialty:";
    printSpecialty(s.speciality);
}

void printCourse(const Course& c)
{
    std::cout << "Students in this course:\n";
    for (int i = 0; i < c.amountOfStudents; ++i)
    {
        printStudent(c.students[i]);
        std::cout << std::endl;
    }
}

void addStudent(Course& c, const Student& s)
{
    if (c.amountOfStudents >= constants::AMOUNT_OF_STUDENTS)
    {
        std::cout << "Your course is ful!";
        return;
    }
    c.students[c.amountOfStudents++] = s;
}

void swapStudent(Student& s1, Student& s2)
{
    Student temp = s1;
    s1 = s2;
    s2 = temp;
}

void removeStudentOnIndex(Course& c, int index)
{
    if (index > c.amountOfStudents)return;
    for (int i = index; i < c.amountOfStudents-1; ++i)
    {
        for (int j = i + 1; j < c.amountOfStudents; ++j)
        {
            swapStudent(c.students[i], c.students[j]);
        }
    }
    c.amountOfStudents--;
}

void removeStudent(Course& c, size_t fn)
{
    if (c.amountOfStudents == 0)return;
    int index=-1;
    for (int i = 0; i < c.amountOfStudents; ++i)
    {
        if (c.students[i].fn == fn)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        std::cout << "There is no student with the presentet FN in this course";
        return;
    }
    removeStudentOnIndex(c, index);
}

const void filter(const Course& c, bool(*p)(const Student*))
{
    for (int i = 0; i < c.amountOfStudents; ++i)
    {
        if (p(&c.students[i]))
        {
            printStudent(c.students[i]);
        }
    }
}

void sort(Course& c, bool(*p)(const Student*, const Student*))
{
    for (int i = 0; i < c.amountOfStudents-1; ++i)
    {
        for (int j = i + 1; j < c.amountOfStudents; ++j)
        {
            if (p(&c.students[i], &c.students[j]))
            {
                swapStudent(c.students[i], c.students[j]);
            }
        }
    }
}

