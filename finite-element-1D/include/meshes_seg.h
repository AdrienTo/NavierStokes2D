#ifndef MESHES_SEG_H
#define MESHES_SEG_H

#include <iostream>
#include "simple_dim.h"
#include <vector>
#include <cmath>

// Class representing a vertice in dimension 1

class Seg
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

    static const int nbNodes = 2;
    static int Nb();

};

// Abstract class that represent a mesh storage has a finite element resolution method
// The construction of the rigidity matrix is done by make_Rigidity_Matrix(), the result is in CRS form
// The method linearForm represents the linear form result, applying the operator to originPoint and otherPoint in the vertice Segment
// This is an abstact class, it needs to be writter explicitly depending on the problem
    
class Mesh_1D
{
    private:
        // Mesh-related vectors
        vector<R1> Nodes;
        vector<Seg> Segments;
        vector<vector<Seg*> > SegmentContainingNodes;   // Given the number of a node, it returns the vector of pointer to segments that have this node
        
        // Rigidity matrix vectors (the matrix is stored in the format CRS)
        vector<double> value;
        vector<int> col_ind, row_ptr;
    public:
        Mesh_1D(char* filename);
        virtual double linearForm(R1 * originPoint, R1 *  otherPoint, Seg segment) = 0;
        void make_Rigidity_Matrix();
        void get_Rigidity_Matrix(vector<double> & value,vector<int> & col_ind,vector<int> & row_ptr);
};

class Orthogonal_Mesh_1D: public Mesh_1D                // This class has been created for the purpose of testing
{
    public:
        Orthogonal_Mesh_1D(char* filename): Mesh_1D(filename){};                // Call the Mesh_1D constructor at the initalization
        double linearForm(R1 * originPoint, R1 *  otherPoint, Seg segment);
};

class P1_Lapl_Mesh_1D: public Mesh_1D
{
    public:
        P1_Lapl_Mesh_1D(char* filename): Mesh_1D(filename){};                // Call the Mesh_1D constructor at the initalization
        double linearForm(R1 * originPoint, R1 *  otherPoint, Seg segment);
};
ostream& operator<<(ostream& stream,const Seg& Segment);

vector<R1> loadNodes(char* file) ;
void loadSeg(char* file,vector<R1> & arrayNodes, vector<Seg> &arraySeg,vector<vector<Seg*> > & segInNodes);
void exportGnuPlot(vector<Seg> inputSeg, string file = "output.txt" );
#endif
