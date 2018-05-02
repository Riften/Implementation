#pragma once

#include "ray.h"
#include "material.h"
#include <vector>

class BaseObj;

/*
Intersection is a struct used to compute the intersection
of sight ray and object.
	distance:	distance from eye (origin of ray).
	isHit:		whether the object is intersected by ray.
	position:	position of intersection.
	normal:		normal of the object at the intersection.
	object:		the object that is intersected by ray.
*/
struct Intersection {
	double distance;
	bool isHit;
	GVector3 position;
	GVector3 normal;
	BaseObj* object;
	Intersection() {
		isHit = 0;
		object = NULL;
	}
	static inline Intersection noHit() { return Intersection(); }
};

//BaseObj is the base class of other objects.
//Note: color information is stored in material.
class BaseObj {
public:
	BaseObj();
	~BaseObj();
	virtual Intersection intersect(Ray& RAY);
	Material *material;
};

//Plane is defined by its normal and its distance from origin.
//Note: the positive direction of distance is the same with normal.
class Plane : public BaseObj{
public:
	GVector3 normal;
	double d;
	Plane();
	Plane(const GVector3& _normal, const double& _d);
	Plane(const GVector3& _normal, const double& _d, Material* _material);
	virtual ~Plane();
	virtual Intersection intersect(Ray& RAY);
};

//Sphere is defined by its center and radius
class Sphere :public BaseObj
{
public:
	Sphere();
	Sphere(const Sphere& s);
	Sphere(const GVector3& _center, const double& _radius);
	Sphere(const GVector3& _center, const double& _radius, Material* _material);
	void setCenter(const GVector3& _center);
	void setRadius(const double& _radius);
	void move(GVector3& _dc);
	GVector3 getCenter() const;
	double getRadius() const;
	virtual GVector3 getNormal(GVector3 point);
	virtual Intersection intersect(Ray& RAY);
	virtual ~Sphere();
protected:
private:
	GVector3 center;
	double radius;
};

//face is defined by three vertice.
class face : public BaseObj
{
public:
	GVector3 v1;
	GVector3 v2;
	GVector3 v3;
	GVector3 normal;
	face(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3);
	face(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3, Material* _material);
	face();
	void set(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3);
	void set(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3, Material* _material);
	virtual Intersection intersect(Ray& RAY);
};


//A container used to rend all the objects.
class objUnion :public BaseObj
{
public:
	objUnion();
	virtual ~objUnion();
	void push(BaseObj* object);
	virtual Intersection intersect(Ray& _ray);
protected:
private:
	std::vector<BaseObj*> cobjects;
};