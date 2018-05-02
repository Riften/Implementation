#include "gvector.h"
#include <iostream>
using namespace std;
GVector3::GVector3()
{
}
GVector3::~GVector3()
{
}
GVector3::GVector3(double posX, double posY, double posZ)
{
	x = posX;
	y = posY;
	z = posZ;
}
GVector3& GVector3::operator=(const GVector3& v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}
GVector3 GVector3::operator+(const GVector3& v)
{
	return GVector3(x + v.x, v.y + y, v.z + z);
}
GVector3 GVector3::operator-(const GVector3& v)
{
	return GVector3(x - v.x, y - v.y, z - v.z);
}
GVector3 GVector3::operator*(const double& n)
{
	return GVector3(x*n, y*n, z*n);
}
GVector3 GVector3::operator/(const double& n)
{
	return GVector3(x / n, y / n, z / n);
}

GVector3 GVector3::abs()
{
	if (x<0) x *= -1;
	if (y<0) y *= -1;
	if (z<0) z *= -1;
	return GVector3(x, y, z);
}
double GVector3::dotMul(const GVector3& v2)
{
	return (x*v2.x + y*v2.y + z*v2.z);
}
GVector3 GVector3::crossMul(const GVector3& v2)
{
	GVector3 vNormal;
	vNormal.x = ((y * v2.z) - (z * v2.y));
	vNormal.y = ((z * v2.x) - (x * v2.z));
	vNormal.z = ((x * v2.y) - (y * v2.x));
	return vNormal;
}
double GVector3::getLength()
{
	return  (double)sqrt(x*x + y*y + z*z);
}
GVector3 GVector3::normalize()
{
	double length = getLength();
	x = x / length;
	y = y / length;
	z = z / length;
	return GVector3(x, y, z);
}
void GVector3::show()
{
	cout << "x:" << x << "  y:" << y << "  z" << z << endl;
}
double GVector3::Max()
{
	double tmp = MAX(y, z);
	return MAX(x, tmp);
}
double GVector3::Min()
{
	double tmp = MIN(y, z);
	return MIN(x, tmp);
}
double GVector3::getDist(const GVector3& v)
{
	double tmp = (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z);
	return sqrt(tmp);
}

GVector3 GVector3::negate() {
	return GVector3(-x, -y, -z);
}