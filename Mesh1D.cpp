#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>

#include "Mesh1D.hpp"

Mesh1D::Mesh1D(int nm) {

	this->nv = nm + 1;
	this->ne = nm;

	double tx;
	for (int i = 0; i < this->nv; i++) {
		tx = (double)i / (double)this->ne;
		vi2vc.insert(std::make_pair(i + 1, tx));
		if (i < this->ne) {
			ei2vip.insert(std::make_pair(i + 1, std::make_pair(i + 1, i + 2)));
		}
		if (i == 0 || i == this->ne) {
			vi2bi.insert(std::make_pair(i + 1, 1));
		} else {
			vi2bi.insert(std::make_pair(i + 1, 0));
		}
	}

	bv = new int[2];
	bv[0] = 1;
	bv[0] = this->nv;

}


Mesh1D::Mesh1D(std::string str) {

	std::ifstream ifs(str);

	int rnv;
	int rne;
	int r1;
	ifs >> rnv >> rne >> r1;
	this->nv = rnv;
	this->ne = rne;

	double rc;
	int rbi;
	for (int i = 0; i < this->nv; i++) {
		ifs >> rc >> rbi;
		vi2vc.insert(std::make_pair(i + 1, rc));
		vi2bi.insert(std::make_pair(i + 1, rbi));
	}

	int rvi1;
	int rvi2;
	int r2;
	for (int i = 0; i < this->ne; i++) {
		ifs >> rvi1 >> rvi2 >> r2;
		ei2vip.insert(std::make_pair(i + 1, std::make_pair(rvi1, rvi2)));
	}

	bv = new int[2];
	int rvbi;
	int r3;
	for (int i = 0; i < 2; i++) {
		ifs >> rvbi >> r3;
		bv[i] = rvbi;
	}

}


Mesh1D::~Mesh1D() {
	delete bv;
}

double Mesh1D::operator[](int i) {
	return this->vi2vc[i];
}

void Mesh1D::writeMeshFile(std::string str) {
	std::cout << "tbd" << std::endl;
}

int Mesh1D::getNumVertex() const {
	return this->nv;
}

int Mesh1D::getNumEdge() const {
	return this->ne;
}

std::pair<int, int> Mesh1D::getVertexIndexPair(int ei) {
	return this->ei2vip[ei];
}

double Mesh1D::getVertexCoordinate(int vi) {
	return this->vi2vc[vi];
}
double Mesh1D::getEdgeLength(int ei) {
	std::pair<int, int> eip = this->getVertexIndexPair(ei);
	double xa = this->getVertexCoordinate(eip.first);
	double xb = this->getVertexCoordinate(eip.second);
	return std::fabs(xa - xb);
}
