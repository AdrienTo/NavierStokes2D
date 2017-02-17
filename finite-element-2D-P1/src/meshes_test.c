#include "meshes_tri.h"
#include "double_dim.h"
#include <cassert>
#include <vector>


void test_Triangle()
{
    assert(Tri::Nb() == 0);
    Tri T1 = Tri();
    assert(Tri::Nb() == 1);
    R2 P1 = R2(0.3,1.3);
    R2 P2 = R2(0,1.);
    R2 P3 = R2(2.,1.);
    Tri T2 = Tri(P1,P2,P3);
    assert(Tri::Nb() == 2);
    Tri T3 = Tri(T2);
    assert(Tri::Nb() == 3);
    T1 = T2;
    Tri * T4 = new Tri();
    assert(Tri::Nb() == 4);
    delete T4;
    assert(Tri::Nb() == 3);

    R2 P4 = R2(0.,0.), P5 = R2(1.,0.), P6 = R2(0.,1.);
    R2 P7 = R2(0.,0.), P8 = R2(4*sqrt(3.)/2.,0.), P9 = R2(0.,2.);
    Tri T5 = Tri(P4,P5,P6), T6 = Tri(P5,P6,P4), T7 = Tri(P5,P4,P6);
    Tri T8 = Tri(P7,P8,P9);
    assert(fabs(T5.area()-1./2.)<0.00000001);
    assert(fabs(T5.area()-T6.area())<0.00000001);
    assert(fabs(T5.area()-T7.area())<0.00000001);

    assert(fabs(T8.area()-16.*sqrt(3.)/8.)<0.000000001);

    assert(T1[0]->getX() == 0.3 && T1[1]->getY() ==1. && T1[2]->getX() == 2. );
    assert(T2[0]->getX() == 0.3 && T2[1]->getY() ==1. && T2[2]->getX() == 2. );
    assert(T3[0]->getY() == 1.3 && T3[1]->getX() ==0. && T3[2]->getY() == 1. );
    assert((T3.get(0))->getY() == 1.3 && (T3.get(1))->getX() ==0. && (T3.get(2))->getY() == 1. );
    cout << "Affichage du triangle P1(0.3,1.3) P2(0.,1.) P3(2.,1.)" <<endl;
    T1.show();

    cout << "Affichage  du triangle P1(0.3,1.3) P2(5.,6.) P3(2.,1.)" << T2 <<endl;
}


void test_loadNodes()
{
    try{
        loadNodes("test_mes.msh");   
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Impossible d'ouvrir le fichier: test_mes.msh") ==0);
    }
    vector<R2> arrayNodes = loadNodes("test_mesh.msh");
    int sizeA = arrayNodes.size();
    assert(sizeA ==  9);
    
    assert(arrayNodes[0].isBoundary());
    assert(fabs(arrayNodes[0].getX() )<0.0000000001 );
    assert(fabs(arrayNodes[0].getY() )<0.0000000001 );
    assert(arrayNodes[0].getBoundary(0)==4 );
    assert(arrayNodes[0].getBoundary(1)==1 );

    assert(arrayNodes[1].getBoundary(0)==1 );
    assert(arrayNodes[1].getBoundary(1)<0);
    assert(fabs(arrayNodes[1].getX() - 0.5 )<0.0000000001 );
    assert(fabs(arrayNodes[1].getY() )<0.0000000000000001 );
    assert(arrayNodes[1].getBoundary(1)<0.);
    assert(arrayNodes[1].isBoundary());
    
    assert(fabs(arrayNodes[2].getX() - 1 )<0.0000000001);
    assert(fabs(arrayNodes[2].getY()  )<0.0000000001);
    assert(arrayNodes[2].getBoundary(0)==2);
    assert(arrayNodes[2].getBoundary(1)==1);
    assert(arrayNodes[2].isBoundary());

    assert(fabs(arrayNodes[3].getX() )<0.0000000001);
    assert(fabs(arrayNodes[3].getY() - 0.5 )<0.0000000001);
    assert(arrayNodes[3].isBoundary());
    assert(arrayNodes[3].getBoundary(0)==4);
    assert(arrayNodes[3].getBoundary(1)<0);

    assert(fabs(arrayNodes[4].getX() - 0.5 )<0.0000000001);
    assert(fabs(arrayNodes[4].getY() - 0.5 )<0.0000000001);
    assert(arrayNodes[4].getBoundary(1)<0);
    assert(arrayNodes[4].getBoundary(0)<0);  
    assert(!arrayNodes[4].isBoundary());  

    assert(fabs(arrayNodes[8].getX() - 1. )<0.0000000001);
    assert(fabs(arrayNodes[8].getY() - 1. )<0.0000000001);
    assert(arrayNodes[8].getBoundary(0) == 3); 
    assert(arrayNodes[8].getBoundary(1) == 2); 
    for(int i=0;i < sizeA-1; i++)
    {
            assert(fabs(arrayNodes[i].getX() - (i%3)*0.5 )<0.0000000001);
            assert(fabs(arrayNodes[i].getY() - (i/3)*0.5 )<0.0000000001);
    }
    assert(fabs(arrayNodes[sizeA-1].getX() - 1)<0.0000000001);
    assert(fabs(arrayNodes[sizeA-1].getY() - 1 )<0.0000000001);
    return;
}
void test_loadTri()
{
    vector<R2> arrayNodes = loadNodes("test_mesh.msh");
    vector<Tri> arrayTri;
    vector<vector<Tri*> >  triContainingNodes;
    try{
        loadTri("test_mes.msh",arrayNodes,arrayTri,triContainingNodes);   
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Impossible d'ouvrir le fichier: test_mes.msh") ==0);
    }

    loadTri("test_mesh.msh",arrayNodes,arrayTri,triContainingNodes);
    int triSize = arrayTri.size(), nodeSize = arrayNodes.size(), stockSize=8 ;
    assert(arrayTri.size() == stockSize);

    int firstArray[8]={1,1,2,2,4,4,5,5}, secondArray[8]={2,5,3,6,5,8,6,9}, thirdArray[8]={5,4,6,5,8,7,9,8}; // Created by hand, reading test_mesh.msh
    for(int i = 0; i<stockSize;i++){
//       cout << i << " " << (arrayTri[i].get(1)-&arrayNodes[0]+1) <<" " << firstArray[i] <<endl;
        assert( (arrayTri[i].get(0)-&arrayNodes[0]+1) == firstArray[i]);
        assert( (arrayTri[i].get(1)-&arrayNodes[0]+1) == secondArray[i]);
        assert( (arrayTri[i].get(2)-&arrayNodes[0]+1) == thirdArray[i]);
    }
    for (int i = 0; i<nodeSize; i++)
    {
        stockSize = (triContainingNodes[i]).size();
        for(int j=0; j<stockSize; j++)
        {
            assert( (  (*((triContainingNodes[i])[j])).get(0) ==   &(arrayNodes[i])  ) || (  (*((triContainingNodes[i])[j])).get(1) ==   &(arrayNodes[i]) ) || (  (*((triContainingNodes[i])[j])).get(2) ==   &(arrayNodes[i])  ) );
        }
    }
    return;
}
void test_Orthogonal_Mesh_2D()
{
    Orthogonal_Mesh_2D lineMesh("test_mesh.msh");
    lineMesh.make_Stiffness_Matrix();
    vector<double> value;
    vector<int> col_ind, row_ptr;
    lineMesh.get_Stiffness_Matrix(value,col_ind,row_ptr);
    assert(col_ind.size() ==  value.size());
    assert(col_ind.size() ==  9);
    assert(row_ptr.size() == 10);
    int Rsize = col_ind.size();
    assert(fabs(value[0]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[1]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[2]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[3]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[4]-0.750)<0.0000000000001);
    assert(fabs(value[5]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[6]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[7]-Mesh_2D::penalty_coeff)<0.0000000000001);
    assert(fabs(value[8]-Mesh_2D::penalty_coeff)<0.0000000000001);

    for(int i = 0; i<Rsize; i++)
    {
        assert(col_ind[i]== i);
        assert(row_ptr[i] == i);
    }
}

void test_P1_Lapl_Mesh_2D()
{
    P1_Lapl_Mesh_2D lineMesh("test_mesh.msh");
    try{
        lineMesh.solveSystem();
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Erreur: tentative de résolution du problème sans avoir calculé la matrice de rigidité (matrice de rigidité de taille nulle).") ==0);
    }


    lineMesh.make_Stiffness_Matrix();
    vector<double> value,constant_vector;
    vector<int> col_ind, row_ptr;
    
    lineMesh.get_Stiffness_Matrix(value,col_ind,row_ptr);
    assert(col_ind.size() ==  value.size());
    assert(col_ind.size() == 33);
    assert(row_ptr.size() == 10);
    int Rsize = col_ind.size();

    int sum_neighbour[10] ={0,3,7,10,14,19,23,26,30,33};
    for(int i=0;i<10;i++)
    {
        assert(row_ptr[i] == sum_neighbour[i]);
    }



    assert(col_ind[0] == 0);    
    assert(col_ind[1] == 1);    
    assert(col_ind[2] == 3);     
    assert(col_ind[3] == 0);
    assert(col_ind[4] == 1);
    assert(col_ind[5] == 2);
    assert(col_ind[6] == 4);

    assert(col_ind[7] == 1);
    assert(col_ind[10] == 0);
    assert(col_ind[14] == 1);
    assert(col_ind[19] == 2);
    assert(col_ind[23] == 3);
    assert(col_ind[26] == 4);
    assert(col_ind[30] == 5);
    assert(col_ind[31] == 7);
    assert(col_ind[32] == 8);
    
    int j=0;
    for(int i = 0; i<33; i++)
    {   
        if(row_ptr[j] == i)
        {
            j++;     
        }
        if(j-1 == col_ind[i])
        {
            if(j-1 !=4)
            {
                assert( fabs(value[i]-P1_Lapl_Mesh_2D::penalty_coeff)<0.000000000001);
            }
            if(j-1==4)
            {
                assert( fabs(value[i]-4.)<0.000000000001);  
            }

        }
        else
        {
            assert( (fabs(value[i]-1./2.)<0.000000000001) ||(fabs(value[i]+1./2.)<0.000000000001) || (fabs(value[i]+1.)<0.000000000001) || (fabs(value[i]-1.)<0.000000000001));  
        }
    }
    try{
        lineMesh.solveSystem();
    }
    catch(std::exception &exce){
        assert(((string) exce.what()).compare("Erreur: tentative de résolution du problème sans avoir calculé la partie constante du système (vecteur constant de taille nulle).") ==0);
    }
    lineMesh.make_Constant_Vector();
    lineMesh.get_Constant_Vector(constant_vector);

    lineMesh.solveSystem();
}
void gnuPlot()
{
    vector<vector<Tri*> >  triContainingNodes;
    vector<R2> arrayNodes = loadNodes("test_mesh.msh");
    vector<Tri> arrayTri;
    loadTri("test_mesh.msh",arrayNodes,arrayTri,triContainingNodes);
    exportGnuPlot(arrayTri);
}

int main()
{
   cout << "Test classe triangle" << endl;
   test_Triangle();
   cout << "Test reading mesh" << endl;
   test_loadNodes();
   cout << "Test Triangle construction" << endl;
   test_loadTri();
   cout << "Test Orthogonal rigidity matrix construction" <<endl;
   test_Orthogonal_Mesh_2D();
   cout << "Test P1 rigidity matrix construction" << endl;
   test_P1_Lapl_Mesh_2D();
   cout << "Test well performed" <<endl;
   gnuPlot();
}

