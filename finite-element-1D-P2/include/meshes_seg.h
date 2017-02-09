#ifndef MESHES_SEG_H
#define MESHES_SEG_H

#include <iostream>
#include "simple_dim.h"
#include <vector>
#include <cmath>

// Class representing a vertice in dimension 1

class Seg // Va être remplacé par un triangle
{
private:
    R1 * vertices[2];
    static int NbSeg;
public:
    Seg();
    Seg(R1 & point1, R1 & point2);
    Seg(const Seg& Tcopy);
    ~Seg();
    R1 * operator[](int nbVert) const;
    void operator=(const Seg& Scopy);
    friend ostream& operator<<(ostream& stream,const Seg& Segment);
    void set(int nbVertice,R1 & vertice);
    R1 * get(int nbVertice) const;
    void show();
    void showRaw();
    bool find(R1);

    static const int nbNodes = 2;
    static int Nb();

};

// Abstract class that represent a mesh storage has a finite element resolution method
// The construction of the Stiffness matrix is done by make_Stiffness_Matrix(), the result is in CRS form
// The method linearForm represents the linear form result, applying the operator to originPoint and otherPoint in the vertice Segment
// This is an abstact class, it needs to be writter explicitly depending on the problem
    
class Mesh_1D
{
    protected:
        // Mesh-related vectors
        vector<R1> Nodes;
        vector<Seg> Segments;
        vector<vector<Seg*> > SegmentContainingNodes;   // Given the number of a node, it returns the vector of pointer to segments that have this node (using the same index as Nodes)
        vector<R1*> Boundaries;                         // Nodes in the boundaries        

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
        Mesh_1D(char* filename);

        // Defining the Dirichlet problem :
        // integral(Au,v) = integral(f,v) in O
        //  u = g in dO

        virtual double limitCondition(R1* point) = 0;                                       // x |--> g(x), for x in dO 
        virtual double linearForm(R1* originPoint, Seg segment) = 0;                        // integral(f(x),phi(originPoint,x)) on segment                   
        virtual double bilinearForm(R1 * originPoint, R1 *  otherPoint, Seg segment) = 0;   // integral(A(u,v)(x)) on segment with u(x) = phi(originPoint,x), v(x) = phi(otherPoint,x)
 
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

class Orthogonal_Mesh_1D: public Mesh_1D                // This class has been created for the purpose of testing
{
    public:
        Orthogonal_Mesh_1D(char* filename): Mesh_1D(filename){};                // Call the Mesh_1D constructor at the initalization
        double limitCondition(R1* point);            
        double linearForm(R1* originPoint, Seg segment); 
        double bilinearForm(R1 * originPoint, R1 *  otherPoint, Seg segment);
};

class P1_Lapl_Mesh_1D: public Mesh_1D
{
    public:
        P1_Lapl_Mesh_1D(char* filename): Mesh_1D(filename){};                // Call the Mesh_1D constructor at the initalization
        double limitCondition(R1* point);            
        double linearForm(R1* originPoint, Seg segment);
        double bilinearForm(R1 * originPoint, R1 *  otherPoint, Seg segment);
};


class P2_Lapl_Mesh_1D: public Mesh_1D
{
    private:
        int originalNbNodes;
        int newNbNodes;
    public:
        P2_Lapl_Mesh_1D(char* filename);                // Call the Mesh_1D constructor at the initalization
        adaptMeshForP2();
        double limitCondition(R1* point);            
        double linearForm(R1* originPoint, Seg segment);
        double bilinearForm(R1 * originPoint, R1 *  otherPoint, Seg segment);
};

ostream& operator<<(ostream& stream,const Seg& Segment);

vector<R1> loadNodes(char* file) ;
void loadSeg(char* file,vector<R1> & arrayNodes, vector<Seg> &arraySeg,vector<vector<Seg*> > & segInNodes);
void exportGnuPlot(vector<Seg> inputSeg, string file = "output.txt" );
#endif
