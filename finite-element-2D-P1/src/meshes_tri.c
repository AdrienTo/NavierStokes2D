#include "meshes_tri.h"
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <cassert>
#include <suitesparse/umfpack.h>

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
    
    return fabs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
}
R2 * Tri::operator[](int nbVert) const
{
    return vertices[nbVert];
}
int Tri::Nb()
{
    return NbTri;
}

vector<R2> loadNodes(char* file)  // Generate Nodes from text file
{
    ifstream meshfile;
    meshfile.open(file);
    R2 point = R2(NAN,NAN);
    if(meshfile.is_open()){
    // First line parser
	    int nbVertice, nbElem, nbBound;
	    meshfile >> nbVertice >> nbElem >> nbBound;

	    vector<R2> arrayNodes(nbVertice,point);
	    double xValue = -1., yValue = -1.;
	    int boundary;
    // Reading points in the file
	    for(int i = 0; i<nbVertice;i++)
	    {
		    meshfile >> xValue>>yValue>> boundary;  // Read the coordinates from the file
		    point.setX(xValue);
		    point.setY(yValue);
            if(boundary!=0)
            {
                point.setBoundary(0, boundary);
            }
		    arrayNodes[i] =  point;
	    }
    // Skipping the triangles declaration

        char*  buffer = new char[256];
        meshfile.getline(buffer, 256);
        for(int i=0; i<nbElem; i++)    
        {
            meshfile.getline(buffer, 256);  // Skipping one line, assuming its length is lower than 256
        }
    // Reading the boundaries in the file   
        int triangle1=-1, triangle2=-1;
	    for(int i = 0; i<nbBound;i++)
	    {
		    meshfile >> triangle1 >> triangle2 >> boundary;  // Read the coordinates from the file
            if(arrayNodes[triangle1-1].getBoundary(0)!=boundary && arrayNodes[triangle1-1].getBoundary(1) != boundary)
            {
                assert(arrayNodes[triangle1-1].getBoundary(0) != -1 );
                assert(arrayNodes[triangle1-1].getBoundary(1) == -1 );
                arrayNodes[triangle1-1].setBoundary(1,boundary);
            }
            if(arrayNodes[triangle2-1].getBoundary(0)!=boundary && arrayNodes[triangle2-1].getBoundary(1) != boundary)
            {
                assert(arrayNodes[triangle2-1].getBoundary(0) != -1 );
                assert(arrayNodes[triangle2-1].getBoundary(1) == -1 );
                arrayNodes[triangle2-1].setBoundary(1,boundary);
            }
	    }

        meshfile.close();
	    return arrayNodes;
    }
    else
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier: "+( (string) file) );
    }
}



void loadTri(char* file,vector<R2> & arrayNodes, vector<Tri> &arrayTri,vector<vector<Tri*> > & triInNodes)
{
    ifstream meshfile;
    meshfile.open(file);
    if(!meshfile.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier: "+( (string) file) );
    }
    int nbVertice, nbTri, nbLine, boundary, tri1, tri2, tri3;
    // First line parser
    meshfile >> nbVertice >> nbTri >> nbLine;

    Tri initTri =  Tri();
    arrayTri.resize(nbTri,initTri);
    // Skipping the vertice declaration

    char*  buffer = new char[256];
    meshfile.getline(buffer, 256);
    for(int i=0; i<nbVertice; i++)    
    {
        meshfile.getline(buffer, 256);  // Skipping one line, assuming its length is lower than 256
    }
    triInNodes.resize(nbVertice);

    // Reading the vertices, linking with the triangles
    for(int i =0; i<nbTri; i++)
    {
        meshfile >> tri1 >> tri2 >> tri3 >> boundary;
        // Constructing the triangle
        arrayTri[i].set(0,arrayNodes[tri1-1]);
        arrayTri[i].set(1,arrayNodes[tri2-1]);
        arrayTri[i].set(2,arrayNodes[tri3-1]);

        // Constructing the array of triangle containing p1 and p2
        triInNodes[tri1 - 1].push_back(&arrayTri[i]);
        triInNodes[tri2 - 1].push_back(&arrayTri[i]);
        triInNodes[tri3 - 1].push_back(&arrayTri[i]);

    }
    triInNodes.resize(nbVertice);
    meshfile.close();
    return;
}

Mesh_2D::Mesh_2D(char* filename)
{
    Nodes = loadNodes( filename);
    loadTri(filename, Nodes,Triangles,TriangleContainingNodes);
    
}

void Mesh_2D::make_Stiffness_Matrix()
{
    row_ptr.resize(0);
    col_ind.resize(0);
    value.resize(0);
    // Temporary vectors to store one row, in order to store the 
    vector<double> value_temp(Nodes.size(),NAN);                        // The values are initialized at NAN and become real if the value of the matrix is not zero
    vector<int> col_ind_temp;
    


    int nbNodesInTriangles = Tri::nbNodes, indiceOfMatrix=0;
    double valueLinearForm=NAN;
    R2 * stockNodes;
    row_ptr.push_back(indiceOfMatrix);
    // Go through all the nodes
    for(vector<vector<Tri*> >::iterator itNodes = TriangleContainingNodes.begin() ; itNodes < TriangleContainingNodes.end(); ++itNodes)
    {

        // Go through all vertices that contains the node 
        for(vector<Tri*>::iterator itTri = (*itNodes).begin(); itTri < (*itNodes).end(); ++itTri)
        {
            // Go through all the nodes of the vertice and store the scalar product
            for (int i=0; i<nbNodesInTriangles ; i++)
            {   
                stockNodes = (*itTri)->get(i);                                                                    // Temporary node that is a neighbour of the node (or the node itself) in the vertice (*itSeg)
                valueLinearForm = bilinearForm(&Nodes[itNodes-TriangleContainingNodes.begin()],stockNodes,**itTri);
                if(isnan(value_temp[stockNodes-&(Nodes[0])]) && fabs(valueLinearForm)>0.000000001 )               // The matrix does not store the zero-values
                {
                    col_ind_temp.push_back( ((int) (stockNodes-&(Nodes[0])) ) );                                  // The NAN check permits to add the column number only once                         
                    value_temp[stockNodes-&(Nodes[0])] = 0;        

                }
                if(fabs(valueLinearForm)>0.000000001)
                {
                    value_temp[stockNodes-&(Nodes[0])]+= bilinearForm(&Nodes[itNodes-TriangleContainingNodes.begin()],stockNodes,**itTri);
                }
            }
            
        }

        // Exact penalty method
       
        if(Nodes[itNodes-TriangleContainingNodes.begin()].isBoundary())
        {
            value_temp[itNodes-TriangleContainingNodes.begin()]=penalty_coeff;
        }

        // Copying the temporary values to the  real vectors

        for(vector<int>::iterator itIndexNode = col_ind_temp.begin(); itIndexNode < col_ind_temp.end(); ++itIndexNode)
        {
            indiceOfMatrix++;  
            value.push_back(value_temp[*itIndexNode]);
            value_temp[*itIndexNode] =  NAN;            // Setting back the values to NAN
        }
    
        // Reset the temporary values
        col_ind.insert(col_ind.end(),col_ind_temp.begin(),col_ind_temp.end());
        col_ind_temp.resize(0);
        row_ptr.push_back(indiceOfMatrix);

    }
    assert(col_ind.size() ==  value.size());
/*    cout << "Col_ind: " <<col_ind.size() <<endl;
    for(int i = 0; i< col_ind.size(); i++)
    {
        cout << col_ind[i] << " ";
    }
    cout << endl << endl;
    cout << "Value: " << value.size() << endl;
    for(int i = 0; i< value.size(); i++)
    {
        cout << value[i] << " ";
    }
    cout << endl << endl;
        cout << "Row_ptr: "<<  row_ptr.size() << endl;
    for(int i = 0; i< row_ptr.size(); i++)
    {
        cout << row_ptr[i] << " ";
    }
    cout << endl << endl; */
    
}

void Mesh_2D::get_Stiffness_Matrix(vector<double> & value_get,vector<int> & col_ind_get,vector<int> & row_ptr_get)
{
    value_get = value;
    col_ind_get = col_ind;
    row_ptr_get = row_ptr;
}

void Mesh_2D::make_Constant_Vector()
{
    constVect.resize(0);
    constVect.resize(Nodes.size(),0.);
     // Go through all the nodes
    for(vector<vector<Tri*> >::iterator itNodes = TriangleContainingNodes.begin() ; itNodes < TriangleContainingNodes.end(); ++itNodes)
    {
        assert(constVect[itNodes-TriangleContainingNodes.begin()] == 0.);
        if(!Nodes[itNodes-TriangleContainingNodes.begin()].isBoundary())
        {
        // Go through all vertices that contains the node 
            for(vector<Tri*>::iterator itTri = (*itNodes).begin(); itTri < (*itNodes).end(); ++itTri)
            {
                constVect[itNodes-TriangleContainingNodes.begin()] += linearForm(&Nodes[itNodes-TriangleContainingNodes.begin()], **itTri); 
            }
        }
        else
        {
            // Exact penalty method
            constVect[itNodes-TriangleContainingNodes.begin()]  = limitCondition(&Nodes[itNodes-TriangleContainingNodes.begin()])*penalty_coeff;
        }
    }
         
}

void Mesh_2D::get_Constant_Vector(vector<double> & constVect_get)
{
    constVect_get = constVect;
}
double Orthogonal_Mesh_2D::bilinearForm(R2 * originPoint, R2 *  otherPoint, Tri triangle)
{
    if(originPoint == otherPoint)
    {
        return fabs(triangle.area());
    }
    else
    {
        return 0.;
    }
}
double Orthogonal_Mesh_2D::limitCondition(R2* point)
{
    return 0;
}          
double Orthogonal_Mesh_2D::linearForm(R2 * originPoint,  Tri triangle)
{
        return 0.;
}
double P1_Lapl_Mesh_2D::bilinearForm(R2 * originPoint, R2 *  otherPoint, Tri triangle)
{
        double area = triangle.area();
        double scalar = 0;
        R2 * P1 = triangle.get(0), * P2 = triangle.get(1), * P3 = triangle.get(2);
        int indiceOriginPoint = -(originPoint != P1) + (originPoint == P2)*2 + (originPoint == P3)*3;                    // Get the index of the points in the triangle and set the value to -1 if not in the triangle
        int indiceOtherPoint = -(otherPoint != P1) + (otherPoint == P2)*2 + (otherPoint == P3)*3;   // Same as above, for the other point
        assert(indiceOriginPoint <=2 && indiceOriginPoint >=0 );
        assert(indiceOtherPoint <=2 && indiceOtherPoint >=0 );
        if(originPoint == otherPoint)
        {
            scalar = ( pow(distR2(*triangle.get( ( indiceOriginPoint+1)%3 ), *triangle.get( ( indiceOriginPoint+2)%3 ) ),2) )/(4*area*area);   //
        }
        else  
        {
            scalar =distR2(*triangle.get( ( indiceOriginPoint+1)%3 ), *triangle.get( ( indiceOriginPoint+2)%3 ) )*distR2(*triangle.get( ( indiceOtherPoint+1)%3 ), *triangle.get( ( indiceOtherPoint+2)%3 ) )/(4*area*area);
        }
        
        return  scalar*area;
}
double P1_Lapl_Mesh_2D::linearForm(R2 * originPoint, Tri triangle)
{
        double area = triangle.area();
        double scalar = 1./3.;
        return  scalar*area;
}
double P1_Lapl_Mesh_2D::limitCondition(R2* point)
{
    return 5;
}     

void Mesh_2D::solveSystem()
{
    
    int sizeMatrix = Nodes.size();
    int numberNonZero = value.size();
    assert(numberNonZero == col_ind.size());
    if(sizeMatrix == 0)
    {
        throw std::runtime_error("Erreur: tentative de résolution du problème sans avoir chargé de maillage (nbNoeuds = 0).");
    }

    // Getting the CRS Matrix

    if(value.size() == 0 || col_ind.size() == 0 || row_ptr.size() == 0)
    {
        throw std::runtime_error("Erreur: tentative de résolution du problème sans avoir calculé la matrice de rigidité (matrice de rigidité de taille nulle).");
    }


    double * valArray = &value[0];
    int * colArray = &col_ind[0], * rowArray = &row_ptr[0];

    // Getting the constant values of the system

    if(constVect.size() == 0)
    {
        throw std::runtime_error("Erreur: tentative de résolution du problème sans avoir calculé la partie constante du système (vecteur constant de taille nulle).");
    }


    
    double * constArray =  &constVect[0];

    // Array that store the result

    double result[sizeMatrix];

    double *null = ( double * ) NULL;
    void *Numeric;
    int status;
    void *Symbolic;
    for(int i=0; i< numberNonZero; i++)
    {
        cout << valArray[i] << " ";
    }
    cout << endl << endl;
    for(int i=0; i< numberNonZero; i++)
    {
        cout << colArray[i]<< " ";
    }
    cout << endl<< endl << numberNonZero << endl;

    //
    //  Carry out the symbolic factorization.
    //
      status = umfpack_di_symbolic ( sizeMatrix, sizeMatrix, rowArray, colArray, valArray, &Symbolic, null, null );
    //
    //  Use the symbolic factorization to carry out the numeric factorization.
    //
      status = umfpack_di_numeric (rowArray, colArray,valArray, Symbolic, &Numeric, null, null );
    //
    //  Free the memory associated with the symbolic factorization.
    //
      umfpack_di_free_symbolic ( &Symbolic );
    //
    //  Solve the linear system.
    //
      status = umfpack_di_solve ( UMFPACK_A, rowArray, colArray, valArray, result, constArray, Numeric, null, null );
    //
    //  Free the memory associated with the numeric factorization.
    //
      umfpack_di_free_numeric ( &Numeric );
    cout<<endl;
    for(int i=0; i<sizeMatrix; i++)
    {
        cout << Nodes[i].getX() << " "  << Nodes[i].getY() <<" "<< result[i]<< " "<< constArray[i] <<endl;
    }
}

void exportGnuPlot(vector<Tri> inputTri, string file){
    ofstream plotfile;
    plotfile.open(file.c_str());
    if(!plotfile.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier: "+file);
    }
    plotfile << "# Syntax for gnuplot: 'plot "+file +" using 1:2:($3-$1):($4-$2) with vectors nohead'" <<endl;
    plotfile << "# The grid is a list of segment between the points (X0,Y0) and (X1,Y1)" <<endl;   
    plotfile << "# X0 Y0 X1 Y1" <<endl;
    for(vector<Tri>::iterator it = inputTri.begin(); it != inputTri.end(); ++it)
    {
        plotfile<< it->get(0)->getX() << " " << it->get(0)->getY() << " ";
        plotfile<< it->get(1)->getX() << " " << it->get(1)->getY() <<endl;
        plotfile<< it->get(1)->getX() << " " << it->get(1)->getY() << " ";
        plotfile<< it->get(2)->getX() << " " << it->get(2)->getY() <<endl;
        plotfile<< it->get(2)->getX() << " " << it->get(2)->getY() << " ";
        plotfile<< it->get(0)->getX() << " " << it->get(0)->getY() <<endl;
    }
    plotfile.close();
    
}
     
