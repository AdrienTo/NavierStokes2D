#include "simple_dim.h"
#include <cassert>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
 
void test_creation_R1()
{
    R1 point1  = R1();
    R1 point2  = R1(3.121);
    R1 point3  = R1(point2);
    point1.set(-1.3);

    assert(point1.get() == -1.3);
    assert(point3.get() == 3.121);
    assert(point2.get() == 3.121);
}

void test_show_R1()
{
    R1 point1 = R1(23.121);
    cout << "Le vecteur à coordonnées X = 23.121 va s'afficher:"<<endl;
    point1.show();
}

// Teste la fonction distance entre points

void test_distance_R1()
{
    R1 point1 = R1(11.5);
    R1 point2 = R1(1.5);
    R1 point3 = R1(0.);
    R1 point4 = R1(1.5); 

    assert( fabs(distR1(point1,point2)-10.)<0.005);
    assert( distR1(point2,point2) == 0.);
    assert(fabs(distR1(point3,point2)-1.5)<0.005);
    assert(fabs(distR1(point2,point4)) == 0 );
    assert(distR1(point1,point2) == distR1(point2,point1));
}

// Teste la fonction de comparaison entre points

void test_compare_R1()
{
    R1 point1 = R1(11.5);
    R1 point2 = R1(1.5);
    R1 point3 = R1(point1);

    assert(compR1(point1,point1));
    assert(compR1(point1,point3));
    assert(!compR1(point1,point2));
    assert(compR1(point3,point1));
}







int main()
{
    cout << "Testing vector basics" <<endl;
    test_creation_R1();
    test_show_R1();
    test_distance_R1();
    test_compare_R1();


    cout << " Test well performed !!"<<endl;
    return 0;

}
