#ifndef VAR_PROBLEM_H
#define VAR_PROBLEM_H

#include "mesh_2D.h"



class Orthogonal_Mesh_2D: public Mesh_2D                // This class has been created for the purpose of testing
{
    public:
        Orthogonal_Mesh_2D(char* filename): Mesh_2D(filename){};                // Call the Mesh_2D constructor at the initalization
        double limitCondition(R2* point);            
        double linearForm(R2* originPoint, Tri triangle); 
        double bilinearForm(R2* originPoint, R2*  otherPoint, Tri triangle);
};

class P1_Lapl_Mesh_2D: public Mesh_2D
{
    public:
        P1_Lapl_Mesh_2D(char* filename): Mesh_2D(filename){};                // Call the Mesh_2D constructor at the initalization
        double limitCondition(R2* point);            
        double linearForm(R2* originPoint, Tri triangle);
        double bilinearForm(R2 * originPoint, R2 *  otherPoint, Tri triangle);
};

#endif
