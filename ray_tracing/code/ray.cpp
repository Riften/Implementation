#include "ray.h"
#include <iostream>
using namespace std;
Ray::Ray()
{
}
Ray::~Ray()
{
}
Ray::Ray(const GVector3& o,const GVector3& d)
{
	origin = o;
	direction = d;
	direction.normalize();
}
void Ray::setDirection(const GVector3& d)
{
	direction = d;
	direction.normalize();
}
void Ray::setOrigin(const GVector3& o)
{
	origin = o;
}
GVector3 Ray::getDirection()
{
	return direction;
}
GVector3 Ray::getOrigin()
{
	return origin;
}
GVector3 Ray::getPoint(double t)
{
	return origin + direction*t;
}



perspectiveCamera::perspectiveCamera()
{

}
perspectiveCamera::~perspectiveCamera()
{
}
perspectiveCamera::perspectiveCamera(GVector3& _eye, GVector3& _front, GVector3& _refUp,const double& _fov)
{
	eye = _eye;
	front = _front.normalize();
	refUp = _refUp.normalize();
	fov = _fov;
	right = front.crossMul(refUp);
	up = right.crossMul(front);
	fovScale = tan(fov* (PI  * 0.5f / 180)) * 2;
}
Ray perspectiveCamera::generateRay(const double& x, const double& y)
{
	GVector3 r = right*((x - 0.5f) * fovScale);
	GVector3 u = up*((y - 0.5f) * fovScale);
	GVector3 tmp = front + r + u;
	tmp.normalize();
	return Ray(eye, tmp);
}


Color::Color()
{
}

Color::~Color()
{
}
Color::Color(const double& _r, const double& _g, const double& _b)
{
	r = _r; g = _g; b = _b;
}
Color Color::add(const Color& c) const
{
	return Color(r + c.r, g + c.g, b + c.b);
}
Color Color::operator+(const Color& c) const {
	return Color(r + c.r, g + c.g, b + c.b);
}
Color Color::multiply(const double& s) const
{
	return Color(r * s, g * s, b * s);
}
Color Color::operator*(const double& d) const {
	return Color(r * d, g * d, b * d);
}
Color Color::modulate(const Color&c) const
{
	return Color(r * c.r, g * c.g, b * c.b);
}
Color Color::operator*(const Color& c) const {
	return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::divide(const double& _d) const{
	return Color(r / _d, g / _d, b / _d);
}
Color Color::operator/(const double& d) const {
	return Color(r / d, g / d, b / d);
}
Color& Color::operator=(const Color& c) {
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}
Color Color::saturate()
{
	r = r>1.0 ? 1.0 : r;
	g = g>1.0 ? 1.0 : g;
	b = b>1.0 ? 1.0 : b;
	return Color(r, g, b);
}
void Color::show()
{
	cout << "r:" << r << "\tg:" << g << "\tb:" << b << endl;
}