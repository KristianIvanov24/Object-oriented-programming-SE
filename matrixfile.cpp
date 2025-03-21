#include<iostream>
#include<cstring>
#include<fstream>
#define MAX_SIZE 100
#pragma warning(disable:4996)


using std::cin;
using std::cout;
using std::endl;




class MatrixFile {
	int matrix[MAX_SIZE][MAX_SIZE];
	int row;
	int col;

	void swap(int& a, int& b) {
		int swap = a;
		a = b;
		b = swap;
	}

public:
	
	MatrixFile() {
		row = MAX_SIZE;
		col = MAX_SIZE;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->matrix[i][j] = 0;
			}
		}
	}

	void ReadMatrix(std::ifstream& ifs) {
		ifs >> row >> col;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ifs >> this->matrix[i][j];
			}
		}
	}

	~MatrixFile() {
		std::ofstream ofs("Matrix.txt");

		ofs << row << " " << col << endl;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ofs << matrix[i][j] << " ";
			}
			ofs << endl;
		}
	}
	int getRow() {
		return this->row;
	}
	int getCol() {
		return this->col;
	}

	void printMatrix() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << this->matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	void transpose() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				//cout << i << " " << j << endl;
				swap(this->matrix[i][j], this->matrix[j][i]);
			}
		}
	}
	void multiplyByScalar(int scalar) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->matrix[i][j] *= scalar;
			}
		}
	}
	void change(int i, int j, int number) {
		if (i > row || j > col) {
			return;
		}
		this->matrix[i][j] = number;
	}
	

};

int main() {

	std::ifstream ifs("Matrix.txt");
	MatrixFile matrix;
	matrix.ReadMatrix(ifs);
	matrix.printMatrix();

	matrix.multiplyByScalar(2);

	cout << endl << endl;

	matrix.printMatrix();

	matrix.change(1, 1, 13);
	cout << endl << endl;
	matrix.printMatrix();


	ifs.close();
	
	return 0;
}