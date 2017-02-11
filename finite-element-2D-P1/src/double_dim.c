#include "double_dim.h"
#include <assert.h>


/////////////////////////
///// Point methods /////
/////////////////////////

R2::R2()
{};
R2::R2(double newX, double newY)
{
    x = newX;
    y = newY;
    label[0]=-1;
    label[1]=-1;
}
R2::R2(const R2& point)
{
    x = point.getX();
    y = point.getY();
    label[0]=point.getBoundary(0);
    label[1]=point.getBoundary(1);
}

double R2::getX() const
{
    return x;
}
double R2::getY() const
{
    return y;
}
void R2::setX(double newX)
{
    x = newX;
}
void R2::setY(double newY)
{
    y = newY;
}
void R2::show()
{
    cout << "("<< x << ","<<endl;
    cout << y <<")"<< endl;
}
int R2::isBoundary() const
{
    return label[0]>0;
}

void R2::setBoundary(int boundary, int newLabel)
{
    assert(boundary <= 1 && boundary>=0);
    label[boundary] = newLabel;
}
int R2::getBoundary(int boundaryNumber) const
{
    return label[boundaryNumber];
};


double distR2(R2 point1, R2 point2)
{
    double x = point1.getX() - point2.getX();
    double y = point1.getY() - point2.getY();
    return sqrt(x*x+y*y);
}
bool compR2(R2 point1, R2 point2)
{
    return (point1.getX() == point2.getX()) && (point1.getY() ==  point2.getY());
}

////////////
//Operators
////////////

void R2::operator=(const R2& copyVect )
{
    x = copyVect.getX();
    y = copyVect.getY();
}

ostream& operator<<(ostream& stream,const R2 &pointPrint)
{
    stream <<"Point("<<pointPrint.getX()<<","<<pointPrint.getY() <<")";
    return stream; 
}

R2 R2::operator+(R2 addVect)
{
    R2 newVect(x+addVect.getX(),y+addVect.getY());
    return newVect;
}
double R2::operator,(R2 scalarVect)
{
    return x*scalarVect.getX()+y*scalarVect.getY();
}
double R2::operator[](int index)
{
    if((index >1) || (index <0))
    {
         throw "R2 error: index out of range.";
    }
    if(index ==0)
    {
        return x;
    }
    else
    {
        return y;
    }
}
R2 operator*(double lambda, R2 point)
{
    R2  newVect(point.x*lambda, point.y*lambda);
    return newVect;
}
///////////////////////////
//// Matrix methods ///////
///////////////////////////


matR2::matR2(){}

matR2::matR2(double x11,double x12,double x21,double x22)
{
    value[0] =  x11;
    value[1] =  x12;
    value[2] =  x21;
    value[3] =  x22;
}

matR2::matR2(const matR2& source)
{
    value[0] =  source.get(0,0);
    value[1] =  source.get(0,1);
    value[2] =  source.get(1,0);
    value[3] =  source.get(1,1);
}
double matR2::get(int row, int column) const
{
    if(((row*2+column)<0) || ((row*2+column)>3))
    {
        throw "Error mat2: index out of range";
    }
    return value[row*2 + column];
};
void matR2::set(int row, int column, double newValue)
{
    if(((row*2+column)<0) || ((row*2+column)>3))
    {
        throw "Error mat2: index out of range";
    }
    value[row*2+column] = newValue;
};
void matR2::show(){
    cout << "(" << value[0] << "," <<value[1] <<endl;
    cout << value[2] << "," << value[3] << ")" <<endl;

}
void matR2::operator=(const matR2& copyMat)
{
    value[0] =  copyMat.get(0,0);
    value[1] =  copyMat.get(0,1);
    value[2] =  copyMat.get(1,0);
    value[3] =  copyMat.get(1,1);
}

ostream& operator<<(ostream & stream, matR2 matPrint)
{
    return stream <<"Matrix("<<matPrint.get(0,0)<<","<<matPrint.get(0,1)<<endl << matPrint.get(1,0) <<","<<matPrint.get(1,1) <<")"; 
}
matR2 matR2::operator+(matR2 addMat)
{
    matR2 newMat = matR2();
    newMat.set(0,0,value[0]+addMat.get(0,0));
    newMat.set(0,1,value[1]+addMat.get(0,1));
    newMat.set(1,0,value[2]+addMat.get(1,0));
    newMat.set(1,1,value[3]+addMat.get(1,1));
    return newMat;
}
matR2 matR2::operator*(matR2 multMat)
{
    matR2 newMat = matR2();
    for (int i=0; i<2; i++)
    {
       for(int j = 0; j<2; j++)
       {
           newMat.set(i,j,this->get(i,0)*multMat.get(0,j)+this->get(i,1)*multMat.get(1,j));
       }
    }
    return newMat;

}

R2 matR2::operator*(R2 vectMult)
{
    R2 newVect = R2();
    newVect.setX( this->get(0,0)*vectMult.getX()+this->get(0,1)*vectMult.getY());
    newVect.setY(this->get(1,0)*vectMult.getX()+this->get(1,1)*vectMult.getY());
    return newVect;
}
double matR2::operator()(int row, int column)
{
   return this->get(row,column);
}



