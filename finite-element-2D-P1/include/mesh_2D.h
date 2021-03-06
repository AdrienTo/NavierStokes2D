#ifndef MESHES_TRI_H
#define MESHES_TRI_H

#include <iostream>
#include "double_dim.h"
#include <vector>
#include <cmath>
#include "triangle.h"




// Abstract class that represent a mesh storage has a finite element resolution method
// The construction of the Stiffness matrix is done by make_Stiffness_Matrix(), the result is in CRS form
// The method linearForm represents the linear form result, applying the operator to originPoint and otherPoint in the vertice Triangle
// This is an abstact class, it needs to be writter explicitly depending on the problem
    
class Mesh_2D
{
    protected:
        // Mesh-related vectors
        vector<R2> Nodes;
        vector<Tri> Triangles;
        vector<vector<Tri*> > TriangleContainingNodes;   // Given the number of a node, it returns the vector of pointer to triangles that have this node (using the same index as Nodes)
        vector<R2*> Boundaries;                         // Nodes in the boundaries        

        // Stiffness matrix vectors (the matrix is stored in the format Compression Row Storage)
        vector<double> value;
        vector<int> col_ind, row_ptr;

        // Constant vector (b in Ax = b)
        vector<double> constVect;

        // Solution of the problem
        vector<double> Solution;



    public:
        // Penalty coefficient
        static const double penalty_coeff = 10000000000;
       
       // Loading the ".msh" file
        Mesh_2D(char* filename);

        // Defining the Dirichlet problem :
        // integral(Au,v) = integral(f,v) in O
        //  u = g in dO

        virtual double limitCondition(R2* point) = 0;                                       // x |--> g(x), for x in dO 
        virtual double linearForm(R2* originPoint, Tri triangle) = 0;                        // integral(f(x),phi(originPoint,x)) on triangle                  
        virtual double bilinearForm(R2* originPoint, R2*  otherPoint, Tri triangle) = 0;   // integral(A(u,v)(x)) on triangle with u(x) = phi(originPoint,x), v(x) = phi(otherPoint,x)
 
        ////////
        //////// Solving the problem
        ////////

        // Calculating the data for the linear system

        void make_Stiffness_Matrix();
        void get_Stiffness_Matrix(vector<double> & value_get,vector<int> & col_ind_get,vector<int> & row_ptr_get);
        void make_Constant_Vector();
        void get_Constant_Vector(vector<double> & constVect_get);

        // Solving the system

        void solveSystem();      

};



vector<R2> loadNodes(char* file) ;
void loadTri(char* file,vector<R2> & arrayNodes, vector<Tri> &arrayTri,vector<vector<Tri*> > & triInNodes);
void exportGnuPlot(vector<Tri> inputTri, string file = "output.txt" );
#endif
