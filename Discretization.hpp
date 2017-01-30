#include "Mesh1D.hpp"

typedef double (*FunctionPointer)(double);

double KroneckerDelta(int i, int j);
matrix DiscretizationOperator1D(Mesh1D m, int type);
matrix DiscretizationFunction1D(Mesh1D m, FunctionPointer funcptr);
