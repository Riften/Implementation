#pragma once
#include "object.h"

/*
All kinds of lights will implement a intersect function
which will compute the color of (Intersection &result)
lighted by this light.
*/
class Light {
public:
	Color color;
	bool isShadow;
	double intensity;
	Light();
	virtual ~Light();
	virtual Color intersect(objUnion &scence, Intersection &result);
};

class PointLight :public Light
{
public:
	GVector3 position;
	PointLight();
	PointLight(const Color& _color, const double& _intensity, const GVector3& _position, const bool& _isShadow);
	virtual ~PointLight();
	virtual Color intersect(objUnion &scence, Intersection &result);
};

/*
Note that AmbientLight doesn't have intensity variable.
That is because we don't need to consider then fading of intensity.
We can get the color of intersection by simply multiplying the light color and object color.
*/
class AmbientLight : public Light {
public:
	AmbientLight();
	AmbientLight(Color _color);
	virtual ~AmbientLight();
	virtual Color intersect(objUnion &scene, Intersection &result);
};


class lightUnion
{
public:
	lightUnion();
	virtual ~lightUnion();
	void push(Light* l);
	Color intersect(objUnion &scence, Intersection &result);
	Light* getLight(int i);
protected:
private:
	std::vector<Light*> lights;
};