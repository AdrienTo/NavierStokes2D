#include "double_dim.h"
#include <cassert>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
 
void test_creation_R2()
{
    R2 point1  = R2();
    R2 point2  = R2(3.121,2.93);
    R2 point3  = R2(point2);
    point1.setX(-1.3);
    point1.setY(-51.3);

    assert(point1.getX() == -1.3);
    assert(point2.getY() == 2.93);
    assert(point3.getX() == 3.121);
    assert(point1.getY() == -51.3);
}

void test_show_R2()
{
    R2 point1 = R2(23.121,-10.52);
    cout << "Le vecteur à coordonnées X = 23.121 ,Y = -10.52 va s'afficher:"<<endl;
    point1.show();
}
// Teste l'ajout et la différence entre points

void test_sum_R2()
{
    R2 point1 = R2(11.5,11.5);
    R2 point2 = R2(1.5,1.5);
    R2 point3 = R2(1.,1.5);
    R2 point4 = point3-point2;
    R2 point5 = point3+point1;
    assert((fabs(point4.getX()+0.5)<0.00000001) && (fabs(point4.getY())<0.00000001) );
    assert((fabs(point5.getX()-12.5)<0.00000001) && (fabs(point5.getY()-13.0)<0.00000001) );
}

// Teste la fonction distance entre points

void test_distance_R2()
{
    R2 point1 = R2(11.5,11.5);
    R2 point2 = R2(1.5,1.5);
    R2 point3 = R2(0.,1.5);
    R2 point4 = R2(1.5,0.); 
    
    assert(fabs(distR2(point1,point2)-sqrt(2.)*10.)<0.005);
    assert( distR2(point2,point2) == 0.);
    assert(fabs(distR2(point3,point2)-1.5)<0.005);
    assert(fabs(distR2(point3,point4)-1.5*sqrt(2.))<0.005);
    assert(distR2(point1,point2) == distR2(point2,point1));
}

// Teste la fonction de comparaison entre points

void test_compare_R2()
{
    R2 point1 = R2(11.5,11.5);
    R2 point2 = R2(1.5,1.5);
    R2 point3 = R2(point1);

    assert(compR2(point1,point1));
    assert(compR2(point1,point3));
    assert(!compR2(point1,point2));
    assert(compR2(point3,point1));
}

// Teste la construction de matrice

void test_creation_mat_R2()
{
    matR2 mat1(1.,2.,3.,4.);
    matR2 mat2(5.5,6.6,7.7,8.8);
    matR2 mat3 = matR2(mat1);
    matR2 mat4 = matR2();
    mat4.set(1,1,1.230);
    mat3.set(0,1,10.3);

    assert(mat1.get(0,0) == 1.);
    assert(mat2.get(0,1) == 6.6);
    assert(mat2.get(0,1) != 5.6);
    assert(mat3.get(1,0) == 3.);
    assert(mat2.get(1,1) == 8.8);
    assert(mat3.get(0,1) == 10.3);
    assert(mat4.get(1,1) == 1.230);
}


// Teste les operations sur R2 et les matrices


void test_operation_R2()
{

    R2 point1 = R2(11.5,14.5);
    R2 point2 = point1;
    R2 point3 = R2(1.,1.5);
    R2 point4 = R2(1.5,0.); 
    R2 point5 = point1.orthogonal();
    matR2 mat1(1.,2.,3.,4.);
    matR2 mat2;

    matR2 mat3 = matR2(mat1);
    matR2 mat4 = matR2();
    mat4.set(1,1,1.230);
    mat3.set(0,1,10.3);
    
    cout << "Le point de coordonnées 11.5, 14.5 va etre affiche" << point1 <<endl;
    cout << "La matrice avec les valeurs 1, 2, 3, 4 va etre affichee " << mat1 <<endl;
    
    assert((fabs(point5.getX()+14.5)<0.000000000001) && (fabs(point5.getY()-11.5)<0.000000000001));
    point4 = 1.45*point3;
    assert((point4.getX() == 1.45)  && point4.getY() == 2.175);
    double scalar;
    scalar = (point2,point3);
    assert(scalar == 33.25);
    assert(( point4.getX() == (point4[0]))  && (point4.getY() == point4[1]));
    try{
        point4[2];
    }
    catch(const char* Msg) {
    assert(!strcmp("R2 error: index out of range.",Msg));
    }
    try{
        point4[-1];
    }
    catch(const char* Msg) {
    assert(!strcmp("R2 error: index out of range.",Msg));
    }
    mat2 = mat1;
    assert((mat2.get(0,0) ==1.) && (mat2.get(0,1) == 2. ) && (mat2.get(1,0) == 3.) && (mat2.get(1,1) == 4.)); // Operateur =

    mat3 = mat2*mat1;
    assert((mat3.get(0,0) == 7.) && (mat3.get(0,1)== 10.) && (mat3.get(1,0) == 15.) && (mat3.get(1,1) == 22)); // Multiplication matricielle
    
    point4 = (mat2*point3);  // Multiplication matrice-vecteur
    assert((point4.getX() == 4.)&& (point4.getY() == 9.));


	
   
}
// Teste l'affichage de matrices

void test_show_mat_R2()
{
    matR2 mat1(3.2,2.3,4.5,5.4);
    cout << "Affichage de la matrice (3.2,2.3,4.5,5.4) " <<endl;
    mat1.show();
} 


int main()
{
    cout << "Testing vector basics" <<endl;
    test_creation_R2();
    test_show_R2();
    test_distance_R2();
    test_compare_R2();
    test_sum_R2();
    cout << "Testing matrix basics" << endl;
    test_creation_mat_R2();
    test_show_mat_R2();
    cout << "Testing operators" <<endl;
    test_operation_R2();
    cout << " Test well performed !!"<<endl;
    return 0;

}
