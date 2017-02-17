#ifndef TRI_H
#define TRI_H

#include <iostream>
#include "double_dim.h"

// Class representing a vertice in dimension 2

class Tri
{
private:
    R2 * vertices[3];
    static int NbTri;
public:
    Tri();
    Tri(R2 & point1, R2 & point2, R2 & point3);
    Tri(const Tri& Tcopy);
    ~Tri();
    R2 * operator[](int nbVert) const;
    void operator=(const Tri& Tcopy);
    friend ostream& operator<<(ostream& stream,const Tri& Triangle);
    void set(int nbVertice,R2 & vertice);
    R2 * get(int nbVertice) const;
    void show();
    void showRaw();
    double area();

    static const int nbNodes = 3;
    static int Nb();

};

ostream& operator<<(ostream& stream,const Tri& Triangle);


#endif
