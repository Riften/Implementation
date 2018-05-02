#pragma once
#include "gvector.h"  
#define PI 3.14159  

/*
Ray is used in two condition:
	sight ray to do ray tracing;
	reflected ray to compute shadow.
*/
class Ray
{
private:
	GVector3 origin;
	GVector3 direction;
public:
	Ray();
	Ray(const GVector3& o,const GVector3& d);
	~Ray();
	void setOrigin(const GVector3& o);
	void setDirection(const GVector3& d);
	GVector3 getOrigin();
	GVector3 getDirection();
	GVector3 getPoint(double t);
};

class perspectiveCamera {
public:
	perspectiveCamera();
	~perspectiveCamera();
	perspectiveCamera(GVector3& _eye, GVector3& _front, GVector3& _refUp, const double& _fov);
	Ray generateRay(const double& x, const double& y);

private:
	GVector3 eye;
	GVector3 front;
	GVector3 refUp;
	double   fov;
	GVector3 right;
	GVector3 up;
	double   fovScale;
};

class Color
{
public:
	double r;
	double g;
	double b;
	Color();
	Color(const double& _r, const double& _g, const double& _b);
	Color add(const Color& c) const;
	Color multiply(const double& s) const;
	Color modulate(const Color& c) const;
	Color divide(const double& _d) const;

	Color operator+(const Color& c) const;
	Color operator*(const Color& c) const;
	Color operator*(const double& d) const;
	Color operator/(const double& d) const;
	Color& operator=(const Color& c);

	Color saturate();
	void show();
	virtual ~Color();
	static inline Color black() { return Color(0, 0, 0); }
	static inline Color white() { return Color(1, 1, 1); }
	static inline Color red() { return Color(1, 0, 0); }
	static inline Color green() { return Color(0, 1, 0); }
	static inline Color blue() { return Color(0, 0, 1); }
	static inline Color IndianRed1() { return Color(1, 106.0 / 255.0, 106.0 / 255.0); }
	static inline Color BlueViolet() { return Color(138.0 / 255.0, 43.0 / 255.0, 226.0 / 255.0); }
	static inline Color LightSkyBlue() { return Color(135.0 / 255.0, 206.0 / 255.0, 250.0 / 255.0); }
	static inline Color SpringGreen1() { return Color(0.0 / 255.0, 255.0 / 255.0, 127.0 / 255.0); }
	static inline Color DarkOrange1() { return Color(255.0 / 255.0, 127.0 / 255.0, 0.0 / 255.0); }
	static inline Color DarkOrange2() { return Color(255.0 / 255.0, 155.0 / 255.0, 70.0 / 255.0); }
protected:
private:

};


