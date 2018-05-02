#include "light.h"
#include <iostream>
using namespace std;
Light::Light() {
	//cout << "Basic constructor of Light\n";
}
Light::~Light() {

}
Color Light::intersect(objUnion &scence, Intersection &rayResult) {
	cout << "Basic intersect of Light\n";
	return Color::white();
}

PointLight::PointLight()
{
}

PointLight::~PointLight()
{ 
}

PointLight::PointLight(const Color& _color, const double& _intensity, const GVector3& _position, const bool& _isShadow = 1)
{
	color = _color;
	intensity = _intensity;
	position = _position;
	isShadow = _isShadow;
}

Color PointLight::intersect(objUnion &scence, Intersection &result)
{
	double factor = 0.05;
	GVector3 v = result.position - position;
	GVector3 vDir = v;
	vDir.normalize();
	double DdotV = result.normal.dotMul(vDir);
	if (DdotV >= 0) {
		return Color::black();
	}
	double distance = v.getLength();

	//shadowRay can be seen as a reflected ray at intersection
	//The reason I add a (vDir.negate()*factor) is avoid intersecting with this object again.
	Ray shadowRay = Ray(result.position+(vDir.negate()*factor), v.negate());
	Intersection lightResult = scence.intersect(shadowRay);
	if (lightResult.isHit && (lightResult.distance <= distance)){
		return Color::black();
	}
	else {
		double fadeIntensity = -(intensity / (distance*distance))*DdotV;
		return ((color*fadeIntensity)*(result.object->material->getColor())).saturate();
	}
}
AmbientLight::AmbientLight() {
	isShadow = false;
	color = Color::white().multiply(0.2);
}

AmbientLight::~AmbientLight() {
}

AmbientLight::AmbientLight(Color _color) {
	isShadow = false;
	color = _color;
	color.saturate();
}

Color AmbientLight::intersect(objUnion &scene, Intersection &result) {
	if (result.isHit) {
		return color*(result.object->material->getColor());
	}
	else {
		return Color::black();
	}
}


lightUnion::lightUnion() {}

lightUnion::~lightUnion() {}

void lightUnion::push(Light* l) {
	lights.push_back(l);
}
Color lightUnion::intersect(objUnion &scence, Intersection &result) {
	long size = lights.size();
	Color resultColor = Color::black();
	for (int i = 0; i < size; i++) {
		resultColor = resultColor.add(lights[i]->intersect(scence, result));
	}
	resultColor.saturate();
	return resultColor;
}

Light* lightUnion::getLight(int i) {
	return lights[i];
}