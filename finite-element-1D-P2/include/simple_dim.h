#ifndef SIMPLE_DIM_H
#define SIMPLE_DIM_H

#include <iostream>
#include <cmath>
using namespace std;
class R1 
{
private:
    double x;
    int label;
public: 
    R1();
    R1(double newX, int isBoundary =-1);
    R1(const R1&);
    double get() const;
    int isBoundary() const;
    
    void set(double newX);

    void setBoundary(int isBoundary);
    void show() const;
    void operator=(const R1& copyVect);
    friend ostream& operator<<(ostream& stream,const R1& pointPrint);
    R1 operator+(R1 addVect);
    double operator,(R1 scalarVect);
    double operator[](int index);
    friend R1 operator*(double lambda, R1 point);
};

double distR1(R1 point1, R1 point2);
bool compR1(R1 point1, R1 point2);

#endif 
