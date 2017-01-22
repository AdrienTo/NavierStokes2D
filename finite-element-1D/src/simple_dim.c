#include "simple_dim.h"



/////////////////////////
///// Point methods /////
/////////////////////////

R1::R1()
{};
R1::R1(double newX)
{
    x = newX;
}
R1::R1(const R1& point)
{
    x = point.get();
}

double R1::get() const
{
    return x;
}

void R1::set(double newX)
{
    x = newX;
}

void R1::show()
{
    cout << "("<< x << ")"<<endl;
}

double distR1(R1 point1, R1 point2)
{

    return fabs(point1.get()-point2.get());
}
bool compR1(R1 point1, R1 point2)
{
    return (point1.get() == point2.get()) ;
}

////////////
//Operators
////////////

void R1::operator=(const R1& copyVect )
{
    x = copyVect.get();
}

ostream& operator<<(ostream& stream,const R1 &pointPrint)
{
    stream <<"Point("<<pointPrint.get()<<")";
    return stream; 
}

R1 R1::operator+(R1 addVect)
{
    R1 newVect(x+addVect.get());
    return newVect;
}
double R1::operator,(R1 scalarVect)
{
    return x*scalarVect.get();
}
double R1::operator[](int index)
{
    if( index !=0 )
    {
         throw "R1 error: index out of range.";
    }
    return x;
}
R1 operator*(double lambda, R1 point)
{
    R1  newVect(point.x*lambda);
    return newVect;
}




