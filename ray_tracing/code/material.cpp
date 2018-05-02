#include "material.h"  

Material::Material() {}
Material::Material(const Color& _color, const double& _reflectivity){
	color = _color;
	reflectivity = _reflectivity;
}
Material::~Material() {}

double Material::getRef(){
	return reflectivity;
}
Color Material::getColor() {
	return color;
}
void Material::setRef(const double& _reflectivity){
	reflectivity = _reflectivity;
}
void Material::setColor(const Color& _color) {
	color = _color;
}
