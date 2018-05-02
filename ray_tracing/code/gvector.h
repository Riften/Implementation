#pragma once
#include <cmath>  
#define MIN(x,y) (x)>(y)?(y):(x);  
#define MAX(x,y) (x)>(y)?(x):(y);  

/*
GVector3 is the implementation of 3D vector.
I overload some operator for GVector3.
*/
class GVector3
{
public:
	double x;
	double y;
	double z;
	GVector3();
	~GVector3();
	GVector3(double posX, double posY, double posZ);
	GVector3& operator=(const GVector3& v);
	GVector3 operator+(const GVector3& v);
	GVector3 operator-(const GVector3& v);
	GVector3 operator*(const double& n);
	GVector3 operator/(const double& n);
	double dotMul(const GVector3& v2);
	GVector3 crossMul(const GVector3& v2);
	GVector3 abs();
	double Max();
	double Min();
	double getLength();
	GVector3 normalize();	//Note that normalize will change the value of itself.
	double getDist(const GVector3& v);
	static inline GVector3 zero() { return GVector3(0, 0, 0); }
	void show();
	GVector3 negate();

};