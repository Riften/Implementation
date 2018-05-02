#pragma once
#include "ray.h"

class Material{
private:
	Color color;
	double reflectivity;
public:
	double getRef();
	Color getColor();
	void setRef(const double& _reflectivity);
	void setColor(const Color& _color);
	Material();
	Material(const Color& _color, const double& _reflectivity = 0);
	virtual ~Material();
};
