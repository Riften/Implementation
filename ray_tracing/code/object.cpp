#include "object.h"

//---------------------------------------------
//BaseObj
//---------------------------------------------
BaseObj::BaseObj() {
	material = NULL;
}
BaseObj::~BaseObj() {
}
Intersection BaseObj::intersect(Ray& RAY) {
	//Simple
	return Intersection();
}


//---------------------------------------------
//Plane
//---------------------------------------------
Plane::Plane()
{
	material = NULL;
}

Plane::~Plane()
{
}

Plane::Plane(const GVector3& _normal, const double& _d)
{
	normal = _normal;
	normal.normalize();
	d = _d;
	material = NULL;
}
Plane::Plane(const GVector3& _normal, const double& _d, Material* _material) {
	normal = _normal;
	normal.normalize();
	d = _d;
	material = _material;
}
Intersection Plane::intersect(Ray& ray)
{
	Intersection result = Intersection::noHit();
	double a = ray.getDirection().dotMul(normal);
	if (a <0)
	{
		result.isHit = 1;
		double b = normal.dotMul(normal*d - ray.getOrigin());
		result.distance = b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = normal;
		result.object = this;
	}
	return result;
}



//---------------------------------------------
//Sphere
//---------------------------------------------
Sphere::Sphere(){
	material = NULL;
}
Sphere::Sphere(const GVector3& _center, const double& _radius){
	center = _center;
	radius = _radius;
	material = NULL;
}

Sphere::Sphere(const GVector3& _center, const double& _radius, Material* _material) {
	center = _center;
	radius = _radius;
	material = _material;
}
Sphere::Sphere(const Sphere& s)
{
	center = s.getCenter();
	radius = s.getRadius();
	material = s.material;
}
Sphere::~Sphere()
{
}
void Sphere::setCenter(const GVector3& c)
{
	center = c;
}
void Sphere::setRadius(const double& r)
{
	radius = r;
}
GVector3 Sphere::getCenter() const
{
	return center;
}
double Sphere::getRadius() const
{
	return radius;
}
GVector3 Sphere::getNormal(GVector3 p){
	return (p - center).normalize();
}
void Sphere::move(GVector3& _dc) {
	center = center + _dc;
}
Intersection Sphere::intersect(Ray& _ray){
	Intersection result = Intersection::noHit();
	GVector3 v = _ray.getOrigin() - center;
	double DdotV = _ray.getDirection().dotMul(v);

	if (DdotV < 0) {
		double a2 = v.dotMul(v) - DdotV*DdotV;
		if (a2 < radius*radius) {
			result.isHit = 1;
			result.distance = -DdotV - sqrt(radius*radius - a2);
			result.position = _ray.getPoint(result.distance);
			result.normal = getNormal(result.position);
			result.object = this;
		}
	}
	return result;
}




//---------------------------------------------
//face
//---------------------------------------------
face::face(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = ((v2 - v1).crossMul(v3 - v1)).normalize();
	material = NULL;
}

face::face(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3, Material* _material) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = ((v2 - v1).crossMul(v3 - v1)).normalize();
	material = _material;
}

face::face() :v1(), v2(), v3(), normal() {
	material = NULL;
}

void face::set(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = ((v2 - v1).crossMul(v3 - v1)).normalize();
}

void face::set(const GVector3& _v1, const GVector3& _v2, const GVector3& _v3, Material* _material) {
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = ((v2 - v1).crossMul(v3 - v1)).normalize();
	material = _material;
}

Intersection face::intersect(Ray& RAY) {
	Intersection result = Intersection::noHit();
	//compute A
	GVector3 v12 = v1 - v2;
	GVector3 v13 = v1 - v3;
	GVector3 v1e = v1 - RAY.getOrigin();
	GVector3 d = RAY.getDirection();

	double A = v12.x*v13.y*d.z + v13.x*d.y*v12.z + v12.y*v13.z*d.x -
		v12.z*v13.y*d.x - v12.y*v13.x*d.z - v13.z*d.y*v12.x;
	double B = (v1e.x*v13.y*d.z + v13.x*d.y*v1e.z + v1e.y*v13.z*d.x -
		v1e.z*v13.y*d.x - v1e.y*v13.x*d.z - v13.z*d.y*v1e.x) / A;
	double r = (v12.x*v1e.y*d.z + v1e.x*d.y*v12.z + v12.y*v1e.z*d.x -
		v12.z*v1e.y*d.x - v12.y*v1e.x*d.z - v1e.z*d.y*v12.x) / A;
	double t = (v12.x*v13.y*v1e.z + v13.x*v1e.y*v12.z + v12.y*v13.z*v1e.x -
		v12.z*v13.y*v1e.x - v12.y*v13.x*v1e.z - v13.z*v1e.y*v12.x) / A;
	if (B > 0 && r > 0 && (B + r)<1 && t>0) {
		result.isHit = 1;
		result.distance = t;
		result.position = RAY.getPoint(t);
		result.normal = normal;
		result.object = this;
	}
	return result;

}

objUnion::objUnion()
{
	material = NULL;
}

objUnion::~objUnion()
{
}
void objUnion::push(BaseObj* object)
{
	cobjects.push_back(object);
}
Intersection objUnion::intersect(Ray& _ray)
{
	const double Infinity = 1e30;
	double minDistance = Infinity;
	Intersection minResult = Intersection::noHit();
	int size = cobjects.size();
	for (int i = 0; i<size; ++i) {
		Intersection result = cobjects[i]->intersect(_ray);
		if (result.object && (result.distance < minDistance)) {
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}