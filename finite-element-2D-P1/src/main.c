#include <iostream>
#include "var_problem.h"
using namespace std;

int main(int argc, char** argv)
{
    
    P1_Lapl_Mesh_2D lineMesh("mesh.msh");
    lineMesh.make_Stiffness_Matrix();
    lineMesh.make_Constant_Vector();
    lineMesh.solveSystem();
	return 0;
}
