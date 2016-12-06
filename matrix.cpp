#include <iostream>
#include <fstream>
#include <ostream>

#include "matrix.hpp"

matrix::matrix(int i, int j) {

	// default constructor 

	this->nr = i;
	this->nc = j;
	this->m = new double[this->nr * this->nc];
	this->init = false;

}


matrix::matrix(const matrix& mat) {

	// copy constructor 

	this->nr = mat.getNumRow();
	this->nc = mat.getNumColumn();
	this->m = new double[this->nr * this->nc];
	this->init = true;

	for (int i = 0; i < this->nr; i++) {
		for (int j = 0; j < this->nc; j++) {
			this->m[this->nc * i + j] = mat[this->nc * i + j];
		}
	}

}


matrix::~matrix() {

	// destructor 

	delete this->m;

}


matrix& matrix::operator=(const matrix& mat){

	// assignment operator

	return *this;

}

matrix matrix::operator+(const matrix& mat) {

	matrix rmat(this->nr, this->nc);
	double* tm = new double[this->nr * this->nc];
	for (int i = 0; i < this->nr; i++) {
		for (int j = 0; j < this->nc; j++) {
			tm[this->nc * i + j] = this->m[this->nc * i + j] + mat[this->nc * i + j];
		}
	}
	rmat.initialise(tm);
	delete tm;

	return rmat;

}


matrix matrix::operator*(double x) {

	matrix rmat(this->nr, this->nc);
	double* tm = new double[this->nr * this->nc];
	for (int i = 0; i < this->nr; i++) {
		for (int j = 0; j < this->nc; j++) {
			tm[this->nc * i + j] = this->m[this->nc * i + j] * x;
		}
	}
	rmat.initialise(tm);
	delete tm;
	return rmat;
}


matrix operator*(double x, const matrix& mat) {

	int tnr = mat.getNumRow();
	int tnc = mat.getNumColumn();
	matrix rmat(tnr, tnc);
	double* tm = new double[tnr * tnc];
	for (int i = 0; i < tnr; i++) {
		for (int j = 0; j < tnc; j++) {
			tm[tnc * i + j] = mat[tnc * i + j] * x;
		}
	}
	rmat.initialise(tm);
	delete tm;
	return rmat;

}


matrix matrix::operator*(const matrix& mat) {

	int lnr = this->nr;
	int lnc = this->nc; // lnc == rnr

	int rnr = mat.getNumRow(); // lnc == rnr
	int rnc = mat.getNumColumn();

	int n = lnc; // n == lnc == rnr
	matrix rmat(lnr, rnc);
	double tx = 0.0;

	double* tm = new double[lnr * rnc];
	for (int i = 0; i < lnr; i++) {
		for (int j = 0; j < rnc; j++) {
			tx = 0.0; // initialise
			for (int k = 0; k < n; k++) {
				tx += this->m[lnc * i + k] * mat[rnr * k + j];
			}
			tm[rnc * i + j] = tx;
		}
	}
	rmat.initialise(tm);
	delete tm;

	return rmat;
}


double matrix::operator[](int i) const {
	return m[i];
}


double& matrix::operator[](int i) {
	return m[i];
}


double matrix::operator()(int i, int j) const {
	return m[this->nr * i + j];
}


double& matrix::operator()(int i, int j) {
	return m[this->nr * i + j];
}


std::ostream& operator<<(std::ostream& out, const matrix& mat) {

	int nr = mat.getNumRow();
	int nc = mat.getNumColumn();
	out << "(";
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			out << mat[nc * i + j];
			if (j < nc - 1) {
				out << ", ";
			}
		}
		if (i < nr - 1) {
			out << "; ";
		}
	}
	out << ")";
	return out;

}

void matrix::initialise(double* p) {

	for (int i = 0; i < this->nr; i++) {
		for (int j = 0; j < this->nc; j++) {
			this->m[this->nc * i + j] = p[this->nc * i + j];
		}
	}
	this->init = true;

}


int matrix::getNumRow() const {
	return nr;
}


int matrix::getNumColumn() const {
	return nc;
}

