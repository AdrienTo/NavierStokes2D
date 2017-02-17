#include "var_problem.h"
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <cassert>
#include <suitesparse/umfpack.h>
#include <algorithm>
#include <limits>


                ///////////////////////////////
                ////// P1 Laplacien Mesh //////
                ///////////////////////////////

double P1_Lapl_Mesh_2D::bilinearForm(R2 * originPoint, R2 *  otherPoint, Tri triangle)
{
        double area = triangle.area();
        double scalar = 0;
        R2 * P1 = triangle.get(0), * P2 = triangle.get(1), * P3 = triangle.get(2);
        // Get the index of the points in the triangle and set the value to -1 if not in the triangle
        int indiceOriginPoint = -(originPoint != P1) + (originPoint == P2)*2 + (originPoint == P3)*3;

        // Same as above, for the other point                    
        int indiceOtherPoint = -(otherPoint != P1) + (otherPoint == P2)*2 + (otherPoint == P3)*3; 
        R2 gradientVectorOriginPoint = R2(NAN,NAN), gradientVectorOtherPoint = R2(NAN,NAN), vectorOneSide = R2(NAN,NAN); 
        assert(indiceOriginPoint <=2 && indiceOriginPoint >=0 );
        assert(indiceOtherPoint <=2 && indiceOtherPoint >=0 );

        // Let ABC be the triangle, the gradient vector of the point A is (orthog(BC)/BC)*1/h = orthog(BC)/(h*BC) = orthog(BC)/(2*area)

        gradientVectorOriginPoint = (*triangle.get( ( indiceOriginPoint+1)%3 ) - *triangle.get( ( indiceOriginPoint+2)%3 )).orthogonal();
       
        // Get the right direction and length
     
        vectorOneSide =    (*triangle.get( ( indiceOriginPoint)%3 ) - *triangle.get( ( indiceOriginPoint+1)%3 ));
        gradientVectorOriginPoint = ( ((vectorOneSide,gradientVectorOriginPoint)>0)*2-1 )*gradientVectorOriginPoint; // Right direction
        gradientVectorOriginPoint = (1/(2*area))*gradientVectorOriginPoint;  


        gradientVectorOtherPoint = (*triangle.get( ( indiceOtherPoint+1)%3 ) - *triangle.get( ( indiceOtherPoint+2)%3 )).orthogonal();
  
       // Get the right direction and length
     
        vectorOneSide =    (*triangle.get( ( indiceOtherPoint)%3 ) - *triangle.get( ( indiceOtherPoint+1)%3 ));
        gradientVectorOtherPoint = ( ((vectorOneSide,gradientVectorOtherPoint)>0)*2-1 )*gradientVectorOtherPoint;     // Right direction
        gradientVectorOtherPoint = (1/(2*area))*gradientVectorOtherPoint; 

        scalar = (gradientVectorOriginPoint,gradientVectorOtherPoint); 

        return  scalar*area;
}
double P1_Lapl_Mesh_2D::linearForm(R2 * originPoint, Tri triangle)
{
        double area = triangle.area();
       //double scalar = 10./3.;
        double x = originPoint->getX(), y=originPoint->getY();
        double scalar = 30*cos((x*x+y*y)*3);
       /* if( x<0.)
        {
            
        }
        else
        {
            return 0.;
        }*/
        return  scalar*area;
}
double P1_Lapl_Mesh_2D::limitCondition(R2* point)
{
    return 0.;
}     


                //////////////////////////////////////////////////
                ////// Orthogonal Mesh - Only test purpose  //////
                //////////////////////////////////////////////////


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

     
