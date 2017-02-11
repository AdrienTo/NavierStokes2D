#ifndef DOUBLE_DIM_H
#define DOUBLE_DIM_H

#include <iostream>
#include <cmath>
using namespace std;
class R2
{
private:
    double x,y;
    int label[2];
public: 
    R2();
    R2(double newX, double newY);
    R2(const R2&);
    double getX() const;
    double getY() const;

    int isBoundary() const;
    int getBoundary(int boundaryNumber) const;
    void setBoundary(int boundary, int newLabel);
    void setX(double newX);
    void setY(double newY);
    void show();
    void operator=(const R2& copyVect);
    friend ostream& operator<<(ostream& stream,const R2& pointPrint);
    R2 operator+(R2 addVect);
    double operator,(R2 scalarVect);
    double operator[](int index);
    friend R2 operator*(double lambda, R2 point);

};

double distR2(R2 point1, R2 point2);
bool compR2(R2 point1, R2 point2);

class matR2
{
private:
    double value[4];
public: 
    matR2();
    matR2(double x11,double x12,double x21,double x22);
    matR2(const matR2&);
    double get(int row, int column) const;
    void set(int row, int column, double newValue);
    void show();
    void operator=(const matR2& copyMat);
    friend ostream& operator<<(ostream & stream, matR2 matPrint);
    matR2 operator+(matR2 addMat);
    matR2 operator*(matR2 multMat);
    R2 operator*(R2 vectMult);
    double operator()(int row, int column);

};

double detMatR2(matR2 matrix);
double traceMatR2(matR2 matrix);


#endif 
