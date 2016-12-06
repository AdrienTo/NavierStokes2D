#include <iostream>
#include <fstream>
#include <ostream>
#include "matrix.hpp"

int main(){

	std::cout << "Hello, World!" << std::endl;

	std::cout << "___START___" << std::endl;

	matrix mat1(3, 2);
	double* m1;
	m1 = new double[6];
	for (int i = 0; i < 6; i++) {
		m1[i] = 1.2345 * (double)(i + 1);
	}
	mat1.initialise(m1);
	delete m1;

	matrix mat2(2, 3);
	double* m2;
	m2 = new double[6];
	for (int i = 0; i < 6; i++) {
		m2[i] = 0.54321 * (double)(i + 1);
	}
	mat2.initialise(m2);
	delete m2;

	std::cout << mat1 << std::endl;
	std::cout << mat2 << std::endl;
	std::cout << mat1 + mat2 << std::endl;
	std::cout << 2.0 * mat2 << std::endl;
	std::cout << mat1 * mat2 << std::endl;
	std::cout << mat2 * mat1 << std::endl;
	std::cout << mat1[3] << std::endl;
	std::cout << mat2(1, 1) << std::endl;

	std::cout << "___END___" << std::endl;

	return 0;

}