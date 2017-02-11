#ifndef SIMPLE_DIM_H
#define SIMPLE_DIM_H

#include <iostream>
#include <cmath>
using namespace std;
class R2
{
private:
    double x,y;
    int label;
public: 
    R2();
    R2(double newX, int isBoundary =-1);
    R2(const R2&);
    double get() const;
    int isBoundary() const;
    
    void set(double newX);

    void setBoundary(int isBoundary);
    void show() const;
    void operator=(const R2& copyVect);
    friend ostream& operator<<(ostream& stream,const R2& pointPrint);
    R2 operator+(R2 addVect);
    double operator,(R2 scalarVect);
    double operator[](int index);
    friend R2 operator*(double lambda, R2 point);

};

double distR2(R2 point1, R2 point2);
bool compR2(R2 point1, R2 point2);

#endif 
