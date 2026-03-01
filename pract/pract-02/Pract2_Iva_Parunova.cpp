//1

//#include <iostream>
//
//struct Complex {
//    double real;
//    double imag;
//};
//
//Complex addComplex(const Complex& lhs, const Complex& rhs) {
//    return { lhs.real + rhs.real, lhs.imag + rhs.imag };
//}
//
//Complex multComplex(const Complex& lhs, const Complex& rhs) {
//    double real = lhs.real * rhs.real - lhs.imag * rhs.imag;
//    double imag= lhs.real * rhs.real + lhs.imag * rhs.imag;
//    return { real, imag };
//}
//
//void print(const Complex& a) {
//    std::cout<<a.real << "+" << a.imag << "i" ;
//}
//
//int main()
//{
//    double real1, real2, imag1, imag2;
//    std::cin >> real1>>real2>> imag1>> imag2;
//    Complex number1;
//    number1.real = real1;
//    number1.imag = imag1;
//    Complex number2;
//    number1.real = real2;
//    number1.imag = imag2;
//    addComplex(number1, number2);
//    multComplex(number1, number2);
//    print(number1);
//    return 0;
//}

//2

//#include <iostream>
//
//struct Point {
//	double OX;
//	double OY;
//};
//
//void SpaceBetween2P(const Point& P1, const Point& P2) {
//	double OX = P2.OX - P1.OX;
//	double OY = P2.OY - P2.OY;
//	double result = sqrt(OX * OX + OY * OY);
//	std::cout << result;
//}
//
//int main() {
//	Point myPoint1, myPoint2;
//	double OX1, OY1, OX2, OY2;
//	std::cin >> OX1 >> OY1>>OX2>>OY2;
//	myPoint1.OX = OX1;
//	myPoint1.OY = OY1;
//	myPoint2.OX = OX2;
//	myPoint2.OY = OY2;
//	std::cout << "(" << myPoint1.OX << ";" << myPoint1.OY << ")";
//	std::cout << "(" << myPoint2.OX << ";" << myPoint2.OY << ")";
//	SpaceBetween2P(myPoint1, myPoint2);
//	return 0;
//}

//3

//#include <iostream>
//struct Triangle {
//	double side1;
//	double side2;
//	double side3;
//};
//
//void Parameter(const Triangle& T) {
//	double parameter = T.side1 + T.side2 + T.side3;
//	std::cout << parameter<<std::endl;
//}
//
//void Area(const Triangle& T) {
//	std::cout << "Area calculations:" << std::endl;
//
//	std::cout << "Using side1: " << (T.side1 / 2.0) << " * h1" << std::endl;
//	std::cout << "Using side2: " << (T.side2 / 2.0) << " * h2" << std::endl;
//	std::cout << "Using side3: " << (T.side3 / 2.0) << " * h3" << std::endl;
//}
//enum TypeOfT {
//	Equilateral,
//	Isosceles,
//	Scalene
//};
//
//int TypeOfT(const Triangle& T) {
//	if (T.side1 != T.side2 != T.side3) return { TypeOfT::Scalene };
//	else if (T.side1 == T.side2 == T.side3) return { TypeOfT::Equilateral };
//	else if (T.side1 == T.side2 || T.side2 == T.side3 || T.side1 == T.side3) return { TypeOfT::Isosceles };
//}
//
//int main() {
//	Triangle myTriangle;
//	double side1, side2, side3;
//	std::cin >> side1 >> side2 >> side3;
//	myTriangle.side1 = side1;
//	myTriangle.side2 = side2;
//	myTriangle.side3 = side3;
//	Parameter(myTriangle);
//	std::cout<<TypeOfT(myTriangle)<<std::endl;
//	Area(myTriangle);
//}

//4
//#include <iostream>
//
//namespace constants {
//	const unsigned TITLE_LEN = 100;
//	const unsigned SINGER_LEN = 100;
//	const unsigned SONGS_MAX = 64;
//};
//
//enum genre {
//	Rock,
//	Pop,
//	Trash_Metal,
//	Kpop,
//	Chalga
//};
//
//struct Song {
//	char title[constants::TITLE_LEN];
//	char singer[constants::SINGER_LEN];
//	genre genre;
//	unsigned rating;
//	unsigned listen_count;
//};
//
//struct Playlist {
//	Song songs[constants::SONGS_MAX];
//	int currentCount = 0;
//};
//
//void addSong(Playlist& Playlist, const Song& newSong) {
//	if (Playlist.currentCount < constants::SONGS_MAX) {
//		Playlist.songs[Playlist.currentCount] = newSong;
//		Playlist.currentCount++;
//	}
//	else {
//		std::cout << "Playlist is full!" << std::endl;
//	}
//}
//
//bool isKpop(const Song& s) {
//	return s.genre == Kpop;
//}
//
//bool sortByRating(const Song& a, const Song& b) {
//	return a.rating > b.rating;
//}
//
//Song* findSong(Playlist& Playlist, bool (*predicate)(const Song&)) {
//	for (int i = 0; i < Playlist.currentCount; i++) {
//		if (predicate(Playlist.songs[i])) {
//			return &Playlist.songs[i];
//		}
//	}
//	return nullptr;
//}
//
//void sortPlaylist(Playlist& p, bool (*compare)(const Song&, const Song&)) {
//	for (int i = 0; i < p.currentCount - 1; i++) {
//		for (int j = 0; j < p.currentCount - i - 1; j++) {
//			if (compare(p.songs[j + 1], p.songs[j])) {
//				Song temp = p.songs[j];
//				p.songs[j] = p.songs[j + 1];
//				p.songs[j + 1] = temp;
//			}
//		}
//	}
//}
//
//void printPlaylist(const Playlist& p) {
//    std::cout << "\n--- CURRENT PLAYLIST ---\n";
//    for (int i = 0; i < p.currentCount; i++) {
//        std::cout << i + 1 << ". " << p.songs[i].singer << " - " << p.songs[i].title
//            << " (Rating: " << p.songs[i].rating << ")\n"
//            << "(Genre: "<<p.songs[i].genre<<")\n"
//            << "(Listen count: "<<p.songs[i].listen_count<<")\n";
//    }
//    std::cout << "------------------------\n";
//}
//
//int main() {
//    Playlist myPlaylist;
//    bool anotherSong = true;
//
//    while (anotherSong) {
//        Song newSong;
//        int genreInt;
//
//        std::cout << "\n--- Add a song ---\n";
//
//        std::cout << "Enter title: ";
//        std::cin.getline(newSong.title, constants::TITLE_LEN);
//
//        std::cout << "Enter singer: ";
//        std::cin.getline(newSong.singer, constants::SINGER_LEN);
//
//        std::cout << "Enter genre (0-Rock, 1-Pop, 2-Trash, 3-Kpop, 4-Chalga): ";
//        std::cin >> genreInt;
//        newSong.genre = (enum genre)genreInt;
//
//        std::cout << "Enter rating (0-10): ";
//        std::cin >> newSong.rating;
//
//        std::cout << "Enter listens: ";
//        std::cin >> newSong.listen_count;
//
//        addSong(myPlaylist, newSong);
//
//        std::cout << "Do you want to add another song - yes(1) or no(0)? ";
//        int answer;
//        std::cin >> answer;
//        anotherSong = (answer == 1);
//
//        std::cin.ignore();
//    }
//
//    printPlaylist(myPlaylist);
//
//    std::cout << "\nSearching for a Kpop song...\n";
//    Song* result = findSong(myPlaylist, isKpop);
//
//    if (result) {
//        std::cout << "Found: " << result->singer << " - " << result->title << "\n";
//    }
//    else {
//        std::cout << "No Kpop songs in the list.\n";
//    }
//
//    std::cout << "\nSorting playlist by rating...\n";
//    sortPlaylist(myPlaylist, sortByRating);
//
//    if (myPlaylist.currentCount > 0) {
//        std::cout << "Top rated song: " << myPlaylist.songs[0].title
//            << " with rating " << myPlaylist.songs[0].rating << std::endl;
//    }
//
//    return 0;
//}

//5
//#include <iostream>
//
//namespace constants {
//	const unsigned MAX_SIZE = 20;
//}
//
//struct Polynomial {
//    double coefficients[constants::MAX_SIZE] = { 0.0 };
//	unsigned degree = 0;
//};
//
//Polynomial createPolynomial(double c[], int d) {
//    Polynomial p;
//    p.degree = d;
//    while (p.degree >= constants::MAX_SIZE) {
//        std::cout << "The degree of the polynomial should be between 0 and 19!";
//        std::cin >> d;
//        p.degree = d;
//    }
//    for (int i = 0; i <= p.degree; i++) {
//        p.coefficients[i] = c[i];
//    }
//    return p;
//}
//
//double evaluate(Polynomial p, double x) {
//    double result = 0;
//    for (int i = p.degree; i >= 0; i--) {
//        result = result * x + p.coefficients[i];
//    }
//    return result;
//}
//
//Polynomial add(Polynomial p1, Polynomial p2) {
//    Polynomial result;
//    unsigned maxDeg = 0;
//    maxDeg = (p1.degree > p2.degree) ? p1.degree : p2.degree;
//    result.degree = maxDeg;
//    for (int i = 0; i <= result.degree; ++i) {
//        result.coefficients[i] = p1.coefficients[i] + p2.coefficients[i];
//    }
//    return result;
//}
//
//Polynomial subtract(Polynomial p1, Polynomial p2) {
//    Polynomial result;
//    unsigned maxDeg = 0;
//    maxDeg = (p1.degree > p2.degree) ? p1.degree : p2.degree;
//    result.degree = maxDeg;
//    for (int i = 0; i <= result.degree; i++) {
//        result.coefficients[i] = p1.coefficients[i] - p2.coefficients[i];
//    }
//    return result;
//}
//
//Polynomial multiply(Polynomial p1, Polynomial p2) {
//    Polynomial result;
//    int newDegree = p1.degree + p2.degree;
//    result.degree = newDegree;
//    if (result.degree >= constants::MAX_SIZE) {
//        std::cout << "The degree of the polynomial should be between 0 and 19!";
//    }
//    else {
//        for (int i = 0; i <= p1.degree; i++) {
//            for (int j = 0; j <= p2.degree; j++) {
//                if (i + j < constants::MAX_SIZE) {
//                    result.coefficients[i + j] += p1.coefficients[i] * p2.coefficients[j];
//                }
//            }
//        }
//        return result;
//    }
//}
//
//void printPolynomial(Polynomial p) {
//    for (int i = p.degree; i >= 0; i--) {
//        std::cout << p.coefficients[i] << "x^" << i;
//        if (i > 0) std::cout << " + ";
//    }
//    std::cout << std::endl;
//}
//
//int main() {
//    double c1[constants::MAX_SIZE] = { 0 };
//    double c2[constants::MAX_SIZE] = { 0 };
//    unsigned d1, d2;
//
//    std::cout << "Write down the degree of the first polynomial: ";
//    std::cin >> d1;
//    std::cout << "Write down the coefficients of the first polynomial (0-n): ";
//    for (int i = 0; i <= d1; i++) {
//        std::cin >> c1[i];
//    }
//    
//    std::cout << "Write down the degree of the second polynomial: ";
//    std::cin >> d2;
//    std::cout << "Write down the coefficients of the second polynomial (0-n): ";
//    for (int i = 0; i <= d2; i++) {
//        std::cin >> c2[i];
//    }
//
//    Polynomial p1 = createPolynomial(c1, d1);
//    Polynomial p2 = createPolynomial(c2, d2);
//
//    std::cout << "P1: "; printPolynomial(p1);
//    std::cout << "P2: "; printPolynomial(p2);
//
//    Polynomial sum = add(p1, p2);
//    std::cout << "Sum: "; printPolynomial(sum);
//
//    Polynomial prod = multiply(p1, p2);
//    std::cout << "Product: "; printPolynomial(prod);
//
//    double x;
//    std::cout << "Enter a x with which the program will evaluate the polynomials: ";
//    std::cin >> x;
//
//    std::cout << "Value of P1 at x="<< x << " : " << evaluate(p1, x) << std::endl;
//    std::cout << "Value of P2 at x=" << x << " : " << evaluate(p2, x) << std::endl;
//
//    return 0;
//}

//6 
#include <iostream>

void Strcpy(char* dest, const char* source)
{
	if (!source)
		return;

	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
}

namespace constants {
	const unsigned NAME_LEN = 33;
	const unsigned MAX_STUDENTS = 50;
}

enum Major {
	ComputerScience,
	SoftwareEngineering,
	Informatics,
	InformationSystems,
	AppliedMathematics,
	Mathematics
};

const char* majorToString(Major m) {
	switch (m) {
	case Major::ComputerScience: return "Computer Science";
	case Major::SoftwareEngineering: return "Software Engineering";
	case Major::Informatics: return "Informatics";
	case Major::InformationSystems: return "Information Systems";
	case Major::AppliedMathematics: return "Applied Mathematics";
	case Major::Mathematics: return "Mathematics";
	default: return "Unknown";
	}
}

struct Student {
	char name[constants::NAME_LEN];
	int fn;
	double average_grade;
	Major major;
};

struct Course {
	Student students[constants::MAX_STUDENTS];
	unsigned num_students=0;
};

Student createStudent(const char* name, int fn, double average_grade, Major major) {
	Student s;
	Strcpy(s.name, name);
	s.name[32] = '\0';
	s.fn = fn;
	s.average_grade = average_grade;
	s.major = major;
	return s;
}

void printStudent(const Student& s) {
	std::cout << "Name: " << s.name
		<< " | FN: " << s.fn
		<< " | Grade: " << s.average_grade
		<< " | Major: " << majorToString(s.major) << std::endl;
}

void printCourse(const Course& c) {
	std::cout << "--- Course List (" << c.num_students << " students) ---" << std::endl;
	for (int i = 0; i < c.num_students; i++) {
		printStudent(c.students[i]);
	}
}

bool addStudent(Course& c, const Student& s) {
	if (c.num_students >= constants::MAX_STUDENTS) {
		std::cout << "Course is full!" << std::endl;
		return false;
	}
	c.students[c.num_students++] = s;
	return true;
}

bool removeStudent(Course& c, int fn) {
	for (int i = 0; i < c.num_students; i++) {
		if (c.students[i].fn == fn) {
			c.students[i] = c.students[c.num_students - 1];
			c.num_students--;
			return true;
		}
	}
	return false;
}

void filterStudents(const Course& c, bool (*predicate)(const Student&)) {
	std::cout << "--- Filtered Students ---" << std::endl;
	for (int i = 0; i < c.num_students; i++) {
		if (predicate(c.students[i])) {
			printStudent(c.students[i]);
		}
	}
}

void sortCourse(Course& c, bool (*compare)(const Student&, const Student&)) {
	if (c.num_students < 2) return;
	for (int i = 0; i < c.num_students - 1; i++) {
		for (int j = 0; j < c.num_students - i - 1; j++) {
			if (!compare(c.students[j], c.students[j + 1])) {
				Student temp = c.students[j];
				c.students[j] = c.students[j + 1];
				c.students[j + 1] = temp;
			}
		}
	}
}

bool isExcellent(const Student& s) {
	return s.average_grade >= 5.50;
}

bool compareByGrade(const Student& a, const Student& b) {
	return a.average_grade > b.average_grade;
}

int main() {
	Course fmiCourse = { {}, 0 };

	Student s1 = createStudent("Ivan Ivanov", 123456, 5.75, Major::SoftwareEngineering);
	Student s2 = createStudent("Maria Petrova", 654321, 4.20, Major::ComputerScience);
	Student s3 = createStudent("Georgi Georgiev", 111222, 5.90, Major::Informatics);

	addStudent(fmiCourse, s1);
	addStudent(fmiCourse, s2);
	addStudent(fmiCourse, s3);

	std::cout << "Original course:" << std::endl;
	printCourse(fmiCourse);

	std::cout << "\nSorting by grade:" << std::endl;
	sortCourse(fmiCourse, compareByGrade);
	printCourse(fmiCourse);

	std::cout << "\nFiltering excellent students:" << std::endl;
	filterStudents(fmiCourse, isExcellent);

	std::cout << std::endl;
	std::cout << "Removeing student 2:" << std::endl;
	removeStudent(fmiCourse, 654321);
	printCourse(fmiCourse);

	return 0;
}