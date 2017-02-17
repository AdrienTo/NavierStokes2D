#include "triangle.h"


///////////////////////////
////  Triangle methods ////
///////////////////////////

int Tri::NbTri = 0;

Tri::Tri(){
    NbTri++;
}
Tri::Tri(R2 &point1, R2 &point2, R2 &point3) // Création à partir de 3 points
{
    NbTri++;
    vertices[0] = &point1;
    vertices[1] = &point2;
    vertices[2] = &point3;
}

Tri::Tri(const Tri& Tcopy)    // Constructeur par copie
{    
    NbTri++;
    vertices[0] = Tcopy[0];
    vertices[1] = Tcopy[1];
    vertices[2] = Tcopy[2];
}

Tri::~Tri()   // Décrémentation de NbTri à la destruction d'un objet
{
    NbTri--;
}

void Tri::operator=(const Tri& Tcopy)
{
    vertices[0] = Tcopy[0];
    vertices[1] = Tcopy[1];
    vertices[2] = Tcopy[2];
}
ostream& operator<<(ostream& stream,const Tri& Triangle)
{
    stream <<"Triangle( " << Triangle.vertices[0] <<", " <<Triangle.vertices[1] << ", " << Triangle.vertices[2]<< " )" <<endl;
    return stream;
}

void Tri::set(int nbVertice, R2 & vertice)
{
    vertices[nbVertice] = &vertice;
}

R2 * Tri::get(int nbVertice) const
{
    return vertices[nbVertice];
}

void Tri::show(){
    cout <<"Triangle(";
    vertices[0]->show();
    vertices[1]->show();
    vertices[2]->show();
    cout<<")"<<endl;

}
void Tri::showRaw(){
    cout <<"Triangle("<<vertices[0]<<", " << vertices[1] << ", " << vertices[2] <<")"<<endl;
}

double Tri::area()
{
    double x1 = vertices[0]->getX(), x2 = vertices[1]->getX(), x3 = vertices[2]->getX();
    double y1 = vertices[0]->getY(), y2 = vertices[1]->getY(), y3 = vertices[2]->getY();
    
    return fabs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2.;
}
R2 * Tri::operator[](int nbVert) const
{
    return vertices[nbVert];
}
int Tri::Nb()
{
    return NbTri;
}

