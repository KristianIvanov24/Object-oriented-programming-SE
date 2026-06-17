//1

#include <iostream>
#include <fstream>

//int main() {
//	std::ifstream file("myfile.txt", 1);
//	if (!file.is_open()) {
//		std::cout << "Error!";
//		return -1;
//	}
//	while (!file.eof()) {
//		char buffer[1024];
//		file.getline(buffer, 1024);
//		std::cout << buffer;
//	}
//	file.close();
//}

//2

//int Combine(std::ifstream& file1, std::ofstream& file2) {
//    if (!file1.is_open()) {
//        std::cout<<"File 1 is not open!\n";
//        return -1;
//    }
//    if (!file2.is_open()) {
//        std::cout << "File 2 is not open!\n";
//        return -1;
//    }
//    int a, b;
//    file1 >> a >> b;
//    file1.close();
//
//    file2 << "Sum: " << (a + b)<< "\n";
//    file2.close();
//    return 0;
//}
//
//int main() {
//    std::ifstream in("data.txt");
//    std::ofstream out("result.txt");
//    Combine(in, out);
//    return 0;
//}

//3

//int main() {
//    std::ifstream fileIn("task3.txt");
//    if (!fileIn) {
//        std::cout << "Error opening file!";
//        return -1;
//    }
//
//    fileIn.seekg(0, std::ios::end);
//    long long halfSize = fileIn.tellg() / 2;
//    fileIn.seekg(0, std::ios::beg);
//
//    char* buffer = new char[halfSize];
//    fileIn.read(buffer, halfSize);
//    fileIn.close();
//
//    std::ofstream fileOut("task3.txt", std::ios::trunc);
//    if (!fileIn) {
//        std::cout << "Error opening file!";
//        return -1;
//    }
//    fileOut.write(buffer, halfSize);
//    fileOut.close();
//
//    delete[] buffer;
//    return 0;
//}

//4

//int main()
//{
//	std::ifstream fileIn("task3.txt");
//	if (!fileIn) {
//		std::cout << "Error! Cant open file";
//		return -1;
//	}
//	unsigned new_line = 0;
//	unsigned words = 0;
//	unsigned file_size = 0;
//
//	size_t CurPoss = fileIn.tellg();
//	fileIn.seekg(0, std::ios::end);
//	file_size = fileIn.tellg();
//
//	fileIn.seekg(0, std::ios::beg);
//	char buffer[1024];
//	fileIn.read(buffer, (file_size < 1024 ? file_size : 1024));
//
//	int count_new_line = 0;
//	for (int i = 0; i < file_size; i++) {
//		if (buffer[i] == '\n') {
//			count_new_line++;
//		}
//	}
//	new_line = count_new_line+1;
//
//	int count_words = 0;
//	for (int i = 0; i < file_size; i++) {
//		if (buffer[i] == ' ' || buffer[i] == '\n') {
//			count_words++;
//		}
//	}
//	words = count_words + 1;
//	fileIn.close();
//
//	std::ofstream fileOut("task3.txt", std::ios::out | std::ios::app);
//	if (!fileOut) {
//		std::cout << "Error! Cant open file";
//		return -1;
//	}
//	fileOut << std::endl << "New lines count: " << new_line << "\nWords count: " << words << "\nFile size: " << file_size;
//	fileOut.close();
//	
//	return 0;
//}

//5
//
//namespace constants {
//	const unsigned VECTOR_MAX_COUNT = 50;
//}
//
//struct Vector {
//	int Ox;
//	int Oy;
//	int Oz;
//};
//
//struct VectorSpace {
//	unsigned vect_count = 0;
//	Vector* vectors_arr[constants::VECTOR_MAX_COUNT] = {nullptr};
//};
//
//Vector makeVector(int x, int y, int z) {
//	Vector vector;
//	vector.Ox = x;
//	vector.Oy = y;
//	vector.Oz = z;
//	return vector;
//}
//
//void addToVectorSpace(VectorSpace& vectorSpace, const Vector& vector) {
//	if (vectorSpace.vect_count >= constants::VECTOR_MAX_COUNT) {
//		std::cout << "The vector space is full!" << std::endl;
//		return;
//	}
//	vectorSpace.vectors_arr[vectorSpace.vect_count] = new Vector(vector);
//	vectorSpace.vect_count++;
//}
//
//void serializeVector(std::ofstream& ofs, Vector& vector) {
//	if (!ofs) return;
//	ofs << "<" << vector.Ox << "," << vector.Oy << "," << vector.Oz << ">";
//}
//
//Vector deserializeVector(std::ifstream& ifs) {
//	Vector v = { 0, 0, 0 };
//	char ignore;
//	ifs >> ignore >> v.Ox >> ignore >> v.Oy >> ignore >> v.Oz >> ignore;
//	return v;
//}
//
//void serializeVectorSpace(const char* fileName, const VectorSpace& vectorSpace) {
//	std::ofstream ofs(fileName);
//	if (!ofs) return;
//	ofs << vectorSpace.vect_count;
//
//	for (int i = 0; i < vectorSpace.vect_count; i++) {
//		ofs << " ";
//		serializeVector(ofs, *vectorSpace.vectors_arr[i]);
//	}
//	ofs.close();
//}
//
//VectorSpace deserializeVectorSpace(const char* fileName) {
//	std::ifstream ifs(fileName);
//	VectorSpace vs = { 0, {nullptr} };
//	if (!ifs) return vs;
//	unsigned size;
//	if (!(ifs >> size)) return vs;
//	for (int i = 0; i < size; i++) {
//		Vector v = deserializeVector(ifs);
//		addToVectorSpace(vs, v);
//	}
//
//	ifs.close();
//	return vs;
//}
//
//void clearVectorSpace(VectorSpace& vs) {
//	for (int i = 0; i < vs.vect_count; i++) {
//		delete vs.vectors_arr[i];
//		vs.vectors_arr[i] = nullptr;
//	}
//	vs.vect_count = 0;
//}
//
//int main() {
//	VectorSpace mySpace = { 0, {nullptr} };
//
//	addToVectorSpace(mySpace, makeVector(1, 2, 3));
//	addToVectorSpace(mySpace, makeVector(10, 20, 30));
//	addToVectorSpace(mySpace, makeVector(-5, 0, 15));
//
//	std::cout << "Saving " << mySpace.vect_count << " vectors to file..." << std::endl;
//
//	serializeVectorSpace("space.txt", mySpace);
//
//	VectorSpace loadedSpace = deserializeVectorSpace("space.txt");
//
//	std::cout << "Loaded " << loadedSpace.vect_count << " vectors from file:" << std::endl;
//
//	for (int i = 0; i < loadedSpace.vect_count; i++) {
//		Vector v = *loadedSpace.vectors_arr[i];
//		std::cout << "Vector " << i+1 << ": <"
//			<< v.Ox << ", " << v.Oy << ", " << v.Oz << ">" << std::endl;
//	}
//	clearVectorSpace(mySpace);
//	clearVectorSpace(loadedSpace);
//	return 0;
//}

//6
//
//namespace constants {
//	const unsigned OWNER_NAME_LEN = 25;
//	const unsigned FINES_MAX_COUNT = 50;
//}
//
//enum class Brand {
//	Mercedes,
//	Honda,
//	Hundai
//};
//
//struct Car {
//	Brand brand;
//	char owner[constants::OWNER_NAME_LEN];
//	unsigned average_speed = 0;
//	double fines[constants::FINES_MAX_COUNT] = { 0 };
//	unsigned fines_count = 0;
//};
//
//double fines_sum(const Car& car) {
//	double fines_sum = 0;
//	for (int i = 0; i < constants::FINES_MAX_COUNT; i++) {
//		fines_sum += car.fines[i];
//	}
//	return fines_sum;
//}
//
//void addFine(Car& car, double new_fine) {
//	if (car.fines_count >= constants::FINES_MAX_COUNT) {
//		std::cout << "Maximum fines reached!";
//		return;
//	}
//	else {
//		for (int i = 0; i < constants::FINES_MAX_COUNT; i++) {
//			if (car.fines[i] == 0) {
//				car.fines[i] = new_fine;
//				car.fines_count++;
//			}
//		}
//	}
//}
//
//const char* getBrandName(Brand b) {
//	switch (b) {
//	case Brand::Mercedes: return "Mercedes";
//	case Brand::Honda: return "Honda";
//	case Brand::Hundai: return "Hundai";
//	default: return "Unknown";
//	}
//}
//
//void printCar(const Car& car) {
//	std::cout << "Owner: " << car.owner
//		<< " | Brand: " << getBrandName(car.brand)
//		<< " | Avg Speed: " << car.average_speed
//		<< " | Fines count: " << car.fines_count
//		<< " | Total Fines: " << fines_sum(car) << std::endl;
//}
//
//void writeCarToFile(std::ofstream& out, const Car& c) {
//    if (out.is_open()) {
//        out.write((const char*)&c, sizeof(Car));
//    }
//}
//
//void readCarFromFile(std::ifstream& in, Car& c) {
//    if (in.is_open()) {
//        in.read((char*)&c, sizeof(Car));
//    }
//}
//
//void sortCarsInFile(const char* filename) {
//    std::ifstream in(filename, std::ios::binary);
//    if (!in) return;
//
//    in.seekg(0, std::ios::end);
//    int fileSize = in.tellg();
//    int count = fileSize / sizeof(Car);
//    in.seekg(0, std::ios::beg);
//
//    if (count <= 0) return;
//
//    Car* cars = new Car[count];
//
//    for (int i = 0; i < count; i++) {
//        in.read((char*)&cars[i], sizeof(Car));
//    }
//    in.close();
//
//    for (int i = 0; i < count - 1; i++) {
//        for (int j = 0; j < count - i - 1; j++) {
//            if (cars[j].average_speed > cars[j + 1].average_speed) {
//                Car temp = cars[j];
//                cars[j] = cars[j + 1];
//                cars[j + 1] = temp;
//            }
//        }
//    }
//
//    std::ofstream out(filename, std::ios::binary | std::ios::trunc);
//    for (int i = 0; i < count; i++) {
//        out.write((const char*)&cars[i], sizeof(Car));
//    }
//    out.close();
//
//    delete[] cars;
//}
//
//int main() {
//    const char* file = "cars.txt";
//
//    Car c1 = { Brand::Mercedes, "Ivan Ivanov", 120.5, {}, 0 };
//    addFine(c1, 50.0);
//    addFine(c1, 100.0);
//
//    Car c2 = { Brand::Hundai, "Elon Musk", 150.0, {}, 0 };
//    addFine(c2, 20.0);
//
//    Car c3 = { Brand::Honda, "Petar Petrov", 90.2, {}, 0 };
//    addFine(c3, 300.0);
//
//    std::ofstream out(file, std::ios::binary);
//    writeCarToFile(out, c1);
//    writeCarToFile(out, c2);
//    writeCarToFile(out, c3);
//    out.close();
//
//    std::cout << "--- Data before sorting ---" << std::endl;
//    printCar(c1);
//    printCar(c2);
//    printCar(c3);
//
//    sortCarsInFile(file);
//
//    std::cout << "\n--- Data after sorting in file (by speed) ---" << std::endl;
//    std::ifstream in(file, std::ios::binary);
//    Car temp;
//    while (in.read((char*)&temp, sizeof(Car))) {
//        printCar(temp);
//    }
//    in.close();
//
//    return 0;
//}

//7 
/*9MI0800999,Ivan,Ivanov,software_engineering,3,4
0MI0800134,Georgi,Georgiev,computer_science,2,1
3MI0600956,Alexa,Dimitrova,informatics,1,3*/

//namespace constants {
//	const unsigned NAME_LEN = 20;
//	const unsigned SURNAME_LEN = 30;
//	const unsigned FN_LEN = 11;
//	const unsigned MAX_STUDENTS = 1000;
//	const unsigned BUFFER_SIZE = 256;
//}
//
//enum Major {
//	computer_science,
//	software_engineering,
//	informatics,
//	information_systems,
//	unknown
//};
//
//const char* getMajorName(Major m) {
//	switch (m) {
//	case Major::computer_science: return "computer_science";
//	case Major::software_engineering: return "software_engineering";
//	case Major::informatics: return "informatics";
//	case Major::information_systems: return "information_systems";
//	default: return "Unknown";
//	}
//}
//
//Major stringToMajor(const char* str) {
//	if (strcmp(str, "computer_science") == 0) return computer_science;
//	if (strcmp(str, "software_engineering") == 0) return software_engineering;
//	if (strcmp(str, "informatics") == 0) return informatics;
//	if (strcmp(str, "information_systems") == 0) return information_systems;
//	return unknown;
//}
//
//struct Student {
//	char fn[constants::FN_LEN];
//	char name[constants::NAME_LEN];
//	char surname[constants::SURNAME_LEN];
//	Major major;
//	unsigned year;
//	unsigned group;
//};
//
//int compareFN(const char* a, const char* b) {
//	for (int i = 0; i < constants::FN_LEN; i++) {
//		if (a[i] != b[i]) return a[i] - b[i];
//		if (a[i] == '\0') break;
//	}
//	return 0;
//}
//
//size_t loadFromFile(const char* filename, Student* students) {
//	std::ifstream file(filename);
//	if (!file.is_open()) return 0;
//
//	size_t count = 0;
//	char majorStr[30];
//	char tempBuffer[100];
//
//	while (count < constants::MAX_STUDENTS) {
//		if (!file.getline(students[count].fn, constants::FN_LEN, ',')) break;
//
//		file.getline(students[count].name, constants::NAME_LEN, ',');
//		file.getline(students[count].surname, constants::SURNAME_LEN, ',');
//
//		file.getline(majorStr, 30, ',');
//		students[count].major = stringToMajor(majorStr);
//
//		file.getline(tempBuffer, 100, ',');
//		students[count].year = (unsigned)atoi(tempBuffer);
//
//		file.getline(tempBuffer, 100, '\n');
//		students[count].group = (unsigned)atoi(tempBuffer);
//
//		count++;
//	}
//
//	file.close();
//	return count;
//}
//
//void saveToFile(const char* filename, Student* students, size_t count) {
//	std::ofstream file(filename, std::ios::out | std::ios::trunc);
//	if (!file.is_open()) return;
//
//	for (size_t i = 0; i < count; i++) {
//		file << students[i].fn << ","
//			<< students[i].name << ","
//			<< students[i].surname << ","
//			<< getMajorName(students[i].major) << ","
//			<< students[i].year << ","
//			<< students[i].group << "\n";
//	}
//	file.close();
//}
//
//void printByYear(const Student* students, size_t count, unsigned targetYear) {
//	for (size_t i = 0; i < count; ++i) {
//		if (students[i].year == targetYear) {
//			std::cout << students[i].name << " " << students[i].surname << " (FN: " << students[i].fn << ")\n";
//		}
//	}
//}
//
//void changeGroup(Student* students, size_t count, const char* fn, unsigned newGroup) {
//	for (size_t i = 0; i < count; ++i) {
//		if (compareFN(students[i].fn, fn)) {
//			students[i].group = newGroup;
//			return;
//		}
//	}
//}
//
//void removeStudent(Student* students, size_t& count, const char* targetFn) {
//	for (size_t i = 0; i < count; i++) {
//		if (compareFN(students[i].fn, targetFn) == 0) {
//			for (size_t j = i; j < count - 1; j++) {
//				students[j] = students[j + 1];
//			}
//			count--;
//			return;
//		}
//	}
//}
//
//void sortStudentsByFN(Student* students, int count) {
//	for (int i = 0; i < count - 1; i++) {
//		for (int j = 0; j < count - i - 1; j++) {
//			if (compareFN(students[j].fn, students[j + 1].fn) > 0) {
//				Student temp = students[j];
//				students[j] = students[j + 1];
//				students[j + 1] = temp;
//			}
//		}
//	}
//}
//
//int main() {
//	Student students[constants::MAX_STUDENTS];
//	size_t count = loadFromFile("students_data.cvs", students);
//
//	if (count == 0) {
//		std::cout << "File not found or empty!\n";
//		return -1;
//	}
//
//	int choice;
//	do {
//		std::cout << "\n1. Filter by Year\n2. Change Group\n3. Remove Student\n4. Sort by FN\n5. Save and Exit\nChoice: ";
//		std::cin >> choice;
//
//		if (choice == 1) {
//			unsigned y; 
//			std::cout << "Year: "; std::cin >> y;
//			printByYear(students, count, y);
//		}
//		else if (choice == 2) {
//			char fn[constants::FN_LEN];
//			unsigned g;
//			std::cout << "FN: "; std::cin >> fn;
//			std::cout << "New Group: "; std::cin >> g;
//			changeGroup(students, count, fn, g);
//		}
//		else if (choice == 3) {
//			char inputFn[constants::FN_LEN];
//			std::cout << "FN to remove: ";
//			std::cin >> inputFn;
//			removeStudent(students, count, inputFn);
//		}
//		else if (choice == 4) {
//			sortStudentsByFN(students, count);
//			std::cout << "Sorted.\n";
//		}
//	} while (choice != 5);
//
//	saveToFile("students_data.cvs", students, count);
//	return 0;
//}

//8

void decryptMessage(const char* messageFile, const char* keyFile) {
    std::ifstream kFile(keyFile, std::ios::binary);
    if (!kFile) {
        std::cout << "Can't open key file! :(" << std::endl;
        return;
    }

    int key = 0;
    kFile.read((char*)&key, sizeof(int));
    kFile.close();

    std::ifstream mFile(messageFile, std::ios::binary);
    if (!mFile) {
        std::cout << "Can't open message file! >:(" << std::endl;
        return;
    }

    std::cout << "Decrypted message: ";

    int currentNumber;

    while (mFile.read((char*)&currentNumber, sizeof(int))) {
        int decryptedNumber = currentNumber + key;
        std::cout << decryptedNumber << " ";
    }

    std::cout << std::endl;
    mFile.close();
}

int main() {

    decryptMessage("secret.bin", "key.bin");
    return 0;

}