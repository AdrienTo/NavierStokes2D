#include <cmath>
#include <map>
#include "matrix.hpp"
#include "Discretization.hpp"


double KroneckerDelta(int i, int j) {
	if (i == j) {
		return 1.0;
	} else {
		return 0.0;
	}
}


matrix DiscretizationOperator1D(Mesh1D m, int type) {

	// : lecture note P. 80

	int nv = m.getNumVertex();
	int ne = m.getNumEdge();
	matrix mat(nv, nv);

	double* tx;
	tx = new double[nv * nv];
	for (int i = 0; i < nv * nv; i++) {
		tx[i] = 0.0; // initialisation
	}

	if (type == 1) {

		// __gugv__

		for (int i = 0; i < ne; i++) {
			std::pair<int, int> vip = m.getVertexIndexPair(i);
			int vi1 = vip.first;
			int vi2 = vip.second; // |vi1 - vi2| = 1 in 1D
			int vi[2] = {vi1, vi2};
			double h = m.getEdgeLength(i);
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					tx[vi[j] * nv + vi[k]] += std::pow(-1.0, 1.0 + KroneckerDelta(j, k)) / h;
				}
			}
		}

	} else if (type == 2) {

		// __guv__

		// no need to implement for this problem

	} else if (type == 3) {

		// __uv__
		
		for (int i = 0; i < ne; i++) {
			std::pair<int, int> vip = m.getVertexIndexPair(i);
			int vi1 = vip.first;
			int vi2 = vip.second; // |vi1 - vi2| = 1 in 1D
			int vi[2] = {vi1, vi2};
			double h = m.getEdgeLength(i);
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					tx[vi[j] * nv + vi[k]] += h * (1.0 + KroneckerDelta(j, k)) / 6.0;
				}
			}
		}

	}

	mat.initialise(tx);
	delete tx;

	return mat;

}


matrix DiscretizationFunction1D(Mesh1D m, FunctionPointer funcptr) {

	int nv = m.getNumVertex();
	int ne = m.getNumEdge();
	matrix mat(nv, 1);

	double* tx;
	tx = new double[nv * 1];

	for (int i = 0; i < nv * 1; i++) {
		tx[i] = (funcptr)(m.getVertexCoordinate(i));
	}

	mat.initialise(tx);
	delete tx;

	return mat;

}